#include <os2.h>
#define INCL_OS2MM
#include <os2me.h>

#include "../client/client.h"
#include "../client/snd_loc.h"

cvar_t *sndbits = NULL;
cvar_t *sndspeed = NULL;
cvar_t *sndchannels = NULL;

/* MCI is SHIT, SHIT, SHIT !!! */
/* I copied the code from mpg123 - (C) 1998 Samuel Audet <guardia@cam.org>,
   it is impossible to write mci commands from scratch .*/

/* reinit sound each 10 minutes. I don't know why, but after some
   time, sound becames scrambled. */
#define SOUND_REINIT	600

cvar_t *os2_dma_sound_shift = NULL;

int snd_inited = 0;

//static int tryrates[] = { 11025, 22050, 44100, 8000 };

static MCI_AMP_OPEN_PARMS maop;
static MCI_MIXSETUP_PARMS mmp;
static MCI_BUFFER_PARMS mbp;
static MCI_GENERIC_PARMS mgp;
static MCI_SET_PARMS msp;
static MCI_STATUS_PARMS mstatp;
static MCI_MIX_BUFFER MixBuffers[3];

static LONG APIENTRY DARTEvent(ULONG ulStatus, MCI_MIX_BUFFER *PlayedBuffer, ULONG ulFlags)
{
	switch (ulFlags) {
		case MIX_STREAM_ERROR | MIX_WRITE_COMPLETE:
			if (ulStatus == ERROR_DEVICE_UNDERRUN)
				goto play;
			break;
		case MIX_WRITE_COMPLETE:
			play:
			mmp.pmixWrite(mmp.ulMixHandle, &MixBuffers[0], 1);
			break;
	}
	return TRUE;
}
			

qboolean SNDDMA_Init(void)
{
	int samplebits = 8;
	int speed = 11025;
	int channels = 2;

	int flags;
	int r;

	if (snd_inited)
		return 1;

	memset(&maop, 0, sizeof maop);
	maop.usDeviceID = 0;
	maop.pszDeviceType = (PSZ) MAKEULONG(MCI_DEVTYPE_AUDIO_AMPMIX, 0);
	flags = MCI_WAIT | MCI_OPEN_TYPE_ID;
	if ((r = mciSendCommand(0, MCI_OPEN, flags, &maop, 0))) {
		Com_Printf("MCI_OPEN: %d\n", r);
		return 0;
	}


	memset(&mmp, 0, sizeof mmp);

	if (!sndchannels) {
		os2_dma_sound_shift = Cvar_Get("os2_dma_sound_shift", "128", CVAR_ARCHIVE);
		sndbits = Cvar_Get("sndbits",  getenv("QUAKE_SOUND_SAMPLEBITS"), CVAR_ARCHIVE);
		if (!sndbits) sndbits = Cvar_Get("sndbits", "16", CVAR_ARCHIVE);
		sndspeed = Cvar_Get("sndspeed", getenv("QUAKE_SOUND_SPEED"), CVAR_ARCHIVE);
		if (!sndspeed) sndspeed = Cvar_Get("sndspeed", "11025", CVAR_ARCHIVE);
		sndchannels = Cvar_Get("sndchannels", getenv("QUAKE_SOUND_CHANNELS"), CVAR_ARCHIVE);
		if (!sndchannels) sndchannels = Cvar_Get("sndchannels", "2", CVAR_ARCHIVE);
	}

	samplebits = sndbits->value;
	speed = sndspeed->value;
	channels = sndchannels->value;

	if (samplebits != 8 && samplebits != 16) samplebits = 16;
	if (speed < 5000 || speed > 44100) speed = 11025;
	if (channels != 1 && channels != 2) channels = 2;

	mmp.ulBitsPerSample = samplebits;
	mmp.ulFormatTag = MCI_WAVE_FORMAT_PCM;
	mmp.ulSamplesPerSec = speed;
	mmp.ulChannels = channels;

	mmp.ulFormatMode = MCI_PLAY;
	mmp.ulDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO;
	mmp.pmixEvent = DARTEvent;
	if ((r = mciSendCommand(maop.usDeviceID, MCI_MIXSETUP, MCI_WAIT | MCI_MIXSETUP_INIT, &mmp, 0))) {
		Com_Printf("MCI_MIXSETUP: %d\n", r);
		goto clo;
	}

	memset(&msp, 0, sizeof msp);
	msp.ulAudio = MCI_SET_AUDIO_ALL;
	msp.ulLevel = 45;
	if ((r = mciSendCommand(maop.usDeviceID, MCI_SET, MCI_WAIT | MCI_SET_AUDIO | MCI_SET_VOLUME, &msp, 0))) {
		Com_Printf("MCI_SET VOLUME: %d\n", r);
		goto clo;
	}

	memset(&mbp, 0, sizeof(mbp));
	mbp.ulNumBuffers = 3;
	mbp.ulBufferSize = mmp.ulBufferSize;
	mbp.pBufList = MixBuffers;

	MixBuffers[0].ulStructLength = sizeof(MCI_MIX_BUFFER);
	MixBuffers[1].ulStructLength = sizeof(MCI_MIX_BUFFER);
	MixBuffers[2].ulStructLength = sizeof(MCI_MIX_BUFFER);

	if ((r = mciSendCommand(maop.usDeviceID, MCI_BUFFER, MCI_WAIT | MCI_ALLOCATE_MEMORY, &mbp, 0))) {
		Com_Printf("MCI_BUFFER: %d\n", r);
		goto clo;
	}

	MixBuffers[0].ulFlags = 0;
	MixBuffers[0].ulBufferLength = mbp.ulBufferSize;
	MixBuffers[1].ulFlags = 0;
	MixBuffers[1].ulBufferLength = mbp.ulBufferSize;
	memset(MixBuffers[0].pBuffer, 0, mbp.ulBufferSize);
	memset(MixBuffers[1].pBuffer, 0, mbp.ulBufferSize);

	if ((r = mmp.pmixWrite(mmp.ulMixHandle, MixBuffers, 2))) {
		Com_Printf("Write: %d\n", r);
		goto deall;
	}

	snd_inited = 1;

	dma.channels = mmp.ulChannels;
	dma.submission_chunk = 0;
	dma.samplepos = 0;
	dma.samplebits = mmp.ulBitsPerSample;
	dma.speed = mmp.ulSamplesPerSec;
	dma.buffer = MixBuffers[0].pBuffer;
	dma.samples = mbp.ulBufferSize / (dma.samplebits / 8);

	return 1;

	deall:
	if ((r = mciSendCommand(maop.usDeviceID, MCI_BUFFER, MCI_WAIT | MCI_DEALLOCATE_MEMORY, &mbp, 0))) {
		Com_Printf("MCI_BUFFER DEALLOCATE: %d\n", r);
	}
	clo:
	memset(&mgp, 0, sizeof(mgp));
	if ((r = mciSendCommand(maop.usDeviceID, MCI_CLOSE, MCI_WAIT , &mgp, 0))) {
		Com_Printf("MCI_CLOSE: %d\n", r);
	}
	return 0;
}

int SNDDMA_GetDMAPos(void)
{
	static int c = -1;
	static double last;
	int r;
	if (!snd_inited) return 0;
	if (c == -1) last = Sys_Milliseconds() / 1000;
	if (c++ > 256) {
		c = 0;
		if (Sys_Milliseconds() / 1000 - last > SOUND_REINIT) {
			last = Sys_Milliseconds() / 1000;
			SNDDMA_Shutdown();
			SNDDMA_Init();
			if (!snd_inited) return 0;
		}
	}
	memset(&mstatp, 0, sizeof mstatp);
	mstatp.ulItem = MCI_STATUS_POSITION;
	if ((r = mciSendCommand(maop.usDeviceID, MCI_STATUS, MCI_STATUS_ITEM | MCI_WAIT, &mstatp, 0)) & 0xffff) {
		Com_Printf("MCI_STATUS_POSITION: %d\n", r);
		return 0;
	}
	r = (mstatp.ulReturn - MixBuffers[0].ulTime) * mmp.ulSamplesPerSec / 1000;
	r *= mmp.ulChannels /* * (mmp.ulBitsPerSample>>3)*/;
	r += os2_dma_sound_shift->value;
	while (r < 0) r += mbp.ulBufferSize;
	while (r >= mbp.ulBufferSize) r -= mbp.ulBufferSize;
	r &= ~1;
	dma.samplepos = r;
	return r;
}

void SNDDMA_Shutdown(void)
{
	int r;
	if (!snd_inited) return;
	if ((r = mciSendCommand(maop.usDeviceID, MCI_BUFFER, MCI_WAIT | MCI_DEALLOCATE_MEMORY, &mbp, 0))) {
		Com_Printf("MCI_BUFFER DEALLOCATE: %d\n", r);
	}
	memset(&mgp, 0, sizeof(mgp));
	if ((r = mciSendCommand(maop.usDeviceID, MCI_CLOSE, MCI_WAIT , &mgp, 0))) {
		Com_Printf("MCI_CLOSE: %d\n", r);
	}
	snd_inited = 0;
}

/*
==============
SNDDMA_Submit

Send sound to device if buffer isn't really the dma buffer
===============
*/
void SNDDMA_Submit(void)
{
}

void SNDDMA_BeginPainting (void)
{
}

