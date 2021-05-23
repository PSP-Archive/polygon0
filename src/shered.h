

#ifndef _PSP_SHERED_H
#define _PSP_SHERED_H
/// shered.h

#define v_sync	sceDisplayWaitVblankStart

#define RGB(r,g,b) ((((b   ) & (0x1F<<3))<<(10-3))|(((g   ) & (0x1F<<3))<<(5-3))|(((r>>3) & 0x1F)   ))

#include "syscall.h"

#endif //_PSP_SHERED_H
////////////////////////////////////////////////////////
