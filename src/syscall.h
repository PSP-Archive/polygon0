
/* system call prototype for PSP () */

#ifndef _SYSCALL_H_INCLUDED
#define _SYSCALL_H_INCLUDED

#if 00
typedef unsigned long u32;
typedef unsigned char u8;
//typedef unsigned long size_t;
#else
#include"psptypes.h"

#endif

/******************************************************************************/
/* sceSuspendForUser */
int sceKernelPowerLock(int locktype);
int sceKernelPowerUnlock(int locktype);

/******************************************************************************/
/* scePower */
#define POWER_CB_POWER		0x80000000
#define POWER_CB_HOLDON 	0x40000000
#define POWER_CB_STANDBY	0x00080000
#define POWER_CB_RESCOMP	0x00040000
#define POWER_CB_RESUME 	0x00020000
#define POWER_CB_SUSPEND	0x00010000
#define POWER_CB_EXT		0x00001000
#define POWER_CB_BATLOW 	0x00000100
#define POWER_CB_BATTERY	0x00000080
#define POWER_CB_BATTPOWER	0x0000007F

long scePowerSetClockFrequency(long,long,long);
void scePowerRegisterCallback(int,int);



void scePowerRequestSuspend(void);

/******************************************************************************/
/* sceDisplay */
void sceDisplayWaitVblankStart();
void sceDisplaySetMode(long,long,long);
void sceDisplaySetFrameBuf(unsigned char *topaddr,long linesize,long pixelsize,long);


/******************************************************************************/
/* sceCtrl */
#define CTRL_ANALOG_X	0
#define CTRL_ANALOG_Y	1

/* Button bit masks */
#define CTRL_SELECT 	0x0001
#define CTRL_START		0x0008
#define CTRL_UP 		0x0010
#define CTRL_RIGHT		0x0020
#define CTRL_DOWN		0x0040
#define CTRL_LEFT		0x0080
#define CTRL_LTRIGGER	0x0100
#define CTRL_RTRIGGER	0x0200
#define CTRL_TRIANGLE	0x1000
#define CTRL_CIRCLE 	0x2000
#define CTRL_CROSS		0x4000
#define CTRL_SQUARE 	0x8000
#define CTRL_HOME		0x00010000
#define CTRL_HOLD		0x00020000
#define CTRL_NOTE		0x00800000

typedef struct _ctrl_data
{
	unsigned long frame;		//TimeStamp;
	unsigned long buttons;		//Buttons;
	unsigned char analog[4];
	unsigned long unused;
} ctrl_data_t;

/* Pass 1 to enable analogue mode */
void sceCtrlSetSamplingMode(signed long on);
void sceCtrlSetSamplingCycle(signed long unknown);

int sceCtrlReadBufferPositive(ctrl_data_t* paddata, int count);

/******************************************************************************/
/* IoFileMgrForUser */



/******************************************************************************/
/* StdioForUser */

/******************************************************************************/
/* LoadExecForUser */
void sceKernelExitGame();
int sceKernelRegisterExitCallback(int);

/******************************************************************************/
/* ThreadManForUser */
typedef int (*pg_threadfunc_t)(int args, void *argp);
int sceKernelCreateThread(const char *name, pg_threadfunc_t func, unsigned long priority, unsigned long stacksize, unsigned long attrib, void *unk);
int sceKernelStartThread(int hthread, int arg0, void *arg1);
void sceKernelExitThread(int ret);
int sceKernelWaitThreadEnd(int hthread, void *unk);
int sceKernelDeleteThread(int hthread);


//int sceKernelCreateEventFlag("SceGuSignal",512,3,0);
int sceKernelCreateEventFlag( char *name, int,int,int);//想像？？？


int sceKernelSleepThreadCB(void);
int sceKernelCreateCallback(const char *name, void *func, void *arg);

/******************************************************************************/
/* UtilsForUser */

/******************************************************************************/
/* sceGe_user */

/******************************************************************************/
/* sceAudio */









#endif // _SYSCALL_H_INCLUDED
