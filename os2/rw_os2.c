/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
/*
** RW_SVGALBI.C
**
** This file contains ALL Linux specific stuff having to do with the
** software refresh.  When a port is being made the following functions
** must be implemented by the port:
**
** SWimp_EndFrame
** SWimp_Init
** SWimp_InitGraphics
** SWimp_SetPalette
** SWimp_Shutdown
** SWimp_SwitchFullscreen
*/

#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_VIO
#include <os2.h>
#include <sys/hw.h>
#include <stdlib.h>

#include "../ref_soft/r_local.h"
#include "../client/keys.h"
#include "../linux/rw_linux.h"
#include "vgamodes.h"
#include "vregset.h"

static VIOMODEINFO old_mode_a[2];
static VIOMODEINFO new_mode_a[2];
static VIOPHYSBUF phys_a[2];

static VIOMODEINFO *old_mode;
static VIOMODEINFO *new_mode;
static VIOPHYSBUF *phys;

static HFILE screen_h = 0;

static int stretch, stretch_x, stretch_y;

static int dont_use_modex = 0, dont_use_os2vid = 0;

int VGA_width, VGA_height, VGA_bufferrowbytes, VGA_rowbytes;
void *VGA_pagebase;

void VGA_UpdatePlanarScreen(void *src);

int vid_os2_can_update(void)
{
	UCHAR st;
	if (VioScrLock(LOCKIO_NOWAIT, &st, 0) || st != LOCK_SUCCESS) {
		_sleep2(50);	/* don't suck CPU time when minimized */
		return 0;
	}
	return 1;
}

void vid_os2_wait_update(void)
{
	UCHAR st;
	int r;
	if ((r = VioScrLock(LOCKIO_WAIT, &st, 0))) {
		if (r == ERROR_VIO_EXTENDED_SG) Sys_Error("You must run Quake in full-screen session.");
		Sys_Error("VioScrLock: %d", r);
	}
	if (st != LOCK_SUCCESS) Sys_Error("VioScrLock: status %d", (int)st);
}

void vid_os2_end_update(void)
{
	if (VioScrUnLock(0)) Sys_Error("VioScrUnlock");
}

/*****************************************************************************/

/*
** SWimp_Init
**
** This routine is responsible for initializing the implementation
** specific stuff in a software rendering subsystem.
*/
int SWimp_Init( void *hInstance, void *wndProc )
{
	int r;
	ULONG act;
	if (getenv("WINDOWID") && *getenv("WINDOWID")) Sys_Error("Trying to run full-screen mode in X-window would crash the machine. Run quake2 +set vid_ref softx");
	if (getenv("QUAKE2_NO_MODEX") && *getenv("QUAKE2_NO_MODEX")) dont_use_modex = 1;
	if (getenv("QUAKE2_NO_OS2VID") && *getenv("QUAKE2_NO_OS2VID")) dont_use_os2vid = 1;
	vid_os2_wait_update();
	old_mode = _THUNK_PTR_STRUCT_OK(old_mode_a) ? old_mode_a : old_mode_a + 1;
	new_mode = _THUNK_PTR_STRUCT_OK(new_mode_a) ? new_mode_a : new_mode_a + 1;
	phys = _THUNK_PTR_STRUCT_OK(phys_a) ? phys_a : phys_a + 1;
	old_mode->cb = sizeof(VIOMODEINFO);
	if ((r = VioGetMode(old_mode, 0))) Sys_Error("VioGetMode: %d", r);
	if (DosOpen("SCREEN$", &screen_h, &act, 0, 0, OPEN_ACTION_OPEN_IF_EXISTS, OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE, NULL)) screen_h = 0;
	vid_os2_end_update();
	return true;
}

/*
** SWimp_InitGraphics
**
** This initializes the software refresh's implementation specific
** graphics subsystem.  In the case of Windows it creates DIB or
** DDRAW surfaces.
**
** The necessary width and height parameters are grabbed from
** vid.width and vid.height.
*/
static qboolean SWimp_InitGraphics( qboolean fullscreen )
{
	int r, x = vid.width, y = vid.height;
	vid_os2_wait_update();
	memcpy(new_mode, old_mode, sizeof(VIOMODEINFO));
	new_mode->color = 8;
	new_mode->fbType = 0x0b;
	new_mode->hres = x;
	new_mode->vres = y;
	new_mode->col = x / 8;
	new_mode->row = y / 16;
	if (!screen_h || dont_use_os2vid || (x == 320 && y == 240 && !dont_use_modex)) goto noos2;
	if ((r = VioSetMode(new_mode, 0))) {
		ri.Con_Printf(PRINT_ALL, "Video mode %dx%d not supported by system. VioSetMode: %d.\nTrying 320x200\n", x, y, r);
		noos2:
		new_mode->fbType = VGMT_OTHER | VGMT_GRAPHICS;
		new_mode->hres = 320;
		new_mode->vres = 200;
		new_mode->col = 40;
		new_mode->row = 25;
		if ((r = VioSetMode(new_mode, 0))) {
			Sys_Error(PRINT_ALL, "Video mode 320x200 not supported by system. VioSetMode: %d.\n", r);
		}
		if (x == 320 && y == 240 && !dont_use_modex) {
			VideoRegisterSet(vrs320x240x256planar);
			stretch = 2;
			VGA_width = 320;
			VGA_height = 240;
			VGA_rowbytes = 80;
			VGA_bufferrowbytes = 320;
		} else {
			stretch = 1;
			stretch_x = 320;
			stretch_y = 200;
		}
	} else stretch = 0;
	phys->pBuf = (PBYTE) 0xa0000;
	phys->cb = 0x10000;
	if ((r = VioGetPhysBuf(phys, 0))) {
		Sys_Error("Can't map video memory. VioGetPhysBuf: %d.", r);
	}
	VGA_pagebase = MAKEP(phys->asel[0], 0);
	ri.Vid_NewWindow (vid.width, vid.height);
	vid.rowbytes = vid.width;
	vid.buffer = realloc(vid.buffer, vid.rowbytes * vid.height);
	vid_os2_end_update();
	return true;
}

static int set_page(int page)
{
	struct {
		ULONG  length;
		USHORT bank;
		USHORT modetype;
		USHORT bankmode;
	} parameter;
	ULONG datalen = 0, parmlen;
	parmlen = sizeof(parameter);
	parameter.length = sizeof parameter;
	parameter.bank = page;
	parameter.modetype = 2;
	parameter.bankmode = 1;
	if (DosDevIOCtl(screen_h, 0x80, 1, &parameter, parmlen, &parmlen, NULL, 0, &datalen)) return -1;
	return 0;
}

/*
** SWimp_EndFrame
**
** This does an implementation specific copy from the backbuffer to the
** front buffer.  In the Win32 case it uses BitBlt or BltFast depending
** on whether we're using DIB sections/GDI or DDRAW.
*/
void SWimp_EndFrame (void)
{
	int page = 0;
	char *src = vid.buffer;
	char *end = (char *)vid.buffer + vid.rowbytes * vid.height;
	if (!vid_os2_can_update()) return;
	if (!stretch) do {
		int len;
		set_page(page++);
		len = end - src;
		if (len > 0x10000) len = 0x10000;
		memcpy(VGA_pagebase, src, len);
		src += 0x10000;
	} while (src < end); else if (stretch == 1) {
		int x, y;
		char *v = VGA_pagebase;
		int ye = 0;
		for (y = 0; y < stretch_y; y++) {
			char *pp = src;
			int xe = 0;
			if (stretch_x == vid.width) {
				memcpy(v, src, vid.width);
				v += vid.width;
			} else for (x = 0 ; x < stretch_x; x++) {
				*v++ = *pp;
				xe += vid.width;
				while (xe >= stretch_x) xe -= stretch_x, pp++;
			}
			ye += vid.height;
			while (ye >= stretch_y) ye -= stretch_y, src += vid.rowbytes;
		}
	} else {
		VGA_UpdatePlanarScreen(src);
	}
	vid_os2_end_update();
}

/*
** SWimp_SetMode
*/
rserr_t SWimp_SetMode( int *pwidth, int *pheight, int mode, qboolean fullscreen )
{
	rserr_t retval = rserr_ok;

	ri.Con_Printf (PRINT_ALL, "setting mode %d:", mode );

	if ( !ri.Vid_GetModeInfo( pwidth, pheight, mode ) )
	{
		ri.Con_Printf( PRINT_ALL, " invalid mode\n" );
		return rserr_invalid_mode;
	}

	ri.Con_Printf( PRINT_ALL, " %d %d\n", *pwidth, *pheight);

	if ( !SWimp_InitGraphics( false ) ) {
		// failed to set a valid mode in windowed mode
		return rserr_invalid_mode;
	}

	R_GammaCorrectAndSetPalette( ( const unsigned char * ) d_8to24table );

	return retval;
}

/*
** SWimp_SetPalette
**
** System specific palette setting routine.  A NULL palette means
** to use the existing palette.  The palette is expected to be in
** a padded 4-byte xRGB format.
*/
void SWimp_SetPalette( const unsigned char *palette )
{
	int i;

	if (!vid_os2_can_update()) return;

        if ( !palette )
		palette = ( const unsigned char * ) sw_state.currentpalette;
	
	_outp8(0x3c8, 0);
	i = 0;
	while (i < 1024) {
		_outp8(0x3c9, palette[i++]>>2);
		_outp8(0x3c9, palette[i++]>>2);
		_outp8(0x3c9, palette[i++]>>2);
		i++;
	}

	vid_os2_end_update();
}

/*
** SWimp_Shutdown
**
** System specific graphics subsystem shutdown routine.  Destroys
** DIBs or DDRAW surfaces as appropriate.
*/
void SWimp_Shutdown( void )
{
	vid_os2_wait_update();
	if (vid.buffer) {
		free(vid.buffer);
		vid.buffer = NULL;
	}
	VioSetMode(old_mode, 0);
	vid_os2_end_update();
}

/*
** SWimp_AppActivate
*/
void SWimp_AppActivate( qboolean active )
{
}

//===============================================================================

/*
================
Sys_MakeCodeWriteable
================
*/

void Sys_MakeCodeWriteable (unsigned long startaddr, unsigned long length)
{
	int r;
	r = DosSetMem((void *)startaddr, length, PAG_READ | PAG_WRITE | PAG_EXECUTE);
	if (r < 0)
    		Sys_Error("Protection change failed: %d\n", r);

}

