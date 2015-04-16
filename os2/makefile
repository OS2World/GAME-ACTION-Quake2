#
# Quake2 Makefile for Linux 2.0
#
# Nov '97 by Zoid <zoid@idsoftware.com>
#
# ELF only
#

VERSION=3.21
VERSION_FN=$(VERSION)$(GLIBC)
RPM_RELEASE=6

ifneq (,$(findstring libc6,$(shell if [ -e /lib/libc.so.6* ];then echo libc6;fi)))
GLIBC=-glibc
else
GLIBC=
endif

GAMENAME=os2
ifneq (,$(findstring alpha,$(shell uname -m)))
ARCH=axp
RPMARCH=alpha
else
ARCH=i386
RPMARCH=i386
endif
NOARCH=noarch

MOUNT_DIR=..
VWEP_DIR=/grog/Projects/Quake2/vwep
QUAKE2_DIR=/grog/Projects/Quake2Master

BUILD_DEBUG_DIR=debug$(ARCH)$(GLIBC)
BUILD_RELEASE_DIR=release$(ARCH)$(GLIBC)
CLIENT_DIR=$(MOUNT_DIR)/client
SERVER_DIR=$(MOUNT_DIR)/server
REF_SOFT_DIR=$(MOUNT_DIR)/ref_soft
REF_GL_DIR=$(MOUNT_DIR)/ref_gl
COMMON_DIR=$(MOUNT_DIR)/qcommon
LINUX_DIR=$(MOUNT_DIR)/linux
OS2_DIR=$(MOUNT_DIR)/os2
GAME_DIR=$(MOUNT_DIR)/game
NULL_DIR=$(MOUNT_DIR)/null
CTF_DIR=$(MOUNT_DIR)/ctf
XATRIX_DIR=$(MOUNT_DIR)/xatrix
ROGUE_DIR=$(MOUNT_DIR)/rogue

MESA_DIR=/usr/local/src/Mesa-2.6

EGCS=/usr/local/egcs-1.1.2/bin/gcc

CC=gcc
#BASE_CFLAGS=-Dstricmp=strcasecmp
BASE_CFLAGS=-D__linux__ -Zmt -Wall

ifeq ($(ARCH),axp)
RELEASE_CFLAGS=$(BASE_CFLAGS) -O6 -ffast-math -funroll-loops \
	-fomit-frame-pointer -fexpensive-optimizations
else
# ********* -funroll-loops is BUGGY in GCC 3.0.4 !!!!!!!!! ***********
#RELEASE_CFLAGS=$(BASE_CFLAGS) -m486 -O6 -ffast-math \
#	-fomit-frame-pointer -fexpensive-optimizations
RELEASE_CFLAGS=$(BASE_CFLAGS) -mcpu=pentium -O6 -ffast-math \
	-fomit-frame-pointer -fexpensive-optimizations -Zomf
#RELEASE_CFLAGS=$(BASE_CFLAGS)
endif

DEBUG_CFLAGS=$(BASE_CFLAGS) -g
LDFLAGS=-lm -lsocket -los2me -Zbin-files -Zcrtdll
#-Zlinker /packcode -Zlinker /packdata -Zlinker /exepack:2 -s
SVGALDFLAGS=-lm
XLDFLAGS=-Le:/XFree86/lib -lbsd -lshm -lXxf86dga -lX11 -lXext
XCFLAGS=-Ie:/XFree86/include

GLLDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -L$(MESA_DIR)/lib -lX11 -lXext -lvga -lm
GLXLDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -L$(MESA_DIR)/lib -lX11 -lXext -lXxf86dga -lXxf86vm -lm
GLCFLAGS=-I$(MESA_DIR)/include -I/usr/include/glide

SHLIBEXT=dll

#SHLIBCFLAGS=-fPIC
#SHLIBLDFLAGS=-shared
SHLIBLDFLAGS=-Zbin-files -Zcrtdll -Zdll
#-Zlinker /packcode -Zlinker /packdata -Zlinker /exepack:2 -s

DO_CC=$(CC) $(CFLAGS) -o $@ -c $<
DO_DEBUG_CC=$(CC) $(DEBUG_CFLAGS) -o $@ -c $<
DO_DED_CC=$(CC) $(CFLAGS) -DDEDICATED_ONLY -o $@ -c $<
DO_DED_DEBUG_CC=$(CC) $(DEBUG_CFLAGS) -DDEDICATED_ONLY -o $@ -c $<
DO_O_CC=$(CC) $(CFLAGS) -O -o $@ -c $<
DO_O0_CC=$(CC) $(CFLAGS) -O0 -o $@ -c $<
DO_SHLIB_CC=$(CC) $(CFLAGS) $(SHLIBCFLAGS) -o $@ -c $<
DO_SHLIB_O_CC=$(CC) $(CFLAGS) -O $(SHLIBCFLAGS) -o $@ -c $<
DO_SHLIB_O0_CC=$(CC) $(CFLAGS) -O0 $(SHLIBCFLAGS) -o $@ -c $<
DO_SHLIB_DEBUG_CC=$(CC) $(DEBUG_CFLAGS) $(SHLIBCFLAGS) -o $@ -c $<
DO_GL_SHLIB_CC=$(CC) $(CFLAGS) $(SHLIBCFLAGS) $(GLCFLAGS) -o $@ -c $<
DO_GL_SHLIB_O_CC=$(CC) $(CFLAGS) -O $(SHLIBCFLAGS) $(GLCFLAGS) -o $@ -c $<
DO_GL_SHLIB_O_CC=$(CC) $(CFLAGS) -O0 $(SHLIBCFLAGS) $(GLCFLAGS) -o $@ -c $<
DO_AS=$(CC) $(CFLAGS) -x assembler-with-cpp -o $@ -c $<
DO_SHLIB_AS=$(CC) $(CFLAGS) $(SHLIBCFLAGS) -x assembler-with-cpp -o $@ -c $<

#############################################################################
# SETUP AND BUILD
#############################################################################

ifeq ($(ARCH),axp)
TARGETS=$(BUILDDIR)/q2ded \
	$(BUILDDIR)/game$(GAMENAME).$(SHLIBEXT) \
	$(BUILDDIR)/ctf/game$(GAMENAME).$(SHLIBEXT) \
#	$(BUILDDIR)/xatrix/game$(GAMENAME).$(SHLIBEXT) \
#	$(BUILDDIR)/rogue/game$(GAMENAME).$(SHLIBEXT)
else
TARGETS=$(BUILDDIR)/quake2.exe \
	$(BUILDDIR)/game$(GAMENAME).$(SHLIBEXT) \
	$(BUILDDIR)/r_softx.$(SHLIBEXT) \
	$(BUILDDIR)/r_soft.$(SHLIBEXT) \
	$(BUILDDIR)/ctf/game$(GAMENAME).$(SHLIBEXT) \
#	$(BUILDDIR)/r_gl.$(SHLIBEXT) \
#	$(BUILDDIR)/r_glx.$(SHLIBEXT) \
#	$(BUILDDIR)/xatrix/game$(GAMENAME).$(SHLIBEXT) \
#	$(BUILDDIR)/rogue/game$(GAMENAME).$(SHLIBEXT)
endif

build_debug:
#	@-mkdir $(BUILD_DEBUG_DIR) \
#		$(BUILD_DEBUG_DIR)/client \
#		$(BUILD_DEBUG_DIR)/ded \
#		$(BUILD_DEBUG_DIR)/ref_soft \
#		$(BUILD_DEBUG_DIR)/ref_gl \
#		$(BUILD_DEBUG_DIR)/game \
#		$(BUILD_DEBUG_DIR)/ctf \
#		$(BUILD_DEBUG_DIR)/xatrix \
#		$(BUILD_DEBUG_DIR)/rogue
	$(MAKE) targets BUILDDIR=$(BUILD_DEBUG_DIR) CFLAGS="$(DEBUG_CFLAGS)" OBJ=".o"

build_release:
#	@-mkdir $(BUILD_RELEASE_DIR) \
#		$(BUILD_RELEASE_DIR)/client \
#		$(BUILD_RELEASE_DIR)/ded \
#		$(BUILD_RELEASE_DIR)/ref_soft \
#		$(BUILD_RELEASE_DIR)/ref_gl \
#		$(BUILD_RELEASE_DIR)/game \
#		$(BUILD_RELEASE_DIR)/ctf \
#		$(BUILD_RELEASE_DIR)/xatrix \
#		$(BUILD_RELEASE_DIR)/rogue
	$(MAKE) targets BUILDDIR=$(BUILD_RELEASE_DIR) CFLAGS="$(RELEASE_CFLAGS)" OBJ=".obj"

all: build_debug build_release

targets: $(TARGETS)

#############################################################################
# CLIENT/SERVER
#############################################################################

QUAKE2_OBJS = \
	$(BUILDDIR)/client/cl_cin$(OBJ) \
	$(BUILDDIR)/client/cl_ents$(OBJ) \
	$(BUILDDIR)/client/cl_fx$(OBJ) \
	$(BUILDDIR)/client/cl_input$(OBJ) \
	$(BUILDDIR)/client/cl_inv$(OBJ) \
	$(BUILDDIR)/client/cl_main$(OBJ) \
	$(BUILDDIR)/client/cl_newfx$(OBJ) \
	$(BUILDDIR)/client/cl_parse$(OBJ) \
	$(BUILDDIR)/client/cl_pred$(OBJ) \
	$(BUILDDIR)/client/cl_tent$(OBJ) \
	$(BUILDDIR)/client/cl_scrn$(OBJ) \
	$(BUILDDIR)/client/cl_view$(OBJ) \
	$(BUILDDIR)/client/console$(OBJ) \
	$(BUILDDIR)/client/keys$(OBJ) \
	$(BUILDDIR)/client/menu$(OBJ) \
	$(BUILDDIR)/client/snd_dma$(OBJ) \
	$(BUILDDIR)/client/snd_mem$(OBJ) \
	$(BUILDDIR)/client/snd_mix$(OBJ) \
	$(BUILDDIR)/client/qmenu$(OBJ) \
	$(BUILDDIR)/client/m_flash$(OBJ) \
	\
	$(BUILDDIR)/client/cmd$(OBJ) \
	$(BUILDDIR)/client/cmodel$(OBJ) \
	$(BUILDDIR)/client/common$(OBJ) \
	$(BUILDDIR)/client/crc$(OBJ) \
	$(BUILDDIR)/client/cvar$(OBJ) \
	$(BUILDDIR)/client/files$(OBJ) \
	$(BUILDDIR)/client/md4$(OBJ) \
	$(BUILDDIR)/client/net_chan$(OBJ) \
	\
	$(BUILDDIR)/client/sv_ccmds$(OBJ) \
	$(BUILDDIR)/client/sv_ents$(OBJ) \
	$(BUILDDIR)/client/sv_game$(OBJ) \
	$(BUILDDIR)/client/sv_init$(OBJ) \
	$(BUILDDIR)/client/sv_main$(OBJ) \
	$(BUILDDIR)/client/sv_send$(OBJ) \
	$(BUILDDIR)/client/sv_user$(OBJ) \
	$(BUILDDIR)/client/sv_world$(OBJ) \
	\
	$(BUILDDIR)/client/cd_null$(OBJ) \
	$(BUILDDIR)/client/q_shlinux$(OBJ) \
	$(BUILDDIR)/client/vid_menu$(OBJ) \
	$(BUILDDIR)/client/vid_so$(OBJ) \
	$(BUILDDIR)/client/snd_os2$(OBJ) \
	$(BUILDDIR)/client/sys_linux$(OBJ) \
	$(BUILDDIR)/client/glob$(OBJ) \
	$(BUILDDIR)/client/net_udp$(OBJ) \
	\
	$(BUILDDIR)/client/q_shared$(OBJ) \
	$(BUILDDIR)/client/pmove$(OBJ)

ifeq ($(ARCH),axp)
QUAKE2_AS_OBJS =  #blank
else
QUAKE2_AS_OBJS = \
	$(BUILDDIR)/client/snd_mixa$(OBJ)
endif

$(BUILDDIR)/quake2.exe : $(QUAKE2_OBJS) $(QUAKE2_AS_OBJS)
	$(CC) $(CFLAGS) -o $@ $(QUAKE2_OBJS) $(QUAKE2_AS_OBJS) $(LDFLAGS)

$(BUILDDIR)/client/cl_cin$(OBJ) :     $(CLIENT_DIR)/cl_cin.c
	$(DO_CC)

$(BUILDDIR)/client/cl_ents$(OBJ) :    $(CLIENT_DIR)/cl_ents.c
	$(DO_CC)

$(BUILDDIR)/client/cl_fx$(OBJ) :      $(CLIENT_DIR)/cl_fx.c
	$(DO_CC)

$(BUILDDIR)/client/cl_input$(OBJ) :   $(CLIENT_DIR)/cl_input.c
	$(DO_CC)

$(BUILDDIR)/client/cl_inv$(OBJ) :     $(CLIENT_DIR)/cl_inv.c
	$(DO_CC)

$(BUILDDIR)/client/cl_main$(OBJ) :    $(CLIENT_DIR)/cl_main.c
	$(DO_CC)

$(BUILDDIR)/client/cl_newfx$(OBJ) :    $(CLIENT_DIR)/cl_newfx.c
	$(DO_CC)

$(BUILDDIR)/client/cl_parse$(OBJ) :   $(CLIENT_DIR)/cl_parse.c
	$(DO_CC)

$(BUILDDIR)/client/cl_pred$(OBJ) :    $(CLIENT_DIR)/cl_pred.c
	$(DO_CC)

$(BUILDDIR)/client/cl_tent$(OBJ) :    $(CLIENT_DIR)/cl_tent.c
	$(DO_CC)

$(BUILDDIR)/client/cl_scrn$(OBJ) :    $(CLIENT_DIR)/cl_scrn.c
	$(DO_CC)

$(BUILDDIR)/client/cl_view$(OBJ) :    $(CLIENT_DIR)/cl_view.c
	$(DO_CC)

$(BUILDDIR)/client/console$(OBJ) :    $(CLIENT_DIR)/console.c
	$(DO_CC)

$(BUILDDIR)/client/keys$(OBJ) :       $(CLIENT_DIR)/keys.c
	$(DO_CC)

$(BUILDDIR)/client/menu$(OBJ) :       $(CLIENT_DIR)/menu.c
	$(DO_CC)

$(BUILDDIR)/client/snd_dma$(OBJ) :    $(CLIENT_DIR)/snd_dma.c
	$(DO_CC)

$(BUILDDIR)/client/snd_mem$(OBJ) :    $(CLIENT_DIR)/snd_mem.c
	$(DO_CC)

$(BUILDDIR)/client/snd_mix$(OBJ) :    $(CLIENT_DIR)/snd_mix.c
	$(DO_CC)

$(BUILDDIR)/client/qmenu$(OBJ) :      $(CLIENT_DIR)/qmenu.c
	$(DO_CC)

$(BUILDDIR)/client/m_flash$(OBJ) :    $(GAME_DIR)/m_flash.c
	$(DO_CC)

$(BUILDDIR)/client/cmd$(OBJ) :        $(COMMON_DIR)/cmd.c
	$(DO_CC)

$(BUILDDIR)/client/cmodel$(OBJ) :     $(COMMON_DIR)/cmodel.c
	$(DO_CC)

$(BUILDDIR)/client/common$(OBJ) :     $(COMMON_DIR)/common.c
	$(DO_CC)

$(BUILDDIR)/client/crc$(OBJ) :        $(COMMON_DIR)/crc.c
	$(DO_CC)

$(BUILDDIR)/client/cvar$(OBJ) :       $(COMMON_DIR)/cvar.c
	$(DO_CC)

$(BUILDDIR)/client/files$(OBJ) :      $(COMMON_DIR)/files.c
	$(DO_CC)

$(BUILDDIR)/client/md4$(OBJ) :        $(COMMON_DIR)/md4.c
	$(DO_CC)

$(BUILDDIR)/client/net_chan$(OBJ) :   $(COMMON_DIR)/net_chan.c
	$(DO_CC)

$(BUILDDIR)/client/q_shared$(OBJ) :   $(GAME_DIR)/q_shared.c
	$(DO_O0_CC)

$(BUILDDIR)/client/pmove$(OBJ) :      $(COMMON_DIR)/pmove.c
	$(DO_CC)

$(BUILDDIR)/client/sv_ccmds$(OBJ) :   $(SERVER_DIR)/sv_ccmds.c
	$(DO_CC)

$(BUILDDIR)/client/sv_ents$(OBJ) :    $(SERVER_DIR)/sv_ents.c
	$(DO_CC)

$(BUILDDIR)/client/sv_game$(OBJ) :    $(SERVER_DIR)/sv_game.c
	$(DO_CC)

$(BUILDDIR)/client/sv_init$(OBJ) :    $(SERVER_DIR)/sv_init.c
	$(DO_CC)

$(BUILDDIR)/client/sv_main$(OBJ) :    $(SERVER_DIR)/sv_main.c
	$(DO_CC)

$(BUILDDIR)/client/sv_send$(OBJ) :    $(SERVER_DIR)/sv_send.c
	$(DO_CC)

$(BUILDDIR)/client/sv_user$(OBJ) :    $(SERVER_DIR)/sv_user.c
	$(DO_CC)

$(BUILDDIR)/client/sv_world$(OBJ) :   $(SERVER_DIR)/sv_world.c
	$(DO_CC)

$(BUILDDIR)/client/cd_null$(OBJ) :   $(NULL_DIR)/cd_null.c
	$(DO_CC)

$(BUILDDIR)/client/q_shlinux$(OBJ) :  $(LINUX_DIR)/q_shlinux.c
	$(DO_O_CC)

$(BUILDDIR)/client/vid_menu$(OBJ) :   $(LINUX_DIR)/vid_menu.c
	$(DO_CC)

$(BUILDDIR)/client/vid_so$(OBJ) :     $(LINUX_DIR)/vid_so.c
	$(DO_CC)

$(BUILDDIR)/client/snd_os2$(OBJ) :    $(OS2_DIR)/snd_os2.c
	$(DO_CC)

$(BUILDDIR)/client/snd_mixa$(OBJ) :   $(LINUX_DIR)/snd_mixa.s
	$(DO_AS)

$(BUILDDIR)/client/sys_linux$(OBJ) :  $(LINUX_DIR)/sys_linux.c
	$(DO_CC)

$(BUILDDIR)/client/glob$(OBJ) :       $(LINUX_DIR)/glob.c
	$(DO_CC)

$(BUILDDIR)/client/net_udp$(OBJ) :    $(LINUX_DIR)/net_udp.c
	$(DO_CC)

#############################################################################
# DEDICATED SERVER
#############################################################################

Q2DED_OBJS = \
	\
	$(BUILDDIR)/ded/cmd$(OBJ) \
	$(BUILDDIR)/ded/cmodel$(OBJ) \
	$(BUILDDIR)/ded/common$(OBJ) \
	$(BUILDDIR)/ded/crc$(OBJ) \
	$(BUILDDIR)/ded/cvar$(OBJ) \
	$(BUILDDIR)/ded/files$(OBJ) \
	$(BUILDDIR)/ded/md4$(OBJ) \
	$(BUILDDIR)/ded/net_chan$(OBJ) \
	\
	$(BUILDDIR)/ded/sv_ccmds$(OBJ) \
	$(BUILDDIR)/ded/sv_ents$(OBJ) \
	$(BUILDDIR)/ded/sv_game$(OBJ) \
	$(BUILDDIR)/ded/sv_init$(OBJ) \
	$(BUILDDIR)/ded/sv_main$(OBJ) \
	$(BUILDDIR)/ded/sv_send$(OBJ) \
	$(BUILDDIR)/ded/sv_user$(OBJ) \
	$(BUILDDIR)/ded/sv_world$(OBJ) \
	\
	$(BUILDDIR)/ded/q_shlinux$(OBJ) \
	$(BUILDDIR)/ded/sys_linux$(OBJ) \
	$(BUILDDIR)/ded/glob$(OBJ) \
	$(BUILDDIR)/ded/net_udp$(OBJ) \
	\
	$(BUILDDIR)/ded/q_shared$(OBJ) \
	$(BUILDDIR)/ded/pmove$(OBJ) \
	\
	$(BUILDDIR)/ded/cl_null$(OBJ) \
	$(BUILDDIR)/ded/cd_null$(OBJ)

$(BUILDDIR)/q2ded : $(Q2DED_OBJS)
	$(CC) $(CFLAGS) -o $@ $(Q2DED_OBJS) $(LDFLAGS)

$(BUILDDIR)/ded/cmd$(OBJ) :        $(COMMON_DIR)/cmd.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/cmodel$(OBJ) :     $(COMMON_DIR)/cmodel.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/common$(OBJ) :     $(COMMON_DIR)/common.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/crc$(OBJ) :        $(COMMON_DIR)/crc.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/cvar$(OBJ) :       $(COMMON_DIR)/cvar.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/files$(OBJ) :      $(COMMON_DIR)/files.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/md4$(OBJ) :        $(COMMON_DIR)/md4.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/net_chan$(OBJ) :   $(COMMON_DIR)/net_chan.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/q_shared$(OBJ) :   $(GAME_DIR)/q_shared.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/pmove$(OBJ) :      $(COMMON_DIR)/pmove.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sv_ccmds$(OBJ) :   $(SERVER_DIR)/sv_ccmds.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sv_ents$(OBJ) :    $(SERVER_DIR)/sv_ents.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sv_game$(OBJ) :    $(SERVER_DIR)/sv_game.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sv_init$(OBJ) :    $(SERVER_DIR)/sv_init.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sv_main$(OBJ) :    $(SERVER_DIR)/sv_main.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sv_send$(OBJ) :    $(SERVER_DIR)/sv_send.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sv_user$(OBJ) :    $(SERVER_DIR)/sv_user.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sv_world$(OBJ) :   $(SERVER_DIR)/sv_world.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/q_shlinux$(OBJ) :  $(LINUX_DIR)/q_shlinux.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/sys_linux$(OBJ) :  $(LINUX_DIR)/sys_linux.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/glob$(OBJ) :       $(LINUX_DIR)/glob.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/net_udp$(OBJ) :    $(LINUX_DIR)/net_udp.c
	$(DO_DED_CC)

$(BUILDDIR)/ded/cd_null$(OBJ)     : $(NULL_DIR)/cd_null.c    
	$(DO_DED_CC)

$(BUILDDIR)/ded/cl_null$(OBJ)     : $(NULL_DIR)/cl_null.c    
	$(DO_DED_CC)

#############################################################################
# GAME
#############################################################################

GAME_OBJS = \
	$(BUILDDIR)/game/q_shared$(OBJ) \
	$(BUILDDIR)/game/g_ai$(OBJ) \
	$(BUILDDIR)/game/p_client$(OBJ) \
	$(BUILDDIR)/game/g_cmds$(OBJ) \
	$(BUILDDIR)/game/g_svcmds$(OBJ) \
	$(BUILDDIR)/game/g_chase$(OBJ) \
	$(BUILDDIR)/game/g_combat$(OBJ) \
	$(BUILDDIR)/game/g_func$(OBJ) \
	$(BUILDDIR)/game/g_items$(OBJ) \
	$(BUILDDIR)/game/g_main$(OBJ) \
	$(BUILDDIR)/game/g_misc$(OBJ) \
	$(BUILDDIR)/game/g_monster$(OBJ) \
	$(BUILDDIR)/game/g_phys$(OBJ) \
	$(BUILDDIR)/game/g_save$(OBJ) \
	$(BUILDDIR)/game/g_spawn$(OBJ) \
	$(BUILDDIR)/game/g_target$(OBJ) \
	$(BUILDDIR)/game/g_trigger$(OBJ) \
	$(BUILDDIR)/game/g_turret$(OBJ) \
	$(BUILDDIR)/game/g_utils$(OBJ) \
	$(BUILDDIR)/game/g_weapon$(OBJ) \
	$(BUILDDIR)/game/m_actor$(OBJ) \
	$(BUILDDIR)/game/m_berserk$(OBJ) \
	$(BUILDDIR)/game/m_boss2$(OBJ) \
	$(BUILDDIR)/game/m_boss3$(OBJ) \
	$(BUILDDIR)/game/m_boss31$(OBJ) \
	$(BUILDDIR)/game/m_boss32$(OBJ) \
	$(BUILDDIR)/game/m_brain$(OBJ) \
	$(BUILDDIR)/game/m_chick$(OBJ) \
	$(BUILDDIR)/game/m_flipper$(OBJ) \
	$(BUILDDIR)/game/m_float$(OBJ) \
	$(BUILDDIR)/game/m_flyer$(OBJ) \
	$(BUILDDIR)/game/m_gladiator$(OBJ) \
	$(BUILDDIR)/game/m_gunner$(OBJ) \
	$(BUILDDIR)/game/m_hover$(OBJ) \
	$(BUILDDIR)/game/m_infantry$(OBJ) \
	$(BUILDDIR)/game/m_insane$(OBJ) \
	$(BUILDDIR)/game/m_medic$(OBJ) \
	$(BUILDDIR)/game/m_move$(OBJ) \
	$(BUILDDIR)/game/m_mutant$(OBJ) \
	$(BUILDDIR)/game/m_parasite$(OBJ) \
	$(BUILDDIR)/game/m_soldier$(OBJ) \
	$(BUILDDIR)/game/m_supertank$(OBJ) \
	$(BUILDDIR)/game/m_tank$(OBJ) \
	$(BUILDDIR)/game/p_hud$(OBJ) \
	$(BUILDDIR)/game/p_trail$(OBJ) \
	$(BUILDDIR)/game/p_view$(OBJ) \
	$(BUILDDIR)/game/p_weapon$(OBJ) \
	$(BUILDDIR)/game/m_flash$(OBJ)

$(BUILDDIR)/game$(GAMENAME).$(SHLIBEXT) : $(GAME_OBJS) game.def
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(GAME_OBJS) game.def

$(BUILDDIR)/game/g_ai$(OBJ) :        $(GAME_DIR)/g_ai.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_client$(OBJ) :    $(GAME_DIR)/p_client.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_cmds$(OBJ) :      $(GAME_DIR)/g_cmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_svcmds$(OBJ) :    $(GAME_DIR)/g_svcmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_chase$(OBJ) :    $(GAME_DIR)/g_chase.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_combat$(OBJ) :    $(GAME_DIR)/g_combat.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_func$(OBJ) :      $(GAME_DIR)/g_func.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_items$(OBJ) :     $(GAME_DIR)/g_items.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_main$(OBJ) :      $(GAME_DIR)/g_main.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_misc$(OBJ) :      $(GAME_DIR)/g_misc.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_monster$(OBJ) :   $(GAME_DIR)/g_monster.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_phys$(OBJ) :      $(GAME_DIR)/g_phys.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_save$(OBJ) :      $(GAME_DIR)/g_save.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_spawn$(OBJ) :     $(GAME_DIR)/g_spawn.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_target$(OBJ) :    $(GAME_DIR)/g_target.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_trigger$(OBJ) :   $(GAME_DIR)/g_trigger.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_turret$(OBJ) :    $(GAME_DIR)/g_turret.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_utils$(OBJ) :     $(GAME_DIR)/g_utils.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/g_weapon$(OBJ) :    $(GAME_DIR)/g_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_actor$(OBJ) :     $(GAME_DIR)/m_actor.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_berserk$(OBJ) :   $(GAME_DIR)/m_berserk.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_boss2$(OBJ) :     $(GAME_DIR)/m_boss2.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_boss3$(OBJ) :     $(GAME_DIR)/m_boss3.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_boss31$(OBJ) :     $(GAME_DIR)/m_boss31.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_boss32$(OBJ) :     $(GAME_DIR)/m_boss32.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_brain$(OBJ) :     $(GAME_DIR)/m_brain.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_chick$(OBJ) :     $(GAME_DIR)/m_chick.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_flipper$(OBJ) :   $(GAME_DIR)/m_flipper.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_float$(OBJ) :     $(GAME_DIR)/m_float.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_flyer$(OBJ) :     $(GAME_DIR)/m_flyer.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_gladiator$(OBJ) : $(GAME_DIR)/m_gladiator.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_gunner$(OBJ) :    $(GAME_DIR)/m_gunner.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_hover$(OBJ) :     $(GAME_DIR)/m_hover.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_infantry$(OBJ) :  $(GAME_DIR)/m_infantry.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_insane$(OBJ) :    $(GAME_DIR)/m_insane.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_medic$(OBJ) :     $(GAME_DIR)/m_medic.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_move$(OBJ) :      $(GAME_DIR)/m_move.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_mutant$(OBJ) :    $(GAME_DIR)/m_mutant.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_parasite$(OBJ) :  $(GAME_DIR)/m_parasite.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_soldier$(OBJ) :   $(GAME_DIR)/m_soldier.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_supertank$(OBJ) : $(GAME_DIR)/m_supertank.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/m_tank$(OBJ) :      $(GAME_DIR)/m_tank.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_hud$(OBJ) :       $(GAME_DIR)/p_hud.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_trail$(OBJ) :     $(GAME_DIR)/p_trail.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_view$(OBJ) :      $(GAME_DIR)/p_view.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/p_weapon$(OBJ) :    $(GAME_DIR)/p_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/game/q_shared$(OBJ) :    $(GAME_DIR)/q_shared.c
	$(DO_SHLIB_O0_CC)

$(BUILDDIR)/game/m_flash$(OBJ) :     $(GAME_DIR)/m_flash.c
	$(DO_SHLIB_CC)

#############################################################################
# CTF
#############################################################################

CTF_OBJS = \
	$(BUILDDIR)/ctf/g_ai$(OBJ) \
	$(BUILDDIR)/ctf/g_chase$(OBJ) \
	$(BUILDDIR)/ctf/g_cmds$(OBJ) \
	$(BUILDDIR)/ctf/g_combat$(OBJ) \
	$(BUILDDIR)/ctf/g_ctf$(OBJ) \
	$(BUILDDIR)/ctf/g_func$(OBJ) \
	$(BUILDDIR)/ctf/g_items$(OBJ) \
	$(BUILDDIR)/ctf/g_main$(OBJ) \
	$(BUILDDIR)/ctf/g_misc$(OBJ) \
	$(BUILDDIR)/ctf/g_monster$(OBJ) \
	$(BUILDDIR)/ctf/g_phys$(OBJ) \
	$(BUILDDIR)/ctf/g_save$(OBJ) \
	$(BUILDDIR)/ctf/g_spawn$(OBJ) \
	$(BUILDDIR)/ctf/g_svcmds$(OBJ) \
	$(BUILDDIR)/ctf/g_target$(OBJ) \
	$(BUILDDIR)/ctf/g_trigger$(OBJ) \
	$(BUILDDIR)/ctf/g_utils$(OBJ) \
	$(BUILDDIR)/ctf/g_weapon$(OBJ) \
	$(BUILDDIR)/ctf/m_move$(OBJ) \
	$(BUILDDIR)/ctf/p_client$(OBJ) \
	$(BUILDDIR)/ctf/p_hud$(OBJ) \
	$(BUILDDIR)/ctf/p_menu$(OBJ) \
	$(BUILDDIR)/ctf/p_trail$(OBJ) \
	$(BUILDDIR)/ctf/p_view$(OBJ) \
	$(BUILDDIR)/ctf/p_weapon$(OBJ) \
	$(BUILDDIR)/ctf/q_shared$(OBJ)

$(BUILDDIR)/ctf/game$(GAMENAME).$(SHLIBEXT) : $(CTF_OBJS) game.def
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(CTF_OBJS) game.def

$(BUILDDIR)/ctf/g_ai$(OBJ) :       $(CTF_DIR)/g_ai.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_chase$(OBJ) :    $(CTF_DIR)/g_chase.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_cmds$(OBJ) :     $(CTF_DIR)/g_cmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_combat$(OBJ) :   $(CTF_DIR)/g_combat.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_ctf$(OBJ) :      $(CTF_DIR)/g_ctf.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_func$(OBJ) :     $(CTF_DIR)/g_func.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_items$(OBJ) :    $(CTF_DIR)/g_items.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_main$(OBJ) :     $(CTF_DIR)/g_main.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_misc$(OBJ) :     $(CTF_DIR)/g_misc.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_monster$(OBJ) :  $(CTF_DIR)/g_monster.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_phys$(OBJ) :     $(CTF_DIR)/g_phys.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_save$(OBJ) :     $(CTF_DIR)/g_save.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_spawn$(OBJ) :    $(CTF_DIR)/g_spawn.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_svcmds$(OBJ) :   $(CTF_DIR)/g_svcmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_target$(OBJ) :   $(CTF_DIR)/g_target.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_trigger$(OBJ) :  $(CTF_DIR)/g_trigger.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_utils$(OBJ) :    $(CTF_DIR)/g_utils.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/g_weapon$(OBJ) :   $(CTF_DIR)/g_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/m_move$(OBJ) :     $(CTF_DIR)/m_move.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/p_client$(OBJ) :   $(CTF_DIR)/p_client.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/p_hud$(OBJ) :      $(CTF_DIR)/p_hud.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/p_menu$(OBJ) :     $(CTF_DIR)/p_menu.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/p_trail$(OBJ) :    $(CTF_DIR)/p_trail.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/p_view$(OBJ) :     $(CTF_DIR)/p_view.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/p_weapon$(OBJ) :   $(CTF_DIR)/p_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ctf/q_shared$(OBJ) :   $(CTF_DIR)/q_shared.c
	$(DO_SHLIB_O0_CC)

#############################################################################
# XATRIX
#############################################################################

XATRIX_OBJS = \
	$(BUILDDIR)/xatrix/g_ai$(OBJ) \
	$(BUILDDIR)/xatrix/g_cmds$(OBJ) \
	$(BUILDDIR)/xatrix/g_chase$(OBJ) \
	$(BUILDDIR)/xatrix/g_combat$(OBJ) \
	$(BUILDDIR)/xatrix/g_func$(OBJ) \
	$(BUILDDIR)/xatrix/g_items$(OBJ) \
	$(BUILDDIR)/xatrix/g_main$(OBJ) \
	$(BUILDDIR)/xatrix/g_misc$(OBJ) \
	$(BUILDDIR)/xatrix/g_monster$(OBJ) \
	$(BUILDDIR)/xatrix/g_phys$(OBJ) \
	$(BUILDDIR)/xatrix/g_save$(OBJ) \
	$(BUILDDIR)/xatrix/g_spawn$(OBJ) \
	$(BUILDDIR)/xatrix/g_svcmds$(OBJ) \
	$(BUILDDIR)/xatrix/g_target$(OBJ) \
	$(BUILDDIR)/xatrix/g_trigger$(OBJ) \
	$(BUILDDIR)/xatrix/g_turret$(OBJ) \
	$(BUILDDIR)/xatrix/g_utils$(OBJ) \
	$(BUILDDIR)/xatrix/g_weapon$(OBJ) \
	$(BUILDDIR)/xatrix/m_actor$(OBJ) \
	$(BUILDDIR)/xatrix/m_berserk$(OBJ) \
	$(BUILDDIR)/xatrix/m_boss2$(OBJ) \
	$(BUILDDIR)/xatrix/m_boss3$(OBJ) \
	$(BUILDDIR)/xatrix/m_boss31$(OBJ) \
	$(BUILDDIR)/xatrix/m_boss32$(OBJ) \
	$(BUILDDIR)/xatrix/m_boss5$(OBJ) \
	$(BUILDDIR)/xatrix/m_brain$(OBJ) \
	$(BUILDDIR)/xatrix/m_chick$(OBJ) \
	$(BUILDDIR)/xatrix/m_fixbot$(OBJ) \
	$(BUILDDIR)/xatrix/m_flash$(OBJ) \
	$(BUILDDIR)/xatrix/m_flipper$(OBJ) \
	$(BUILDDIR)/xatrix/m_float$(OBJ) \
	$(BUILDDIR)/xatrix/m_flyer$(OBJ) \
	$(BUILDDIR)/xatrix/m_gekk$(OBJ) \
	$(BUILDDIR)/xatrix/m_gladb$(OBJ) \
	$(BUILDDIR)/xatrix/m_gladiator$(OBJ) \
	$(BUILDDIR)/xatrix/m_gunner$(OBJ) \
	$(BUILDDIR)/xatrix/m_hover$(OBJ) \
	$(BUILDDIR)/xatrix/m_infantry$(OBJ) \
	$(BUILDDIR)/xatrix/m_insane$(OBJ) \
	$(BUILDDIR)/xatrix/m_medic$(OBJ) \
	$(BUILDDIR)/xatrix/m_move$(OBJ) \
	$(BUILDDIR)/xatrix/m_mutant$(OBJ) \
	$(BUILDDIR)/xatrix/m_parasite$(OBJ) \
	$(BUILDDIR)/xatrix/m_soldier$(OBJ) \
	$(BUILDDIR)/xatrix/m_supertank$(OBJ) \
	$(BUILDDIR)/xatrix/m_tank$(OBJ) \
	$(BUILDDIR)/xatrix/p_client$(OBJ) \
	$(BUILDDIR)/xatrix/p_hud$(OBJ) \
	$(BUILDDIR)/xatrix/p_trail$(OBJ) \
	$(BUILDDIR)/xatrix/p_view$(OBJ) \
	$(BUILDDIR)/xatrix/p_weapon$(OBJ) \
	$(BUILDDIR)/xatrix/q_shared$(OBJ)

$(BUILDDIR)/xatrix/game$(GAMENAME).$(SHLIBEXT) : $(XATRIX_OBJS)
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(XATRIX_OBJS)

$(BUILDDIR)/xatrix/g_ai$(OBJ) :        $(XATRIX_DIR)/g_ai.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_cmds$(OBJ) :      $(XATRIX_DIR)/g_cmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_chase$(OBJ) :    $(XATRIX_DIR)/g_chase.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_combat$(OBJ) :    $(XATRIX_DIR)/g_combat.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_func$(OBJ) :      $(XATRIX_DIR)/g_func.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_items$(OBJ) :     $(XATRIX_DIR)/g_items.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_main$(OBJ) :      $(XATRIX_DIR)/g_main.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_misc$(OBJ) :      $(XATRIX_DIR)/g_misc.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_monster$(OBJ) :   $(XATRIX_DIR)/g_monster.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_phys$(OBJ) :      $(XATRIX_DIR)/g_phys.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_save$(OBJ) :      $(XATRIX_DIR)/g_save.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_spawn$(OBJ) :     $(XATRIX_DIR)/g_spawn.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_svcmds$(OBJ) :    $(XATRIX_DIR)/g_svcmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_target$(OBJ) :    $(XATRIX_DIR)/g_target.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_trigger$(OBJ) :   $(XATRIX_DIR)/g_trigger.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_turret$(OBJ) :    $(XATRIX_DIR)/g_turret.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_utils$(OBJ) :     $(XATRIX_DIR)/g_utils.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/g_weapon$(OBJ) :    $(XATRIX_DIR)/g_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_actor$(OBJ) :     $(XATRIX_DIR)/m_actor.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_berserk$(OBJ) :   $(XATRIX_DIR)/m_berserk.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_boss2$(OBJ) :     $(XATRIX_DIR)/m_boss2.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_boss3$(OBJ) :     $(XATRIX_DIR)/m_boss3.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_boss31$(OBJ) :    $(XATRIX_DIR)/m_boss31.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_boss32$(OBJ) :    $(XATRIX_DIR)/m_boss32.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_boss5$(OBJ) :     $(XATRIX_DIR)/m_boss5.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_brain$(OBJ) :     $(XATRIX_DIR)/m_brain.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_chick$(OBJ) :     $(XATRIX_DIR)/m_chick.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_fixbot$(OBJ) :    $(XATRIX_DIR)/m_fixbot.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_flash$(OBJ) :     $(XATRIX_DIR)/m_flash.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_flipper$(OBJ) :   $(XATRIX_DIR)/m_flipper.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_float$(OBJ) :     $(XATRIX_DIR)/m_float.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_flyer$(OBJ) :     $(XATRIX_DIR)/m_flyer.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_gekk$(OBJ) :      $(XATRIX_DIR)/m_gekk.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_gladb$(OBJ) :     $(XATRIX_DIR)/m_gladb.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_gladiator$(OBJ) : $(XATRIX_DIR)/m_gladiator.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_gunner$(OBJ) :    $(XATRIX_DIR)/m_gunner.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_hover$(OBJ) :     $(XATRIX_DIR)/m_hover.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_infantry$(OBJ) :  $(XATRIX_DIR)/m_infantry.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_insane$(OBJ) :    $(XATRIX_DIR)/m_insane.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_medic$(OBJ) :     $(XATRIX_DIR)/m_medic.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_move$(OBJ) :      $(XATRIX_DIR)/m_move.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_mutant$(OBJ) :    $(XATRIX_DIR)/m_mutant.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_parasite$(OBJ) :  $(XATRIX_DIR)/m_parasite.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_soldier$(OBJ) :   $(XATRIX_DIR)/m_soldier.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_supertank$(OBJ) : $(XATRIX_DIR)/m_supertank.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/m_tank$(OBJ) :      $(XATRIX_DIR)/m_tank.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/p_client$(OBJ) :    $(XATRIX_DIR)/p_client.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/p_hud$(OBJ) :       $(XATRIX_DIR)/p_hud.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/p_trail$(OBJ) :     $(XATRIX_DIR)/p_trail.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/p_view$(OBJ) :      $(XATRIX_DIR)/p_view.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/p_weapon$(OBJ) :    $(XATRIX_DIR)/p_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/xatrix/q_shared$(OBJ) :    $(XATRIX_DIR)/q_shared.c
	$(DO_SHLIB_O0_CC)

#############################################################################
# ROGUE
#############################################################################

ROGUE_OBJS = \
	$(BUILDDIR)/rogue/dm_ball$(OBJ) \
	$(BUILDDIR)/rogue/dm_tag$(OBJ) \
	$(BUILDDIR)/rogue/g_ai$(OBJ) \
	$(BUILDDIR)/rogue/g_chase$(OBJ) \
	$(BUILDDIR)/rogue/g_cmds$(OBJ) \
	$(BUILDDIR)/rogue/g_combat$(OBJ) \
	$(BUILDDIR)/rogue/g_func$(OBJ) \
	$(BUILDDIR)/rogue/g_items$(OBJ) \
	$(BUILDDIR)/rogue/g_main$(OBJ) \
	$(BUILDDIR)/rogue/g_misc$(OBJ) \
	$(BUILDDIR)/rogue/g_monster$(OBJ) \
	$(BUILDDIR)/rogue/g_newai$(OBJ) \
	$(BUILDDIR)/rogue/g_newdm$(OBJ) \
	$(BUILDDIR)/rogue/g_newfnc$(OBJ) \
	$(BUILDDIR)/rogue/g_newtarg$(OBJ) \
	$(BUILDDIR)/rogue/g_newtrig$(OBJ) \
	$(BUILDDIR)/rogue/g_newweap$(OBJ) \
	$(BUILDDIR)/rogue/g_phys$(OBJ) \
	$(BUILDDIR)/rogue/g_save$(OBJ) \
	$(BUILDDIR)/rogue/g_spawn$(OBJ) \
	$(BUILDDIR)/rogue/g_sphere$(OBJ) \
	$(BUILDDIR)/rogue/g_svcmds$(OBJ) \
	$(BUILDDIR)/rogue/g_target$(OBJ) \
	$(BUILDDIR)/rogue/g_trigger$(OBJ) \
	$(BUILDDIR)/rogue/g_turret$(OBJ) \
	$(BUILDDIR)/rogue/g_utils$(OBJ) \
	$(BUILDDIR)/rogue/g_weapon$(OBJ) \
	$(BUILDDIR)/rogue/m_actor$(OBJ) \
	$(BUILDDIR)/rogue/m_berserk$(OBJ) \
	$(BUILDDIR)/rogue/m_boss2$(OBJ) \
	$(BUILDDIR)/rogue/m_boss3$(OBJ) \
	$(BUILDDIR)/rogue/m_boss31$(OBJ) \
	$(BUILDDIR)/rogue/m_boss32$(OBJ) \
	$(BUILDDIR)/rogue/m_brain$(OBJ) \
	$(BUILDDIR)/rogue/m_carrier$(OBJ) \
	$(BUILDDIR)/rogue/m_chick$(OBJ) \
	$(BUILDDIR)/rogue/m_flash$(OBJ) \
	$(BUILDDIR)/rogue/m_flipper$(OBJ) \
	$(BUILDDIR)/rogue/m_float$(OBJ) \
	$(BUILDDIR)/rogue/m_flyer$(OBJ) \
	$(BUILDDIR)/rogue/m_gladiator$(OBJ) \
	$(BUILDDIR)/rogue/m_gunner$(OBJ) \
	$(BUILDDIR)/rogue/m_hover$(OBJ) \
	$(BUILDDIR)/rogue/m_infantry$(OBJ) \
	$(BUILDDIR)/rogue/m_insane$(OBJ) \
	$(BUILDDIR)/rogue/m_medic$(OBJ) \
	$(BUILDDIR)/rogue/m_move$(OBJ) \
	$(BUILDDIR)/rogue/m_mutant$(OBJ) \
	$(BUILDDIR)/rogue/m_parasite$(OBJ) \
	$(BUILDDIR)/rogue/m_soldier$(OBJ) \
	$(BUILDDIR)/rogue/m_stalker$(OBJ) \
	$(BUILDDIR)/rogue/m_supertank$(OBJ) \
	$(BUILDDIR)/rogue/m_tank$(OBJ) \
	$(BUILDDIR)/rogue/m_turret$(OBJ) \
	$(BUILDDIR)/rogue/m_widow$(OBJ) \
	$(BUILDDIR)/rogue/m_widow2$(OBJ) \
	$(BUILDDIR)/rogue/p_client$(OBJ) \
	$(BUILDDIR)/rogue/p_hud$(OBJ) \
	$(BUILDDIR)/rogue/p_trail$(OBJ) \
	$(BUILDDIR)/rogue/p_view$(OBJ) \
	$(BUILDDIR)/rogue/p_weapon$(OBJ) \
	$(BUILDDIR)/rogue/q_shared$(OBJ)

$(BUILDDIR)/rogue/game$(GAMENAME).$(SHLIBEXT) : $(ROGUE_OBJS)
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(ROGUE_OBJS)

$(BUILDDIR)/rogue/dm_ball$(OBJ) :      $(ROGUE_DIR)/dm_ball.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/dm_tag$(OBJ) :       $(ROGUE_DIR)/dm_tag.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_ai$(OBJ) :         $(ROGUE_DIR)/g_ai.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_chase$(OBJ) :      $(ROGUE_DIR)/g_chase.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_cmds$(OBJ) :       $(ROGUE_DIR)/g_cmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_combat$(OBJ) :     $(ROGUE_DIR)/g_combat.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_func$(OBJ) :       $(ROGUE_DIR)/g_func.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_items$(OBJ) :      $(ROGUE_DIR)/g_items.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_main$(OBJ) :       $(ROGUE_DIR)/g_main.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_misc$(OBJ) :       $(ROGUE_DIR)/g_misc.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_monster$(OBJ) :    $(ROGUE_DIR)/g_monster.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_newai$(OBJ) :      $(ROGUE_DIR)/g_newai.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_newdm$(OBJ) :      $(ROGUE_DIR)/g_newdm.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_newfnc$(OBJ) :     $(ROGUE_DIR)/g_newfnc.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_newtarg$(OBJ) :    $(ROGUE_DIR)/g_newtarg.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_newtrig$(OBJ) :    $(ROGUE_DIR)/g_newtrig.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_newweap$(OBJ) :    $(ROGUE_DIR)/g_newweap.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_phys$(OBJ) :       $(ROGUE_DIR)/g_phys.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_save$(OBJ) :       $(ROGUE_DIR)/g_save.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_spawn$(OBJ) :      $(ROGUE_DIR)/g_spawn.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_sphere$(OBJ) :     $(ROGUE_DIR)/g_sphere.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_svcmds$(OBJ) :     $(ROGUE_DIR)/g_svcmds.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_target$(OBJ) :     $(ROGUE_DIR)/g_target.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_trigger$(OBJ) :    $(ROGUE_DIR)/g_trigger.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_turret$(OBJ) :     $(ROGUE_DIR)/g_turret.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_utils$(OBJ) :      $(ROGUE_DIR)/g_utils.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/g_weapon$(OBJ) :     $(ROGUE_DIR)/g_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_actor$(OBJ) :      $(ROGUE_DIR)/m_actor.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_berserk$(OBJ) :    $(ROGUE_DIR)/m_berserk.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_boss2$(OBJ) :      $(ROGUE_DIR)/m_boss2.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_boss3$(OBJ) :      $(ROGUE_DIR)/m_boss3.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_boss31$(OBJ) :     $(ROGUE_DIR)/m_boss31.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_boss32$(OBJ) :     $(ROGUE_DIR)/m_boss32.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_brain$(OBJ) :      $(ROGUE_DIR)/m_brain.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_carrier$(OBJ) :    $(ROGUE_DIR)/m_carrier.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_chick$(OBJ) :      $(ROGUE_DIR)/m_chick.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_flash$(OBJ) :      $(ROGUE_DIR)/m_flash.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_flipper$(OBJ) :    $(ROGUE_DIR)/m_flipper.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_float$(OBJ) :      $(ROGUE_DIR)/m_float.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_flyer$(OBJ) :      $(ROGUE_DIR)/m_flyer.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_gladiator$(OBJ) :  $(ROGUE_DIR)/m_gladiator.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_gunner$(OBJ) :     $(ROGUE_DIR)/m_gunner.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_hover$(OBJ) :      $(ROGUE_DIR)/m_hover.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_infantry$(OBJ) :   $(ROGUE_DIR)/m_infantry.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_insane$(OBJ) :     $(ROGUE_DIR)/m_insane.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_medic$(OBJ) :      $(ROGUE_DIR)/m_medic.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_move$(OBJ) :       $(ROGUE_DIR)/m_move.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_mutant$(OBJ) :     $(ROGUE_DIR)/m_mutant.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_parasite$(OBJ) :   $(ROGUE_DIR)/m_parasite.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_soldier$(OBJ) :    $(ROGUE_DIR)/m_soldier.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_stalker$(OBJ) :    $(ROGUE_DIR)/m_stalker.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_supertank$(OBJ) :  $(ROGUE_DIR)/m_supertank.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_tank$(OBJ) :       $(ROGUE_DIR)/m_tank.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_turret$(OBJ) :     $(ROGUE_DIR)/m_turret.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_widow$(OBJ) :      $(ROGUE_DIR)/m_widow.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/m_widow2$(OBJ) :     $(ROGUE_DIR)/m_widow2.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/p_client$(OBJ) :     $(ROGUE_DIR)/p_client.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/p_hud$(OBJ) :        $(ROGUE_DIR)/p_hud.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/p_trail$(OBJ) :      $(ROGUE_DIR)/p_trail.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/p_view$(OBJ) :       $(ROGUE_DIR)/p_view.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/p_weapon$(OBJ) :     $(ROGUE_DIR)/p_weapon.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/rogue/q_shared$(OBJ) :     $(ROGUE_DIR)/q_shared.c
	$(DO_SHLIB_O0_CC)




#############################################################################
# REF_SOFT
#############################################################################

REF_SOFT_OBJS = \
	$(BUILDDIR)/ref_soft/r_aclip$(OBJ) \
	$(BUILDDIR)/ref_soft/r_alias$(OBJ) \
	$(BUILDDIR)/ref_soft/r_bsp$(OBJ) \
	$(BUILDDIR)/ref_soft/r_draw$(OBJ) \
	$(BUILDDIR)/ref_soft/r_edge$(OBJ) \
	$(BUILDDIR)/ref_soft/r_image$(OBJ) \
	$(BUILDDIR)/ref_soft/r_light$(OBJ) \
	$(BUILDDIR)/ref_soft/r_main$(OBJ) \
	$(BUILDDIR)/ref_soft/r_misc$(OBJ) \
	$(BUILDDIR)/ref_soft/r_model$(OBJ) \
	$(BUILDDIR)/ref_soft/r_part$(OBJ) \
	$(BUILDDIR)/ref_soft/r_poly$(OBJ) \
	$(BUILDDIR)/ref_soft/r_polyse$(OBJ) \
	$(BUILDDIR)/ref_soft/r_rast$(OBJ) \
	$(BUILDDIR)/ref_soft/r_scan$(OBJ) \
	$(BUILDDIR)/ref_soft/r_sprite$(OBJ) \
	$(BUILDDIR)/ref_soft/r_surf$(OBJ) \
	\
	$(BUILDDIR)/ref_soft/r_aclipa$(OBJ) \
	$(BUILDDIR)/ref_soft/r_draw16$(OBJ) \
	$(BUILDDIR)/ref_soft/r_drawa$(OBJ) \
	$(BUILDDIR)/ref_soft/r_edgea$(OBJ) \
	$(BUILDDIR)/ref_soft/r_scana$(OBJ) \
	$(BUILDDIR)/ref_soft/r_spr8$(OBJ) \
	$(BUILDDIR)/ref_soft/r_surf8$(OBJ) \
	$(BUILDDIR)/ref_soft/math$(OBJ) \
	$(BUILDDIR)/ref_soft/d_polysa$(OBJ) \
	$(BUILDDIR)/ref_soft/r_varsa$(OBJ) \
	$(BUILDDIR)/ref_soft/sys_dosa$(OBJ) \
	\
	$(BUILDDIR)/ref_soft/q_shared$(OBJ) \
	$(BUILDDIR)/ref_soft/q_shlinux$(OBJ) \
	$(BUILDDIR)/ref_soft/glob$(OBJ)

REF_SOFT_SVGA_OBJS = \
	$(BUILDDIR)/ref_soft/rw_os2$(OBJ) \
	$(BUILDDIR)/ref_soft/in_os2$(OBJ) \
	$(BUILDDIR)/ref_soft/kbd_os2$(OBJ) \
	$(BUILDDIR)/ref_soft/vregset$(OBJ) \
	$(BUILDDIR)/ref_soft/d_copy$(OBJ)

REF_SOFT_X11_OBJS = \
	$(BUILDDIR)/ref_soft/rw_x11$(OBJ)

$(BUILDDIR)/r_soft.$(SHLIBEXT) : $(REF_SOFT_OBJS) $(REF_SOFT_SVGA_OBJS) r_soft.def
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(REF_SOFT_OBJS) \
		$(REF_SOFT_SVGA_OBJS) r_soft.def

$(BUILDDIR)/r_softx.$(SHLIBEXT) : $(REF_SOFT_OBJS) $(REF_SOFT_X11_OBJS) r_softx.def
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(REF_SOFT_OBJS) \
		$(REF_SOFT_X11_OBJS) $(XLDFLAGS) r_softx.def

$(BUILDDIR)/ref_soft/r_aclip$(OBJ) :      $(REF_SOFT_DIR)/r_aclip.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_alias$(OBJ) :      $(REF_SOFT_DIR)/r_alias.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_bsp$(OBJ) :        $(REF_SOFT_DIR)/r_bsp.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_draw$(OBJ) :       $(REF_SOFT_DIR)/r_draw.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_edge$(OBJ) :       $(REF_SOFT_DIR)/r_edge.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_image$(OBJ) :      $(REF_SOFT_DIR)/r_image.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_light$(OBJ) :      $(REF_SOFT_DIR)/r_light.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_main$(OBJ) :       $(REF_SOFT_DIR)/r_main.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_misc$(OBJ) :       $(REF_SOFT_DIR)/r_misc.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_model$(OBJ) :      $(REF_SOFT_DIR)/r_model.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_part$(OBJ) :       $(REF_SOFT_DIR)/r_part.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_poly$(OBJ) :       $(REF_SOFT_DIR)/r_poly.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_polyse$(OBJ) :     $(REF_SOFT_DIR)/r_polyse.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_rast$(OBJ) :       $(REF_SOFT_DIR)/r_rast.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_scan$(OBJ) :       $(REF_SOFT_DIR)/r_scan.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_sprite$(OBJ) :     $(REF_SOFT_DIR)/r_sprite.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_surf$(OBJ) :       $(REF_SOFT_DIR)/r_surf.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/r_aclipa$(OBJ) :     $(LINUX_DIR)/r_aclipa.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/r_draw16$(OBJ) :     $(LINUX_DIR)/r_draw16.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/r_drawa$(OBJ) :      $(LINUX_DIR)/r_drawa.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/r_edgea$(OBJ) :      $(LINUX_DIR)/r_edgea.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/r_scana$(OBJ) :      $(LINUX_DIR)/r_scana.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/r_spr8$(OBJ) :       $(LINUX_DIR)/r_spr8.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/r_surf8$(OBJ) :      $(LINUX_DIR)/r_surf8.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/math$(OBJ) :         $(LINUX_DIR)/math.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/d_polysa$(OBJ) :     $(LINUX_DIR)/d_polysa.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/r_varsa$(OBJ) :      $(LINUX_DIR)/r_varsa.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/sys_dosa$(OBJ) :     $(LINUX_DIR)/sys_dosa.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/q_shared$(OBJ) :     $(GAME_DIR)/q_shared.c
	$(DO_SHLIB_O0_CC)

$(BUILDDIR)/ref_soft/q_shlinux$(OBJ) :    $(LINUX_DIR)/q_shlinux.c
	$(DO_SHLIB_O_CC)

$(BUILDDIR)/ref_soft/glob$(OBJ) :         $(LINUX_DIR)/glob.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/vregset$(OBJ) :   $(OS2_DIR)/vregset.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/d_copy$(OBJ) :       $(LINUX_DIR)/d_copy.s
	$(DO_SHLIB_AS)

$(BUILDDIR)/ref_soft/in_os2$(OBJ) : $(OS2_DIR)/in_os2.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/kbd_os2$(OBJ) : $(OS2_DIR)/kbd_os2.c
	$(DO_SHLIB_CC)

$(BUILDDIR)/ref_soft/rw_os2$(OBJ) :       $(OS2_DIR)/rw_os2.c
	$(DO_SHLIB_CC) $(XCFLAGS)

$(BUILDDIR)/ref_soft/rw_x11$(OBJ) :       $(LINUX_DIR)/rw_x11.c
	$(DO_SHLIB_CC) $(XCFLAGS)

#############################################################################
# REF_GL
#############################################################################

REF_GL_OBJS = \
	$(BUILDDIR)/ref_gl/gl_draw$(OBJ) \
	$(BUILDDIR)/ref_gl/gl_image$(OBJ) \
	$(BUILDDIR)/ref_gl/gl_light$(OBJ) \
	$(BUILDDIR)/ref_gl/gl_mesh$(OBJ) \
	$(BUILDDIR)/ref_gl/gl_model$(OBJ) \
	$(BUILDDIR)/ref_gl/gl_rmain$(OBJ) \
	$(BUILDDIR)/ref_gl/gl_rmisc$(OBJ) \
	$(BUILDDIR)/ref_gl/gl_rsurf$(OBJ) \
	$(BUILDDIR)/ref_gl/gl_warp$(OBJ) \
	\
	$(BUILDDIR)/ref_gl/qgl_linux$(OBJ) \
	$(BUILDDIR)/ref_gl/q_shared$(OBJ) \
	$(BUILDDIR)/ref_gl/q_shlinux$(OBJ) \
	$(BUILDDIR)/ref_gl/glob$(OBJ)

# TTimo: taking out Mesa
REF_GL_FXMESA_OBJS = \
	$(BUILDDIR)/ref_gl/rw_in_svgalib$(OBJ)

#REF_GL_FXMESA_OBJS = \
#	$(BUILDDIR)/ref_gl/gl_fxmesa$(OBJ) \
#	$(BUILDDIR)/ref_gl/rw_in_svgalib$(OBJ)

REF_GL_GLX_OBJS = \
	$(BUILDDIR)/ref_gl/gl_glx$(OBJ)

$(BUILDDIR)/ref_gl.$(SHLIBEXT) : $(REF_GL_OBJS) $(REF_GL_FXMESA_OBJS)
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(REF_GL_OBJS) $(REF_GL_FXMESA_OBJS) $(GLLDFLAGS)

$(BUILDDIR)/ref_glx.$(SHLIBEXT) : $(REF_GL_OBJS) $(REF_GL_GLX_OBJS)
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(REF_GL_OBJS) $(REF_GL_GLX_OBJS) $(GLXLDFLAGS)

$(BUILDDIR)/ref_gl/gl_draw$(OBJ) :        $(REF_GL_DIR)/gl_draw.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_image$(OBJ) :       $(REF_GL_DIR)/gl_image.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_light$(OBJ) :       $(REF_GL_DIR)/gl_light.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_mesh$(OBJ) :        $(REF_GL_DIR)/gl_mesh.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_model$(OBJ) :       $(REF_GL_DIR)/gl_model.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_rmain$(OBJ) :       $(REF_GL_DIR)/gl_rmain.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_rmisc$(OBJ) :       $(REF_GL_DIR)/gl_rmisc.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_rsurf$(OBJ) :       $(REF_GL_DIR)/gl_rsurf.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_warp$(OBJ) :        $(REF_GL_DIR)/gl_warp.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/qgl_linux$(OBJ) :      $(LINUX_DIR)/qgl_linux.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_fxmesa$(OBJ) :      $(LINUX_DIR)/gl_fxmesa.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/gl_glx$(OBJ) :      $(LINUX_DIR)/gl_glx.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/rw_in_svgalib$(OBJ) :  $(LINUX_DIR)/rw_in_svgalib.c
	$(DO_GL_SHLIB_CC)

$(BUILDDIR)/ref_gl/q_shared$(OBJ) :       $(GAME_DIR)/q_shared.c
	$(DO_SHLIB_O0_CC)

$(BUILDDIR)/ref_gl/q_shlinux$(OBJ) :      $(LINUX_DIR)/q_shlinux.c
	$(DO_GL_SHLIB_O_CC)

$(BUILDDIR)/ref_gl/glob$(OBJ) :           $(LINUX_DIR)/glob.c
	$(DO_GL_SHLIB_CC)

#############################################################################
# RPM
#############################################################################

# Make RPMs.  You need to be root to make this work
RPMROOT=/usr/src/redhat
RPM = rpm
RPMFLAGS = -bb
INSTALLDIR = /usr/local/games/quake2
TDFXGL_DIR = /home/zoid/3dfxgl
TMPDIR = e:/temp

ifeq ($(ARCH),axp)

RPMDIR = $(TMPDIR)/q2ded-$(VERSION_FN)
DESTDIR= $(RPMDIR)/$(INSTALLDIR)

rpm: quake2.axp.spec
	touch $(RPMROOT)/SOURCES/q2ded-$(VERSION_FN).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	$(MAKE) copyfiles COPYDIR=$(DESTDIR)
	cp $(MOUNT_DIR)/linux/quake2.gif $(RPMROOT)/SOURCES/.
	cp quake2.axp.spec $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) quake2.axp.spec
	rm -rf $(RPMDIR)
	mv $(RPMROOT)/RPMS/$(RPMARCH)/q2ded-$(VERSION_FN)-$(RPM_RELEASE).$(RPMARCH).rpm archives/.

tar:
	if [ ! -d archives ];then mkdir archives;fi
	$(MAKE) copyfiles COPYDIR=$(RPMDIR)
	cd $(RPMDIR); tar czvf q2ded-$(VERSION_FN)-$(RPMARCH)-unknown-linux2.0.tar.gz *
	mv $(RPMDIR)/*.tar.gz archives/.
	rm -rf $(RPMDIR)

copyfiles:
	-mkdirhier $(COPYDIR)
	cp $(BUILD_RELEASE_DIR)/q2ded $(COPYDIR)
	strip $(COPYDIR)/q2ded
	chmod 755 $(COPYDIR)/q2ded
	-mkdir $(COPYDIR)/baseq2
	chmod 755 $(COPYDIR)/baseq2
	cp $(BUILD_RELEASE_DIR)/game$(GAMENAME).$(SHLIBEXT) $(COPYDIR)/baseq2
	chmod 755 $(COPYDIR)/baseq2/game$(GAMENAME).$(SHLIBEXT)
	-mkdir $(COPYDIR)/ctf
	chmod 755 $(COPYDIR)/ctf
	cp $(BUILD_RELEASE_DIR)/ctf/game$(GAMENAME).$(SHLIBEXT) $(COPYDIR)/ctf
	chmod 755 $(COPYDIR)/ctf/game$(GAMENAME).$(SHLIBEXT)
	-mkdir $(COPYDIR)/xatrix
	chmod 755 $(COPYDIR)/xatrix
	cp $(BUILD_RELEASE_DIR)/xatrix/game$(GAMENAME).$(SHLIBEXT) $(COPYDIR)/xatrix
	chmod 755 $(COPYDIR)/xatrix/game$(GAMENAME).$(SHLIBEXT)
	-mkdir $(COPYDIR)/rogue
	chmod 755 $(COPYDIR)/rogue
	cp $(BUILD_RELEASE_DIR)/rogue/game$(GAMENAME).$(SHLIBEXT) $(COPYDIR)/rogue
	chmod 755 $(COPYDIR)/rogue/game$(GAMENAME).$(SHLIBEXT)
	cp $(MOUNT_DIR)/linux/readme.axp $(COPYDIR)/README
	cp $(MOUNT_DIR)/readme.txt $(COPYDIR)
	cp $(MOUNT_DIR)/$(VERSION)_Changes.txt $(COPYDIR)


quake2.axp.spec : $(MOUNT_DIR)/linux/quake2.axp.spec.sh Makefile
	sh $< $(VERSION_FN) $(RPM_RELEASE) $(ARCH) $(INSTALLDIR) > $@

else

# rpm-quake2-patch
rpm:   rpm-quake2 rpm-quake2-data rpm-quake2-video \
		rpm-quake2-xatrix rpm-quake2-xatrix-video \
		rpm-quake2-rogue rpm-quake2-rogue-video \
		rpm-quake2-ctf

PATCHDIR = $(TMPDIR)/quake2-patch-$(VERSION_FN)
rpm-quake2-patch: quake2-patch.spec
	touch $(RPMROOT)/SOURCES/quake2-patch-$(VERSION_FN).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	$(MAKE) copyfiles COPYDIR=$(PATCHDIR)/$(INSTALLDIR)
	-mkdir $(RPMDIR)/etc
	cp $(MOUNT_DIR)/linux/quake2.conf $(PATCHDIR)/etc/quake2.conf
	cp $(MOUNT_DIR)/linux/quake2.gif $(RPMROOT)/SOURCES/.
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(PATCHDIR)
	mv $(RPMROOT)/RPMS/$(ARCH)/quake2-$(VERSION_FN)-$(RPM_RELEASE).$(ARCH).rpm archives/.

QUAKE2DIR = $(TMPDIR)/quake2-$(VERSION_FN)
QUAKE2INSTDIR = $(TMPDIR)/quake2-$(VERSION_FN)/$(INSTALLDIR)
rpm-quake2: quake2.spec
	touch $(RPMROOT)/SOURCES/quake2-$(VERSION_FN).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	-mkdirhier $(QUAKE2INSTDIR)
	cp $(BUILD_RELEASE_DIR)/quake2 $(QUAKE2INSTDIR)/quake2
	strip $(QUAKE2INSTDIR)/quake2
	-mkdir $(QUAKE2INSTDIR)/baseq2
	chmod 1777 $(QUAKE2INSTDIR)/baseq2
	cp $(BUILD_RELEASE_DIR)/game$(GAMENAME).$(SHLIBEXT) $(QUAKE2INSTDIR)/baseq2
	cp $(BUILD_RELEASE_DIR)/ref_soft.$(SHLIBEXT)  $(QUAKE2INSTDIR)
	cp $(BUILD_RELEASE_DIR)/ref_softx.$(SHLIBEXT) $(QUAKE2INSTDIR)
	cp $(BUILD_RELEASE_DIR)/ref_gl.$(SHLIBEXT) $(QUAKE2INSTDIR)
	cp $(BUILD_RELEASE_DIR)/ref_glx.$(SHLIBEXT) $(QUAKE2INSTDIR)
	-mkdir $(QUAKE2INSTDIR)/ctf
	chmod 1777 $(QUAKE2INSTDIR)/ctf
	cp $(BUILD_RELEASE_DIR)/ctf/game$(GAMENAME).$(SHLIBEXT) $(QUAKE2INSTDIR)/ctf
	-mkdir $(QUAKE2INSTDIR)/xatrix
	chmod 1777 $(QUAKE2INSTDIR)/xatrix
	cp $(BUILD_RELEASE_DIR)/xatrix/game$(GAMENAME).$(SHLIBEXT) $(QUAKE2INSTDIR)/xatrix
	-mkdir $(QUAKE2INSTDIR)/rogue
	chmod 1777 $(QUAKE2INSTDIR)/rogue
	cp $(BUILD_RELEASE_DIR)/rogue/game$(GAMENAME).$(SHLIBEXT) $(QUAKE2INSTDIR)/rogue
	-mkdirhier $(QUAKE2DIR)/usr/lib
	cp $(TDFXGL_DIR)/release$(ARCH)$(GLIBC)/lib3dfxgl.so $(QUAKE2DIR)/usr/lib/lib3dfxgl.so
	cp $(MESA_DIR)/lib/libMesaGL.so.2.6 $(QUAKE2DIR)/usr/lib/libMesaGL.so.2.6
	cp $(MOUNT_DIR)/linux/README $(QUAKE2INSTDIR)
	cp $(MOUNT_DIR)/readme.txt $(QUAKE2INSTDIR)
	-mkdir $(QUAKE2DIR)/etc
	cp $(MOUNT_DIR)/linux/quake2.conf $(QUAKE2DIR)/etc/quake2.conf
	cp $(MOUNT_DIR)/linux/quake2.gif $(RPMROOT)/SOURCES/.
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(QUAKE2DIR)
	mv $(RPMROOT)/RPMS/$(ARCH)/quake2-$(VERSION_FN)-$(RPM_RELEASE).$(ARCH).rpm archives/.

# rpm-quake2-patch: quake2-patch.spec

QUAKE2DATADIR = $(TMPDIR)/quake2-data-$(VERSION)/$(INSTALLDIR)
rpm-quake2-data: quake2-data.spec
	touch $(RPMROOT)/SOURCES/quake2-data-$(VERSION).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	-mkdirhier $(QUAKE2DATADIR)/baseq2
	-mkdirhier $(QUAKE2DATADIR)/baseq2/players
	-mkdirhier $(QUAKE2DATADIR)/baseq2/players/cyborg
	-mkdirhier $(QUAKE2DATADIR)/baseq2/players/female
	-mkdirhier $(QUAKE2DATADIR)/baseq2/players/male
	cp $(QUAKE2_DIR)/baseq2/pak0.pak							 	 $(QUAKE2DATADIR)/baseq2/pak0.pak                         
	cp $(QUAKE2_DIR)/baseq2/pak1.pak                                 $(QUAKE2DATADIR)/baseq2/pak1.pak                         
	cp $(QUAKE2_DIR)/baseq2/pak2.pak                                 $(QUAKE2DATADIR)/baseq2/pak2.pak                         
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/a_grenades.md2            $(QUAKE2DATADIR)/baseq2/players/cyborg/a_grenades.md2    
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_bfg.md2                 $(QUAKE2DATADIR)/baseq2/players/cyborg/w_bfg.md2         
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_blaster.md2             $(QUAKE2DATADIR)/baseq2/players/cyborg/w_blaster.md2     
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_chainfist.md2           $(QUAKE2DATADIR)/baseq2/players/cyborg/w_chainfist.md2   
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_chaingun.md2            $(QUAKE2DATADIR)/baseq2/players/cyborg/w_chaingun.md2    
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_disrupt.md2             $(QUAKE2DATADIR)/baseq2/players/cyborg/w_disrupt.md2     
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_etfrifle.md2            $(QUAKE2DATADIR)/baseq2/players/cyborg/w_etfrifle.md2    
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_glauncher.md2           $(QUAKE2DATADIR)/baseq2/players/cyborg/w_glauncher.md2   
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_grapple.md2             $(QUAKE2DATADIR)/baseq2/players/cyborg/w_grapple.md2     
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_hyperblaster.md2        $(QUAKE2DATADIR)/baseq2/players/cyborg/w_hyperblaster.md2
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_machinegun.md2          $(QUAKE2DATADIR)/baseq2/players/cyborg/w_machinegun.md2  
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_phalanx.md2             $(QUAKE2DATADIR)/baseq2/players/cyborg/w_phalanx.md2     
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_plasma.md2              $(QUAKE2DATADIR)/baseq2/players/cyborg/w_plasma.md2      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_plauncher.md2           $(QUAKE2DATADIR)/baseq2/players/cyborg/w_plauncher.md2   
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_railgun.md2             $(QUAKE2DATADIR)/baseq2/players/cyborg/w_railgun.md2     
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_ripper.md2              $(QUAKE2DATADIR)/baseq2/players/cyborg/w_ripper.md2      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_rlauncher.md2           $(QUAKE2DATADIR)/baseq2/players/cyborg/w_rlauncher.md2   
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_shotgun.md2             $(QUAKE2DATADIR)/baseq2/players/cyborg/w_shotgun.md2     
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/w_sshotgun.md2            $(QUAKE2DATADIR)/baseq2/players/cyborg/w_sshotgun.md2    
	cp $(QUAKE2_DIR)/baseq2/players/female/a_grenades.md2            $(QUAKE2DATADIR)/baseq2/players/female/a_grenades.md2    
	cp $(QUAKE2_DIR)/baseq2/players/female/w_bfg.md2                 $(QUAKE2DATADIR)/baseq2/players/female/w_bfg.md2         
	cp $(QUAKE2_DIR)/baseq2/players/female/w_blaster.md2             $(QUAKE2DATADIR)/baseq2/players/female/w_blaster.md2     
	cp $(QUAKE2_DIR)/baseq2/players/female/w_chainfist.md2           $(QUAKE2DATADIR)/baseq2/players/female/w_chainfist.md2   
	cp $(QUAKE2_DIR)/baseq2/players/female/w_chaingun.md2            $(QUAKE2DATADIR)/baseq2/players/female/w_chaingun.md2    
	cp $(QUAKE2_DIR)/baseq2/players/female/w_disrupt.md2             $(QUAKE2DATADIR)/baseq2/players/female/w_disrupt.md2     
	cp $(QUAKE2_DIR)/baseq2/players/female/w_etfrifle.md2            $(QUAKE2DATADIR)/baseq2/players/female/w_etfrifle.md2    
	cp $(QUAKE2_DIR)/baseq2/players/female/w_glauncher.md2           $(QUAKE2DATADIR)/baseq2/players/female/w_glauncher.md2   
	cp $(QUAKE2_DIR)/baseq2/players/female/w_grapple.md2             $(QUAKE2DATADIR)/baseq2/players/female/w_grapple.md2     
	cp $(QUAKE2_DIR)/baseq2/players/female/w_hyperblaster.md2        $(QUAKE2DATADIR)/baseq2/players/female/w_hyperblaster.md2
	cp $(QUAKE2_DIR)/baseq2/players/female/w_machinegun.md2          $(QUAKE2DATADIR)/baseq2/players/female/w_machinegun.md2  
	cp $(QUAKE2_DIR)/baseq2/players/female/w_phalanx.md2             $(QUAKE2DATADIR)/baseq2/players/female/w_phalanx.md2     
	cp $(QUAKE2_DIR)/baseq2/players/female/w_plasma.md2              $(QUAKE2DATADIR)/baseq2/players/female/w_plasma.md2      
	cp $(QUAKE2_DIR)/baseq2/players/female/w_plauncher.md2           $(QUAKE2DATADIR)/baseq2/players/female/w_plauncher.md2   
	cp $(QUAKE2_DIR)/baseq2/players/female/w_railgun.md2             $(QUAKE2DATADIR)/baseq2/players/female/w_railgun.md2     
	cp $(QUAKE2_DIR)/baseq2/players/female/w_ripper.md2              $(QUAKE2DATADIR)/baseq2/players/female/w_ripper.md2      
	cp $(QUAKE2_DIR)/baseq2/players/female/w_rlauncher.md2           $(QUAKE2DATADIR)/baseq2/players/female/w_rlauncher.md2   
	cp $(QUAKE2_DIR)/baseq2/players/female/w_shotgun.md2             $(QUAKE2DATADIR)/baseq2/players/female/w_shotgun.md2     
	cp $(QUAKE2_DIR)/baseq2/players/female/w_sshotgun.md2            $(QUAKE2DATADIR)/baseq2/players/female/w_sshotgun.md2    
	cp $(QUAKE2_DIR)/baseq2/players/male/a_grenades.md2              $(QUAKE2DATADIR)/baseq2/players/male/a_grenades.md2      
	cp $(QUAKE2_DIR)/baseq2/players/male/w_bfg.md2                   $(QUAKE2DATADIR)/baseq2/players/male/w_bfg.md2           
	cp $(QUAKE2_DIR)/baseq2/players/male/w_blaster.md2               $(QUAKE2DATADIR)/baseq2/players/male/w_blaster.md2       
	cp $(QUAKE2_DIR)/baseq2/players/male/w_chainfist.md2             $(QUAKE2DATADIR)/baseq2/players/male/w_chainfist.md2     
	cp $(QUAKE2_DIR)/baseq2/players/male/w_chaingun.md2              $(QUAKE2DATADIR)/baseq2/players/male/w_chaingun.md2      
	cp $(QUAKE2_DIR)/baseq2/players/male/w_disrupt.md2               $(QUAKE2DATADIR)/baseq2/players/male/w_disrupt.md2       
	cp $(QUAKE2_DIR)/baseq2/players/male/w_etfrifle.md2              $(QUAKE2DATADIR)/baseq2/players/male/w_etfrifle.md2      
	cp $(QUAKE2_DIR)/baseq2/players/male/w_glauncher.md2             $(QUAKE2DATADIR)/baseq2/players/male/w_glauncher.md2     
	cp $(QUAKE2_DIR)/baseq2/players/male/w_grapple.md2               $(QUAKE2DATADIR)/baseq2/players/male/w_grapple.md2       
	cp $(QUAKE2_DIR)/baseq2/players/male/w_hyperblaster.md2          $(QUAKE2DATADIR)/baseq2/players/male/w_hyperblaster.md2  
	cp $(QUAKE2_DIR)/baseq2/players/male/w_machinegun.md2            $(QUAKE2DATADIR)/baseq2/players/male/w_machinegun.md2    
	cp $(QUAKE2_DIR)/baseq2/players/male/w_phalanx.md2               $(QUAKE2DATADIR)/baseq2/players/male/w_phalanx.md2       
	cp $(QUAKE2_DIR)/baseq2/players/male/w_plasma.md2                $(QUAKE2DATADIR)/baseq2/players/male/w_plasma.md2        
	cp $(QUAKE2_DIR)/baseq2/players/male/w_plauncher.md2             $(QUAKE2DATADIR)/baseq2/players/male/w_plauncher.md2     
	cp $(QUAKE2_DIR)/baseq2/players/male/w_railgun.md2               $(QUAKE2DATADIR)/baseq2/players/male/w_railgun.md2       
	cp $(QUAKE2_DIR)/baseq2/players/male/w_ripper.md2                $(QUAKE2DATADIR)/baseq2/players/male/w_ripper.md2        
	cp $(QUAKE2_DIR)/baseq2/players/male/w_rlauncher.md2             $(QUAKE2DATADIR)/baseq2/players/male/w_rlauncher.md2     
	cp $(QUAKE2_DIR)/baseq2/players/male/w_shotgun.md2               $(QUAKE2DATADIR)/baseq2/players/male/w_shotgun.md2       
	cp $(QUAKE2_DIR)/baseq2/players/male/w_sshotgun.md2              $(QUAKE2DATADIR)/baseq2/players/male/w_sshotgun.md2      
	cp $(QUAKE2_DIR)/baseq2/players/female/athena.pcx                $(QUAKE2DATADIR)/baseq2/players/female/athena.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/female/athena_i.pcx              $(QUAKE2DATADIR)/baseq2/players/female/athena_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/female/brianna.pcx               $(QUAKE2DATADIR)/baseq2/players/female/brianna.pcx       
	cp $(QUAKE2_DIR)/baseq2/players/female/brianna_i.pcx             $(QUAKE2DATADIR)/baseq2/players/female/brianna_i.pcx     
	cp $(QUAKE2_DIR)/baseq2/players/female/cobalt.pcx                $(QUAKE2DATADIR)/baseq2/players/female/cobalt.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/female/cobalt_i.pcx              $(QUAKE2DATADIR)/baseq2/players/female/cobalt_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/female/ensign.pcx                $(QUAKE2DATADIR)/baseq2/players/female/ensign.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/female/ensign_i.pcx              $(QUAKE2DATADIR)/baseq2/players/female/ensign_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/female/jezebel.pcx               $(QUAKE2DATADIR)/baseq2/players/female/jezebel.pcx       
	cp $(QUAKE2_DIR)/baseq2/players/female/jezebel_i.pcx             $(QUAKE2DATADIR)/baseq2/players/female/jezebel_i.pcx     
	cp $(QUAKE2_DIR)/baseq2/players/female/jungle.pcx                $(QUAKE2DATADIR)/baseq2/players/female/jungle.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/female/jungle_i.pcx              $(QUAKE2DATADIR)/baseq2/players/female/jungle_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/female/lotus.pcx                 $(QUAKE2DATADIR)/baseq2/players/female/lotus.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/female/lotus_i.pcx               $(QUAKE2DATADIR)/baseq2/players/female/lotus_i.pcx       
	cp $(QUAKE2_DIR)/baseq2/players/female/stiletto.pcx              $(QUAKE2DATADIR)/baseq2/players/female/stiletto.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/female/stiletto_i.pcx            $(QUAKE2DATADIR)/baseq2/players/female/stiletto_i.pcx    
	cp $(QUAKE2_DIR)/baseq2/players/female/tris.md2                  $(QUAKE2DATADIR)/baseq2/players/female/tris.md2          
	cp $(QUAKE2_DIR)/baseq2/players/female/venus.pcx                 $(QUAKE2DATADIR)/baseq2/players/female/venus.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/female/venus_i.pcx               $(QUAKE2DATADIR)/baseq2/players/female/venus_i.pcx       
	cp $(QUAKE2_DIR)/baseq2/players/female/voodoo.pcx                $(QUAKE2DATADIR)/baseq2/players/female/voodoo.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/female/voodoo_i.pcx              $(QUAKE2DATADIR)/baseq2/players/female/voodoo_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/female/weapon.md2                $(QUAKE2DATADIR)/baseq2/players/female/weapon.md2        
	cp $(QUAKE2_DIR)/baseq2/players/female/weapon.pcx                $(QUAKE2DATADIR)/baseq2/players/female/weapon.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/male/cipher.pcx                  $(QUAKE2DATADIR)/baseq2/players/male/cipher.pcx          
	cp $(QUAKE2_DIR)/baseq2/players/male/cipher_i.pcx                $(QUAKE2DATADIR)/baseq2/players/male/cipher_i.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/male/claymore.pcx                $(QUAKE2DATADIR)/baseq2/players/male/claymore.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/male/claymore_i.pcx              $(QUAKE2DATADIR)/baseq2/players/male/claymore_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/male/flak.pcx                    $(QUAKE2DATADIR)/baseq2/players/male/flak.pcx            
	cp $(QUAKE2_DIR)/baseq2/players/male/flak_i.pcx                  $(QUAKE2DATADIR)/baseq2/players/male/flak_i.pcx          
	cp $(QUAKE2_DIR)/baseq2/players/male/grunt.pcx                   $(QUAKE2DATADIR)/baseq2/players/male/grunt.pcx           
	cp $(QUAKE2_DIR)/baseq2/players/male/grunt_i.pcx                 $(QUAKE2DATADIR)/baseq2/players/male/grunt_i.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/male/howitzer.pcx                $(QUAKE2DATADIR)/baseq2/players/male/howitzer.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/male/howitzer_i.pcx              $(QUAKE2DATADIR)/baseq2/players/male/howitzer_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/male/major.pcx                   $(QUAKE2DATADIR)/baseq2/players/male/major.pcx           
	cp $(QUAKE2_DIR)/baseq2/players/male/major_i.pcx                 $(QUAKE2DATADIR)/baseq2/players/male/major_i.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/male/nightops.pcx                $(QUAKE2DATADIR)/baseq2/players/male/nightops.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/male/nightops_i.pcx              $(QUAKE2DATADIR)/baseq2/players/male/nightops_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/male/pointman.pcx                $(QUAKE2DATADIR)/baseq2/players/male/pointman.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/male/pointman_i.pcx              $(QUAKE2DATADIR)/baseq2/players/male/pointman_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/male/psycho.pcx                  $(QUAKE2DATADIR)/baseq2/players/male/psycho.pcx          
	cp $(QUAKE2_DIR)/baseq2/players/male/psycho_i.pcx                $(QUAKE2DATADIR)/baseq2/players/male/psycho_i.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/male/rampage.pcx                 $(QUAKE2DATADIR)/baseq2/players/male/rampage.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/male/rampage_i.pcx               $(QUAKE2DATADIR)/baseq2/players/male/rampage_i.pcx       
	cp $(QUAKE2_DIR)/baseq2/players/male/razor.pcx                   $(QUAKE2DATADIR)/baseq2/players/male/razor.pcx           
	cp $(QUAKE2_DIR)/baseq2/players/male/razor_i.pcx                 $(QUAKE2DATADIR)/baseq2/players/male/razor_i.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/male/recon.pcx                   $(QUAKE2DATADIR)/baseq2/players/male/recon.pcx           
	cp $(QUAKE2_DIR)/baseq2/players/male/recon_i.pcx                 $(QUAKE2DATADIR)/baseq2/players/male/recon_i.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/male/scout.pcx                   $(QUAKE2DATADIR)/baseq2/players/male/scout.pcx           
	cp $(QUAKE2_DIR)/baseq2/players/male/scout_i.pcx                 $(QUAKE2DATADIR)/baseq2/players/male/scout_i.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/male/sniper.pcx                  $(QUAKE2DATADIR)/baseq2/players/male/sniper.pcx          
	cp $(QUAKE2_DIR)/baseq2/players/male/sniper_i.pcx                $(QUAKE2DATADIR)/baseq2/players/male/sniper_i.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/male/tris.md2                    $(QUAKE2DATADIR)/baseq2/players/male/tris.md2            
	cp $(QUAKE2_DIR)/baseq2/players/male/viper.pcx                   $(QUAKE2DATADIR)/baseq2/players/male/viper.pcx           
	cp $(QUAKE2_DIR)/baseq2/players/male/viper_i.pcx                 $(QUAKE2DATADIR)/baseq2/players/male/viper_i.pcx         
	cp $(QUAKE2_DIR)/baseq2/players/male/weapon.md2                  $(QUAKE2DATADIR)/baseq2/players/male/weapon.md2          
	cp $(QUAKE2_DIR)/baseq2/players/male/weapon.pcx                  $(QUAKE2DATADIR)/baseq2/players/male/weapon.pcx          
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/bump1.wav                 $(QUAKE2DATADIR)/baseq2/players/cyborg/bump1.wav         
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/death1.wav                $(QUAKE2DATADIR)/baseq2/players/cyborg/death1.wav        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/death2.wav                $(QUAKE2DATADIR)/baseq2/players/cyborg/death2.wav        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/death3.wav                $(QUAKE2DATADIR)/baseq2/players/cyborg/death3.wav        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/death4.wav                $(QUAKE2DATADIR)/baseq2/players/cyborg/death4.wav        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/drown1.wav                $(QUAKE2DATADIR)/baseq2/players/cyborg/drown1.wav        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/fall1.wav                 $(QUAKE2DATADIR)/baseq2/players/cyborg/fall1.wav         
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/fall2.wav                 $(QUAKE2DATADIR)/baseq2/players/cyborg/fall2.wav         
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/gurp1.wav                 $(QUAKE2DATADIR)/baseq2/players/cyborg/gurp1.wav         
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/gurp2.wav                 $(QUAKE2DATADIR)/baseq2/players/cyborg/gurp2.wav         
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/jump1.wav                 $(QUAKE2DATADIR)/baseq2/players/cyborg/jump1.wav         
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/oni911.pcx                $(QUAKE2DATADIR)/baseq2/players/cyborg/oni911.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/oni911_i.pcx              $(QUAKE2DATADIR)/baseq2/players/cyborg/oni911_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/pain100_1.wav             $(QUAKE2DATADIR)/baseq2/players/cyborg/pain100_1.wav     
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/pain100_2.wav             $(QUAKE2DATADIR)/baseq2/players/cyborg/pain100_2.wav     
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/pain25_1.wav              $(QUAKE2DATADIR)/baseq2/players/cyborg/pain25_1.wav      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/pain25_2.wav              $(QUAKE2DATADIR)/baseq2/players/cyborg/pain25_2.wav      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/pain50_1.wav              $(QUAKE2DATADIR)/baseq2/players/cyborg/pain50_1.wav      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/pain50_2.wav              $(QUAKE2DATADIR)/baseq2/players/cyborg/pain50_2.wav      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/pain75_1.wav              $(QUAKE2DATADIR)/baseq2/players/cyborg/pain75_1.wav      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/pain75_2.wav              $(QUAKE2DATADIR)/baseq2/players/cyborg/pain75_2.wav      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/ps9000.pcx                $(QUAKE2DATADIR)/baseq2/players/cyborg/ps9000.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/ps9000_i.pcx              $(QUAKE2DATADIR)/baseq2/players/cyborg/ps9000_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/tris.md2                  $(QUAKE2DATADIR)/baseq2/players/cyborg/tris.md2          
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/tyr574.pcx                $(QUAKE2DATADIR)/baseq2/players/cyborg/tyr574.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/tyr574_i.pcx              $(QUAKE2DATADIR)/baseq2/players/cyborg/tyr574_i.pcx      
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/weapon.md2                $(QUAKE2DATADIR)/baseq2/players/cyborg/weapon.md2        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/weapon.pcx                $(QUAKE2DATADIR)/baseq2/players/cyborg/weapon.pcx        
	cp $(QUAKE2_DIR)/baseq2/players/cyborg/weapon.pcx.pcx            $(QUAKE2DATADIR)/baseq2/players/cyborg/weapon.pcx.pcx    
	cp -r $(QUAKE2_DIR)/docs $(QUAKE2DATADIR)/docs
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(TMPDIR)/quake2-data-$(VERSION)
	mv $(RPMROOT)/RPMS/$(NOARCH)/quake2-data-$(VERSION)-$(RPM_RELEASE).$(NOARCH).rpm archives/.

QUAKE2VIDEODIR = $(TMPDIR)/quake2-video-$(VERSION)/$(INSTALLDIR)
rpm-quake2-video: quake2-video.spec
	touch $(RPMROOT)/SOURCES/quake2-video-$(VERSION).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	-mkdirhier $(QUAKE2VIDEODIR)/baseq2
	-mkdirhier $(QUAKE2VIDEODIR)/baseq2/video
	cp $(QUAKE2_DIR)/baseq2/video/end.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/eou1_.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/eou2_.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/eou3_.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/eou4_.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/eou5_.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/eou6_.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/eou7_.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/eou8_.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/idlog.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $(QUAKE2_DIR)/baseq2/video/ntro.cin		$(QUAKE2VIDEODIR)/baseq2/video/.
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(TMPDIR)/quake2-video-$(VERSION)
	mv $(RPMROOT)/RPMS/$(NOARCH)/quake2-video-$(VERSION)-$(RPM_RELEASE).$(NOARCH).rpm archives/.

QUAKE2XATRIXDIR = $(TMPDIR)/quake2-xatrix-$(VERSION)/$(INSTALLDIR)
rpm-quake2-xatrix: quake2-xatrix.spec
	touch $(RPMROOT)/SOURCES/quake2-xatrix-$(VERSION).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	-mkdirhier $(QUAKE2XATRIXDIR)/xatrix/docs
	cp $(QUAKE2_DIR)/xatrix/pak0.pak			$(QUAKE2XATRIXDIR)/xatrix/.
	cp $(QUAKE2_DIR)/xatrix/docs/license.doc	$(QUAKE2XATRIXDIR)/xatrix/docs/.
	cp $(QUAKE2_DIR)/xatrix/docs/license.txt	$(QUAKE2XATRIXDIR)/xatrix/docs/.
	cp $(QUAKE2_DIR)/xatrix/docs/manual.doc		$(QUAKE2XATRIXDIR)/xatrix/docs/.
	cp $(QUAKE2_DIR)/xatrix/docs/manual.txt		$(QUAKE2XATRIXDIR)/xatrix/docs/.
	cp $(QUAKE2_DIR)/xatrix/docs/readme.htm		$(QUAKE2XATRIXDIR)/xatrix/docs/.
	cp $(QUAKE2_DIR)/xatrix/docs/readme.txt		$(QUAKE2XATRIXDIR)/xatrix/docs/.
	cp $(QUAKE2_DIR)/xatrix/docs/release.htm	$(QUAKE2XATRIXDIR)/xatrix/docs/.
	cp $(QUAKE2_DIR)/xatrix/docs/release.txt	$(QUAKE2XATRIXDIR)/xatrix/docs/.
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(TMPDIR)/quake2-xatrix-$(VERSION)
	mv $(RPMROOT)/RPMS/$(NOARCH)/quake2-xatrix-$(VERSION)-$(RPM_RELEASE).$(NOARCH).rpm archives/.

QUAKE2XATRIXVIDEODIR = $(TMPDIR)/quake2-xatrix-video-$(VERSION)/$(INSTALLDIR)
rpm-quake2-xatrix-video : quake2-xatrix-video.spec
	touch $(RPMROOT)/SOURCES/quake2-xatrix-video-$(VERSION).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	-mkdirhier $(QUAKE2XATRIXVIDEODIR)/xatrix/video
	cp $(QUAKE2_DIR)/xatrix/video/idlog.cin		$(QUAKE2XATRIXVIDEODIR)/xatrix/video/.
	cp $(QUAKE2_DIR)/xatrix/video/logo.cin		$(QUAKE2XATRIXVIDEODIR)/xatrix/video/.
	cp $(QUAKE2_DIR)/xatrix/video/xin.cin		$(QUAKE2XATRIXVIDEODIR)/xatrix/video/.
	cp $(QUAKE2_DIR)/xatrix/video/xout.cin		$(QUAKE2XATRIXVIDEODIR)/xatrix/video/.
	cp $(QUAKE2_DIR)/xatrix/video/xu1.cin		$(QUAKE2XATRIXVIDEODIR)/xatrix/video/.
	cp $(QUAKE2_DIR)/xatrix/video/xu2.cin		$(QUAKE2XATRIXVIDEODIR)/xatrix/video/.
	cp $(QUAKE2_DIR)/xatrix/video/xu3.cin		$(QUAKE2XATRIXVIDEODIR)/xatrix/video/.
	cp $(QUAKE2_DIR)/xatrix/video/xu4.cin		$(QUAKE2XATRIXVIDEODIR)/xatrix/video/.
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(TMPDIR)/quake2-xatrix-video-$(VERSION)
	mv $(RPMROOT)/RPMS/$(NOARCH)/quake2-xatrix-video-$(VERSION)-$(RPM_RELEASE).$(NOARCH).rpm archives/.

QUAKE2ROGUEDIR = $(TMPDIR)/quake2-rogue-$(VERSION)/$(INSTALLDIR)
rpm-quake2-rogue: quake2-rogue.spec
	touch $(RPMROOT)/SOURCES/quake2-rogue-$(VERSION).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	-mkdirhier $(QUAKE2ROGUEDIR)/rogue/docs
	cp $(QUAKE2_DIR)/rogue/pak0.pak				$(QUAKE2ROGUEDIR)/rogue/.
	cp $(QUAKE2_DIR)/rogue/docs/license.doc		$(QUAKE2ROGUEDIR)/rogue/docs/.
	cp $(QUAKE2_DIR)/rogue/docs/license.txt		$(QUAKE2ROGUEDIR)/rogue/docs/.
	cp $(QUAKE2_DIR)/rogue/docs/readme.htm		$(QUAKE2ROGUEDIR)/rogue/docs/.
	cp $(QUAKE2_DIR)/rogue/docs/readme.txt		$(QUAKE2ROGUEDIR)/rogue/docs/.
	cp $(QUAKE2_DIR)/rogue/docs/release.htm		$(QUAKE2ROGUEDIR)/rogue/docs/.
	cp $(QUAKE2_DIR)/rogue/docs/release.txt		$(QUAKE2ROGUEDIR)/rogue/docs/.
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(TMPDIR)/quake2-rogue-$(VERSION)
	mv $(RPMROOT)/RPMS/$(NOARCH)/quake2-rogue-$(VERSION)-$(RPM_RELEASE).$(NOARCH).rpm archives/.

QUAKE2ROGUEVIDEODIR = $(TMPDIR)/quake2-rogue-video-$(VERSION)/$(INSTALLDIR)
rpm-quake2-rogue-video: quake2-rogue-video.spec
	touch $(RPMROOT)/SOURCES/quake2-rogue-video-$(VERSION).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	-mkdirhier $(QUAKE2ROGUEVIDEODIR)/rogue/video
	cp $(QUAKE2_DIR)/rogue/video/logo.cin		$(QUAKE2ROGUEVIDEODIR)/rogue/video/.
	cp $(QUAKE2_DIR)/rogue/video/rend.cin		$(QUAKE2ROGUEVIDEODIR)/rogue/video/.
	cp $(QUAKE2_DIR)/rogue/video/reu1_.cin		$(QUAKE2ROGUEVIDEODIR)/rogue/video/.
	cp $(QUAKE2_DIR)/rogue/video/reu2_.cin		$(QUAKE2ROGUEVIDEODIR)/rogue/video/.
	cp $(QUAKE2_DIR)/rogue/video/reu3_.cin		$(QUAKE2ROGUEVIDEODIR)/rogue/video/.
	cp $(QUAKE2_DIR)/rogue/video/reu4_.cin		$(QUAKE2ROGUEVIDEODIR)/rogue/video/.
	cp $(QUAKE2_DIR)/rogue/video/rintro.cin		$(QUAKE2ROGUEVIDEODIR)/rogue/video/.
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(TMPDIR)/quake2-rogue-video-$(VERSION)
	mv $(RPMROOT)/RPMS/$(NOARCH)/quake2-rogue-video-$(VERSION)-$(RPM_RELEASE).$(NOARCH).rpm archives/.

QUAKE2CTFDIR = $(TMPDIR)/quake2-ctf-$(VERSION)/$(INSTALLDIR)
rpm-quake2-ctf: quake2-ctf.spec
	touch $(RPMROOT)/SOURCES/quake2-ctf-$(VERSION).tar.gz
	if [ ! -d archives ];then mkdir archives;fi
	-mkdirhier $(QUAKE2CTFDIR)/ctf/docs
	cp $(QUAKE2_DIR)/ctf/pak0.pak	$(QUAKE2CTFDIR)/ctf/.
	cp $(QUAKE2_DIR)/ctf/pak1.pak	$(QUAKE2CTFDIR)/ctf/.
	cp $(QUAKE2_DIR)/ctf/ctf2.ico	$(QUAKE2CTFDIR)/ctf/.
	cp $(QUAKE2_DIR)/ctf/readme.txt	$(QUAKE2CTFDIR)/ctf/.
	cp $(QUAKE2_DIR)/ctf/server.cfg	$(QUAKE2CTFDIR)/ctf/.
	cp $< $(RPMROOT)/SPECS/.
	cd $(RPMROOT)/SPECS; $(RPM) $(RPMFLAGS) $<
	rm -rf $(TMPDIR)/quake2-ctf-$(VERSION)
	mv $(RPMROOT)/RPMS/$(NOARCH)/quake2-ctf-$(VERSION)-$(RPM_RELEASE).$(NOARCH).rpm archives/.

TARDIR=$(TMPDIR)/tar
tar:
	if [ ! -d archives ];then mkdir archives;fi
	$(MAKE) copyfiles COPYDIR=$(TARDIR)
	cp $(MOUNT_DIR)/linux/quake2.conf $(TARDIR)/quake2.conf
	cd $(TARDIR); sh $(MOUNT_DIR)/linux/fixperms.sh
	cd $(TARDIR); tar czvf quake2-$(VERSION_FN)-$(ARCH)-unknown-linux2.0.tar.gz *
	mv $(TARDIR)/*.tar.gz archives/.
	rm -rf $(TARDIR)


copyfiles:
	-mkdirhier $(COPYDIR)
	cp $(BUILD_RELEASE_DIR)/quake2 $(COPYDIR)/quake2
	strip $(COPYDIR)/quake2
	-mkdir $(COPYDIR)/baseq2
#	cp -R $(VWEP_DIR)/baseq2 $(COPYDIR)/.
#	for x in `find $(COPYDIR)/baseq2 -type d`; do chmod 755 $$x;done
#	for x in `find $(COPYDIR)/baseq2 -type f`; do chmod 644 $$x;done
	chmod 1777 $(COPYDIR)/baseq2
	cp $(BUILD_RELEASE_DIR)/game$(GAMENAME).$(SHLIBEXT) $(COPYDIR)/baseq2
	cp $(BUILD_RELEASE_DIR)/ref_soft.$(SHLIBEXT)  $(COPYDIR)
	cp $(BUILD_RELEASE_DIR)/ref_softx.$(SHLIBEXT) $(COPYDIR)
	cp $(BUILD_RELEASE_DIR)/ref_gl.$(SHLIBEXT) $(COPYDIR)
	cp $(BUILD_RELEASE_DIR)/ref_glx.$(SHLIBEXT) $(COPYDIR)
#	-mkdir $(COPYDIR)/ctf
#	chmod 1777 $(COPYDIR)/ctf
#	cp $(BUILD_RELEASE_DIR)/ctf/game$(GAMENAME).$(SHLIBEXT) $(COPYDIR)/ctf
	-mkdir $(COPYDIR)/xatrix
	chmod 1777 $(COPYDIR)/xatrix
	cp $(BUILD_RELEASE_DIR)/xatrix/game$(GAMENAME).$(SHLIBEXT) $(COPYDIR)/xatrix
	-mkdir $(COPYDIR)/rogue
	chmod 1777 $(COPYDIR)/rogue
	cp $(BUILD_RELEASE_DIR)/rogue/game$(GAMENAME).$(SHLIBEXT) $(COPYDIR)/rogue
	cp $(TDFXGL_DIR)/release$(ARCH)$(GLIBC)/lib3dfxgl.so $(COPYDIR)
	cp $(MESA_DIR)/lib/libMesaGL.so.2.6 $(COPYDIR)
	cd $(COPYDIR); ln -sf libMesaGL.so.2.6 libMesaGL.so.2
	cd $(COPYDIR); ln -sf libMesaGL.so.2 libMesaGL.so
	cd $(COPYDIR); ln -sf libMesaGL.so libGL.so
	cp $(MOUNT_DIR)/linux/README $(COPYDIR)
	cp $(MOUNT_DIR)/readme.txt $(COPYDIR)
	cp $(MOUNT_DIR)/$(VERSION)_Changes.txt $(COPYDIR)

quake2.spec: $(MOUNT_DIR)/linux/quake2.spec.sh
	sh $< $(VERSION_FN) $(RPM_RELEASE) $(ARCH) $(INSTALLDIR) > $@

quake2-patch.spec: $(MOUNT_DIR)/linux/quake2-patch.spec.sh
	sh $< $(VERSION_FN) $(RPM_RELEASE) $(ARCH) $(INSTALLDIR) > $@

quake2-data.spec: $(MOUNT_DIR)/linux/quake2-data.spec.sh
	sh $< $(VERSION) $(RPM_RELEASE) $(NOARCH) $(INSTALLDIR) > $@

quake2-video.spec: $(MOUNT_DIR)/linux/quake2-video.spec.sh
	sh $< $(VERSION) $(RPM_RELEASE) $(NOARCH) $(INSTALLDIR) > $@

quake2-xatrix.spec: $(MOUNT_DIR)/linux/quake2-xatrix.spec.sh
	sh $< $(VERSION) $(RPM_RELEASE) $(NOARCH) $(INSTALLDIR) > $@

quake2-xatrix-video.spec: $(MOUNT_DIR)/linux/quake2-xatrix-video.spec.sh
	sh $< $(VERSION) $(RPM_RELEASE) $(NOARCH) $(INSTALLDIR) > $@

quake2-rogue.spec: $(MOUNT_DIR)/linux/quake2-rogue.spec.sh
	sh $< $(VERSION) $(RPM_RELEASE) $(NOARCH) $(INSTALLDIR) > $@

quake2-rogue-video.spec: $(MOUNT_DIR)/linux/quake2-rogue-video.spec.sh
	sh $< $(VERSION) $(RPM_RELEASE) $(NOARCH) $(INSTALLDIR) > $@

quake2-ctf.spec: $(MOUNT_DIR)/linux/quake2-ctf.spec.sh
	sh $< $(VERSION) $(RPM_RELEASE) $(NOARCH) $(INSTALLDIR) > $@


endif


#############################################################################
# MISC
#############################################################################

clean: clean-debug clean-release

clean-debug:
	$(MAKE) clean2 BUILDDIR=$(BUILD_DEBUG_DIR) CFLAGS="$(DEBUG_CFLAGS)"

clean-release:
	$(MAKE) clean2 BUILDDIR=$(BUILD_RELEASE_DIR) CFLAGS="$(DEBUG_CFLAGS)"

clean2:
	-rm -f \
	$(QUAKE2_OBJS) \
	$(Q2DED_OBJS) \
	$(QUAKE2_AS_OBJS) \
	$(GAME_OBJS) \
	$(CTF_OBJS) \
	$(XATRIX_OBJS) \
	$(ROGUE_OBJS) \
	$(REF_SOFT_OBJS) \
	$(REF_SOFT_SVGA_OBJS) \
	$(REF_SOFT_X11_OBJS) \
	$(REF_GL_OBJS) \
	$(REF_GL_FXMESA_OBJS) \
	$(REF_GL_GLX_OBJS) 
