/*
Copyright (C) 1996-1997 Id Software, Inc.

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
//
// vgamodes.h: VGA mode set tables
//

#include "vregset.h"

int vrs320x240x256planar[] = {
//
// switch to linear, non-chain4 mode
//
	VRS_BYTE_OUT, SC_INDEX, SYNC_RESET,
	VRS_BYTE_OUT, SC_DATA,  1,

	VRS_BYTE_OUT, SC_INDEX, MEMORY_MODE,
	VRS_BYTE_RMW, SC_DATA, ~0x08, 0x04,
	VRS_BYTE_OUT, GC_INDEX, GRAPHICS_MODE,
	VRS_BYTE_RMW, GC_DATA, ~0x13, 0x00,
	VRS_BYTE_OUT, GC_INDEX, MISCELLANOUS,
	VRS_BYTE_RMW, GC_DATA, ~0x02, 0x00,

	VRS_BYTE_OUT, SC_INDEX, SYNC_RESET,
	VRS_BYTE_OUT, SC_DATA,  3,

//
// unprotect CRTC0 through CRTC0
//
	VRS_BYTE_OUT, CRTC_INDEX, 0x11,
	VRS_BYTE_RMW, CRTC_DATA, ~0x80, 0x00,

//
// set up the CRT Controller
//
	VRS_WORD_OUT, CRTC_INDEX, 0x0D06,
	VRS_WORD_OUT, CRTC_INDEX, 0x3E07,
	VRS_WORD_OUT, CRTC_INDEX, 0x4109,
	VRS_WORD_OUT, CRTC_INDEX, 0xEA10,
	VRS_WORD_OUT, CRTC_INDEX, 0xAC11,
	VRS_WORD_OUT, CRTC_INDEX, 0xDF12,
	VRS_WORD_OUT, CRTC_INDEX, 0x0014,
	VRS_WORD_OUT, CRTC_INDEX, 0xE715,
	VRS_WORD_OUT, CRTC_INDEX, 0x0616,
	VRS_WORD_OUT, CRTC_INDEX, 0xE317,

	VRS_END,
};


