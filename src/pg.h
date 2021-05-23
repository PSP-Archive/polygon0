// primitive graphics, now not only graphics

#ifndef __PG_H__
#define __PG_H__


void pgPrint(unsigned int x,unsigned int y,unsigned int color,const char *str);
void pgInit();
unsigned long pgiGetpad();
unsigned long pgiGetTick();

typedef struct {
	unsigned long tick;
	unsigned long pad;
	unsigned long analog;
} pgi_ctrl_t;


void pgiGetCtrl(pgi_ctrl_t *d);


#define SCREEN_WIDTH  480
#define SCREEN_HEIGHT 272
#define	PIXELSIZE	1				//in short
#define	LINESIZE	512				//in short
#define	FRAMESIZE	0x44000			//in byte



//#define MKRGB(r,g,b) ( ((b&0xf8)<<7)+((g&0xf8)<<2)+((r&0xf8)>>3)+0x8000 )





#endif // __PG_H__


