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
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/ipc.h>
#ifndef __EMX__
#include <sys/shm.h>
#endif
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#ifndef __EMX__
#include <sys/mman.h>
#endif
#include <errno.h>
#ifndef __EMX__
#include <mntent.h>
#endif

#ifndef __EMX__
#include <dlfcn.h>
#else
#define INCL_KBD
#define INCL_DOS
#include <os2.h>
#ifndef FNDELAY
#define FNDELAY O_NDELAY
#endif
#endif

#include "../qcommon/qcommon.h"

#include "../linux/rw_linux.h"

cvar_t *nostdout;

unsigned	sys_frame_time;

uid_t saved_euid;
qboolean stdin_active = true;

// =======================================================================
// General routines
// =======================================================================

void Sys_ConsoleOutput (char *string)
{
	if (nostdout && nostdout->value)
		return;

	fputs(string, stdout);
}

void Sys_Printf (char *fmt, ...)
{
	va_list		argptr;
	char		text[1024];
	unsigned char		*p;

	va_start (argptr,fmt);
	vsprintf (text,fmt,argptr);
	va_end (argptr);

	if (strlen(text) > sizeof(text))
		Sys_Error("memory overwrite in Sys_Printf");

    if (nostdout && nostdout->value)
        return;

	for (p = (unsigned char *)text; *p; p++) {
		*p &= 0x7f;
		if ((*p > 128 || *p < 32) && *p != 10 && *p != 13 && *p != 9)
			printf("[%02x]", *p);
		else
			putc(*p, stdout);
	}
}

void Sys_Quit (void)
{
	CL_Shutdown ();
	Qcommon_Shutdown ();
    fcntl (0, F_SETFL, fcntl (0, F_GETFL, 0) & ~FNDELAY);
	_exit(0);
}

void Sys_Init(void)
{
#if id386
//	Sys_SetFPCW();
#endif
}

void Sys_Error (char *error, ...)
{ 
    va_list     argptr;
    char        string[1024];

// change stdin to non blocking
    fcntl (0, F_SETFL, fcntl (0, F_GETFL, 0) & ~FNDELAY);

	CL_Shutdown ();
	Qcommon_Shutdown ();
    
    va_start (argptr,error);
    vsprintf (string,error,argptr);
    va_end (argptr);
	fprintf(stderr, "Error: %s\n", string);

	_exit (1);

} 

void Sys_Warn (char *warning, ...)
{ 
    va_list     argptr;
    char        string[1024];
    
    va_start (argptr,warning);
    vsprintf (string,warning,argptr);
    va_end (argptr);
	fprintf(stderr, "Warning: %s", string);
} 

/*
============
Sys_FileTime

returns -1 if not present
============
*/
int	Sys_FileTime (char *path)
{
	struct	stat	buf;
	
	if (stat (path,&buf) == -1)
		return -1;
	
	return buf.st_mtime;
}

void floating_point_exception_handler(int whatever)
{
//	Sys_Warn("floating point exception\n");
	signal(SIGFPE, floating_point_exception_handler);
}

#ifndef __EMX__

char *Sys_ConsoleInput(void)
{
    static char text[256];
    int     len;
	fd_set	fdset;
    struct timeval timeout;

	if (!dedicated || !dedicated->value)
		return NULL;

	if (!stdin_active)
		return NULL;

	FD_ZERO(&fdset);
	FD_SET(0, &fdset); // stdin
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	if (select (1, &fdset, NULL, NULL, &timeout) == -1 || !FD_ISSET(0, &fdset))
		return NULL;

	len = read (0, text, sizeof(text));
	if (len == 0) { // eof!
		stdin_active = false;
		return NULL;
	}

	if (len < 1)
		return NULL;
	text[len-1] = 0;    // rip off the /n and terminate

	return text;
}

#else

extern int time_stamp;

char *Sys_ConsoleInput (void)
{
	static int stamp = 0;
	static char text[256];
	static int pos;
	static KBDKEYINFO kki[2];
	static KBDKEYINFO *key = NULL;

	if (!dedicated || !dedicated->value)
		return NULL;

	if (stamp == time_stamp) return NULL;

	stamp = time_stamp;
	try_next:
	if (!key) key = _THUNK_PTR_STRUCT_OK(kki) ? &kki[0] : &kki[1];
	if (KbdCharIn(key, IO_NOWAIT, 0)) return NULL;
	if (!(key->fbStatus & KBDTRF_FINAL_CHAR_IN)) return NULL;
	//printf("%d %08x\n", (int)key->chChar, (int)key->fbStatus);
	if (key->chChar == '\n' || key->chChar == '\r') {
		line:
		printf("\n");fflush(stdout);
		text[pos] = 0;
		pos = 0;
		return text;
	}
	if (key->chChar == 8) {
		if (pos > 0) {
			pos--;
			printf("%c %c", (char)8, (char)8);
		}
		goto try_next;
	}
	text[pos++] = key->chChar;
	if (pos == 255) goto line;
	printf("%c", (char)key->chChar);fflush(stdout);
	goto try_next;
}

#endif

/*****************************************************************************/

#ifndef __EMX__
static void *game_library;
#else
static HMODULE hgame_library;
#endif

/*
=================
Sys_UnloadGame
=================
*/
void Sys_UnloadGame (void)
{
#ifndef __EMX__
	if (game_library) 
		dlclose (game_library);
	game_library = NULL;
#else
	if (hgame_library) 
		DosFreeModule (hgame_library);
	hgame_library = 0;
#endif
}

/*
=================
Sys_GetGameAPI

Loads the game dll
=================
*/
void *Sys_GetGameAPI (void *parms)
{
	void	*(*GetGameAPI) (void *);

	char	name[MAX_OSPATH];
	char	curpath[MAX_OSPATH];
	char	*path;
#ifdef __EMX__
	const char *gamename = "gameos2.dll";
#elif defined __i386__
	const char *gamename = "gamei386.so";
#elif defined __alpha__
	const char *gamename = "gameaxp.so";
#else
#error Unknown arch
#endif

#ifndef __EMX__
	setreuid(getuid(), getuid());
	setegid(getgid());

	if (game_library)
		Com_Error (ERR_FATAL, "Sys_GetGameAPI without Sys_UnloadingGame");
#else
	if (hgame_library)
		Com_Error (ERR_FATAL, "Sys_GetGameAPI without Sys_UnloadingGame");
#endif

	getcwd(curpath, sizeof(curpath));

	Com_Printf("------- Loading %s -------\n", gamename);

	// now run through the search paths
	path = NULL;
	while (1)
	{
		path = FS_NextPath (path);
		if (!path)
			return NULL;		// couldn't find one anywhere
		sprintf (name, "%s/%s/%s", curpath, path, gamename);
#ifndef __EMX__
		game_library = dlopen (name, RTLD_LAZY );
		if (game_library)
#else
		if (!DosLoadModule(NULL, 0, name, &hgame_library))
#endif
		{
			Com_Printf ("LoadLibrary (%s)\n",name);
			break;
		}
	}

#ifndef __EMX__
	GetGameAPI = (void *)dlsym (game_library, "GetGameAPI");
	if (!GetGameAPI)
#else
	if (DosQueryProcAddr(hgame_library, 0, "GetGameAPI", (PFN *)&GetGameAPI))
#endif
	{
		Sys_UnloadGame ();		
		return NULL;
	}

	return GetGameAPI (parms);
}

/*****************************************************************************/

void Sys_AppActivate (void)
{
}

void Sys_SendKeyEvents (void)
{
#ifndef DEDICATED_ONLY
	if (KBD_Update_fp)
		KBD_Update_fp();
#endif

	// grab frame time 
	sys_frame_time = Sys_Milliseconds();
}

/*****************************************************************************/

char *Sys_GetClipboardData(void)
{
	return NULL;
}

#ifndef __EMX__
int main (int c, char **v)
#else
int c;
char **v;
void m(void *xxxx)
#endif
{
	int 	time, oldtime, newtime;

	// go back to real user for config loads
#ifndef __EMX__
	saved_euid = geteuid();
	seteuid(getuid());
#endif

	Qcommon_Init(c, v);

	fcntl(0, F_SETFL, fcntl (0, F_GETFL, 0) | FNDELAY);

	nostdout = Cvar_Get("nostdout", "0", 0);
	if (!nostdout->value) {
		fcntl(0, F_SETFL, fcntl (0, F_GETFL, 0) | FNDELAY);
//		printf ("Linux Quake -- Version %0.3f\n", LINUX_VERSION);
	}

    oldtime = Sys_Milliseconds ();
    while (1)
    {
// find time spent rendering last frame
		do {
			newtime = Sys_Milliseconds ();
			time = newtime - oldtime;
		} while (time < 1);
        Qcommon_Frame (time);
		oldtime = newtime;
    }

}

#ifdef __EMX__

/* Black magic here:
	initialization code in library os2me mangles exception handlers so
	that SIGFPE handler doesn't work and quake crashes on SIGFPE

	When I start another thread, EMX recreates exception handlers for
	that thread and it works fine.
*/

int main(int argc, char **argv)
{
	c = argc;
	v = argv;
	_beginthread(m, NULL, 512 * 1024, NULL);
	while (1) sleep(100000);
}

#endif

void Sys_CopyProtect(void)
{
#ifndef __EMX__
	FILE *mnt;
	struct mntent *ent;
	char path[MAX_OSPATH];
	struct stat st;
	qboolean found_cd = false;

	static qboolean checked = false;

	if (checked)
		return;

	if ((mnt = setmntent("/etc/mtab", "r")) == NULL)
		Com_Error(ERR_FATAL, "Can't read mount table to determine mounted cd location.");

	while ((ent = getmntent(mnt)) != NULL) {
		if (strcmp(ent->mnt_type, "iso9660") == 0) {
			// found a cd file system
			found_cd = true;
			sprintf(path, "%s/%s", ent->mnt_dir, "install/data/quake2.exe");
			if (stat(path, &st) == 0) {
				// found it
				checked = true;
				endmntent(mnt);
				return;
			}
			sprintf(path, "%s/%s", ent->mnt_dir, "Install/Data/quake2.exe");
			if (stat(path, &st) == 0) {
				// found it
				checked = true;
				endmntent(mnt);
				return;
			}
			sprintf(path, "%s/%s", ent->mnt_dir, "quake2.exe");
			if (stat(path, &st) == 0) {
				// found it
				checked = true;
				endmntent(mnt);
				return;
			}
		}
	}
	endmntent(mnt);

	if (found_cd)
		Com_Error (ERR_FATAL, "Could not find a Quake2 CD in your CD drive.");
	Com_Error (ERR_FATAL, "Unable to find a mounted iso9660 file system.\n"
		"You must mount the Quake2 CD in a cdrom drive in order to play.");
#endif
}

#if 0
/*
================
Sys_MakeCodeWriteable
================
*/
void Sys_MakeCodeWriteable (unsigned long startaddr, unsigned long length)
{

	int r;
	unsigned long addr;
	int psize = getpagesize();

	addr = (startaddr & ~(psize-1)) - psize;

//	fprintf(stderr, "writable code %lx(%lx)-%lx, length=%lx\n", startaddr,
//			addr, startaddr+length, length);

	r = mprotect((char*)addr, length + startaddr - addr + psize, 7);

	if (r < 0)
    		Sys_Error("Protection change failed\n");

}

#endif
