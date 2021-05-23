/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"
#include "pspge.h"
#include "pspgu.h"

unsigned int gu_current_frame;
GuContext gu_contexts[3];
int ge_list_executed[2];
void* ge_edram_address;
GuSettings gu_settings;
GuDisplayList* gu_list;
int gu_curr_context;
int gu_init;
int gu_display_on;
int gu_call_mode;
int gu_states;
GuDrawBuffer gu_draw_buffer;
unsigned int* gu_object_stack[32];
int gu_object_stack_depth;

GuLightSettings light_settings[4] =
{
	{
		{ 0x18, 0x5f, 0x63, 0x64 },
		{ 0x65, 0x6f, 0x70, 0x71 },
		{ 0x8f, 0x90, 0x91, 0x7b },
		{ 0x7c, 0x7d, 0x87, 0x8b }
	},

	{
		{ 0x19, 0x60, 0x66, 0x67 },
		{ 0x68, 0x72, 0x73, 0x74 },
		{ 0x92, 0x93, 0x94, 0x7e },
		{ 0x7f, 0x80, 0x88, 0x8c }
	},

	{
		{ 0x1a, 0x61, 0x69, 0x6a },
		{ 0x6b, 0x75, 0x76, 0x77 },
		{ 0x95, 0x96, 0x97, 0x81 },
		{ 0x82, 0x83, 0x89, 0x8d }
	},

	{
		{ 0x1b, 0x62, 0x6c, 0x6d },
		{ 0x6e, 0x78, 0x79, 0x7a },
		{ 0x98, 0x99, 0x9a, 0x84 },
		{ 0x85, 0x86, 0x8a, 0x8e }
	}
};

unsigned int __attribute__((aligned(16))) ge_init_list[] =
{
    0x01000000, 0x02000000, 0x10000000, 0x12000000, 0x13000000, 0x15000000, 0x16000000, 0x17000000,
    0x18000000, 0x19000000, 0x1a000000, 0x1b000000, 0x1c000000, 0x1d000000, 0x1e000000, 0x1f000000,
    0x20000000, 0x21000000, 0x22000000, 0x23000000, 0x24000000, 0x25000000, 0x26000000, 0x27000000,
    0x28000000, 0x2a000000, 0x2b000000, 0x2c000000, 0x2d000000, 0x2e000000, 0x2f000000, 0x30000000,
    0x31000000, 0x32000000, 0x33000000, 0x36000000, 0x37000000, 0x38000000, 0x3a000000, 0x3b000000,
    0x3c000000, 0x3d000000, 0x3e000000, 0x3f000000, 0x40000000, 0x41000000, 0x42000000, 0x43000000,
    0x44000000, 0x45000000, 0x46000000, 0x47000000, 0x48000000, 0x49000000, 0x4a000000, 0x4b000000,
    0x4c000000, 0x4d000000, 0x50000000, 0x51000000, 0x53000000, 0x54000000, 0x55000000, 0x56000000,
    0x57000000, 0x58000000, 0x5b000000, 0x5c000000, 0x5d000000, 0x5e000000, 0x5f000000, 0x60000000,
    0x61000000, 0x62000000, 0x63000000, 0x64000000, 0x65000000, 0x66000000, 0x67000000, 0x68000000,
    0x69000000, 0x6a000000, 0x6b000000, 0x6c000000, 0x6d000000, 0x6e000000, 0x6f000000, 0x70000000,
    0x71000000, 0x72000000, 0x73000000, 0x74000000, 0x75000000, 0x76000000, 0x77000000, 0x78000000,
    0x79000000, 0x7a000000, 0x7b000000, 0x7c000000, 0x7d000000, 0x7e000000, 0x7f000000, 0x80000000,
    0x81000000, 0x82000000, 0x83000000, 0x84000000, 0x85000000, 0x86000000, 0x87000000, 0x88000000,
    0x89000000, 0x8a000000, 0x8b000000, 0x8c000000, 0x8d000000, 0x8e000000, 0x8f000000, 0x90000000,
    0x91000000, 0x92000000, 0x93000000, 0x94000000, 0x95000000, 0x96000000, 0x97000000, 0x98000000,
    0x99000000, 0x9a000000, 0x9b000000, 0x9c000000, 0x9d000000, 0x9e000000, 0x9f000000, 0xa0000000,
    0xa1000000, 0xa2000000, 0xa3000000, 0xa4000000, 0xa5000000, 0xa6000000, 0xa7000000, 0xa8040004,
    0xa9000000, 0xaa000000, 0xab000000, 0xac000000, 0xad000000, 0xae000000, 0xaf000000, 0xb0000000,
    0xb1000000, 0xb2000000, 0xb3000000, 0xb4000000, 0xb5000000, 0xb8000101, 0xb9000000, 0xba000000,
    0xbb000000, 0xbc000000, 0xbd000000, 0xbe000000, 0xbf000000, 0xc0000000, 0xc1000000, 0xc2000000,
    0xc3000000, 0xc4000000, 0xc5000000, 0xc6000000, 0xc7000000, 0xc8000000, 0xc9000000, 0xca000000,
    0xcb000000, 0xcc000000, 0xcd000000, 0xce000000, 0xcf000000, 0xd0000000, 0xd2000000, 0xd3000000,
    0xd4000000, 0xd5000000, 0xd6000000, 0xd7000000, 0xd8000000, 0xd9000000, 0xda000000, 0xdb000000,
    0xdc000000, 0xdd000000, 0xde000000, 0xdf000000, 0xe0000000, 0xe1000000, 0xe2000000, 0xe3000000,
    0xe4000000, 0xe5000000, 0xe6000000, 0xe7000000, 0xe8000000, 0xe9000000, 0xeb000000, 0xec000000,
    0xee000000, 0xf0000000, 0xf1000000, 0xf2000000, 0xf3000000, 0xf4000000, 0xf5000000, 0xf6000000,
    0xf7000000, 0xf8000000, 0xf9000000,
    0x0f000000, 0x0c000000, 0, 0
};



void resetValues()
{
	unsigned int i;

	gu_init = 0;

	gu_states = 0;
	gu_current_frame = 0;
	gu_object_stack_depth = 0;

	gu_display_on = 0;
	gu_call_mode = 0;

	gu_draw_buffer.pixel_size = 1;
	gu_draw_buffer.frame_width = 0;
	gu_draw_buffer.frame_buffer = 0;
	gu_draw_buffer.disp_buffer = 0;
	gu_draw_buffer.depth_buffer = 0;
	gu_draw_buffer.depth_width = 0;
	gu_draw_buffer.width = 480;
	gu_draw_buffer.height = 272;

	for (i = 0; i < 3; ++i)
	{
		GuContext* context = &gu_contexts[i];

		context->scissor_enable = 0;
		context->scissor_start[0] = 0;
		context->scissor_start[1] = 0;
		context->scissor_end[0] = 0;
		context->scissor_end[1] = 0;

		context->near_plane = 0;
		context->far_plane = 1;

		context->depth_offset = 0;
		context->unknown_state = 0;
		context->texture_function = 0;
		context->texture_proj_map_mode = 0;
		context->texture_map_mode = 0;
		context->sprite_mode[0] = 0;
		context->sprite_mode[1] = 0;
		context->sprite_mode[2] = 0;
		context->sprite_mode[3] = 0;
		context->clear_color = 0;
		context->clear_stencil = 0;
		context->clear_depth = 0xffff;
		context->texture_mode = 0;
	}

	gu_settings.sig = 0;
	gu_settings.fin = 0;
}

void sceGuInit(void)
{
//	PspGeCallbackData callback;
//	callback.signal_func = callbackSig;
//	callback.signal_arg = &gu_settings;
//	callback.finish_func = callbackFin;
//	callback.finish_arg = &gu_settings;
//	gu_settings.ge_callback_id = sceGeSetCallback(&callback);

	ge_edram_address = sceGeEdramGetAddr();

	// initialize graphics hardware
	ge_list_executed[0] = sceGeListEnQueue((void*)((unsigned int)ge_init_list & 0x1fffffff),0,-1/*gu_settings.ge_callback_id*/,0);

	resetValues();

	gu_settings.kernel_event_flag = sceKernelCreateEventFlag("SceGuSignal",512,3,0);

	// wait for init to complete
	sceGeListSync(ge_list_executed[0],0);
}

static unsigned int staticOffset = 0;

static unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm)
{
	switch (psm)
	{
		case GU_PSM_T4:
			return (width * height) >> 1;

		case GU_PSM_T8:
			return width * height;

		case GU_PSM_5650:
		case GU_PSM_5551:
		case GU_PSM_4444:
		case GU_PSM_T16:
			return 2 * width * height;

		case GU_PSM_8888:
		case GU_PSM_T32:
			return 4 * width * height;

		default:
			return 0;
	}
}

void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm)
{
	unsigned int memSize = getMemorySize(width,height,psm);
	void* result = (void*)staticOffset;
	staticOffset += memSize;

	return result;
}

void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm)
{
	void* result = getStaticVramBuffer(width,height,psm);
	return (void*)(((unsigned int)result) + ((unsigned int)sceGeEdramGetAddr()));
}


void sendCommandi(int cmd, int argument)
{
	*(gu_list->current++) = (cmd << 24) | (argument & 0xffffff);
}

void sendCommandf(int cmd, float argument)
{
	union
	{
		float f;
		unsigned int i;
	} t;
	t.f = argument;

	sendCommandi(cmd,t.i >> 8);
}

void sendCommandiStall(int cmd, int argument)
{
	sendCommandi(cmd,argument);

	if (!gu_object_stack_depth && !gu_curr_context)
		sceGeListUpdateStallAddr(ge_list_executed[0],gu_list->current);
}

int sceGuFinish(void)
{
	// TODO: see what this really does...
	if (((gu_curr_context^2) < 1) || (gu_curr_context < 1))
	{
		sendCommandi(15,0);
		sendCommandiStall(12,0);
	}
	else
	{
		if (gu_call_mode == 1)
		{
			sendCommandi(14,0x120000);
			sendCommandi(12,0);
			sendCommandiStall(0,0);
		}
		else
		{
			sendCommandi(11,0);
		}
	}

	unsigned int size = ((unsigned int)gu_list->current) - ((unsigned int)gu_list->start);

	// go to parent list
	gu_curr_context = gu_list->parent_context;
	gu_list = &gu_contexts[gu_curr_context].list;
	return size;
}

void sceGuDrawArray(int prim, int vtype, int count, const void* indices, const void* vertices)
{
  if (vtype)
    sendCommandi(18,vtype);

  if (indices)
  {
    sendCommandi(16,(((unsigned int)indices) >> 8) & 0xf0000);
    sendCommandi(2,((unsigned int)indices) & 0xffffff);
  }

  if (vertices)
  {
    sendCommandi(16,(((unsigned int)vertices) >> 8) & 0xf0000);
    sendCommandi(1,((unsigned int)vertices) & 0xffffff);
  }

  sendCommandiStall(4,(prim << 16)|count);
}
void sceGuEnable(int state)
{
  switch(state)
  {
    case 0: sendCommandi(34,1); break;
    case 1: sendCommandi(35,1); break;
    case 2:
    {
    	GuContext* context = &gu_contexts[gu_curr_context];
	context->scissor_enable = 1;
	sendCommandi(212,(context->scissor_start[1]<<10)|context->scissor_start[0]);
	sendCommandi(213,(context->scissor_end[1]<<10)|context->scissor_end[0]);
    }
    break;
    case 3: sendCommandi(36,1); break;
    case 4: sendCommandi(33,1); break;
    case 5: sendCommandi(29,1); break;
    case 6: sendCommandi(32,1); break;
    case 7: sendCommandi(31,1); break;
    case 8: sendCommandi(28,1); break;
    case 9: sendCommandi(30,1); break;
    case 10: sendCommandi(23,1); break;
    case 11: sendCommandi(24,1); break;
    case 12: sendCommandi(25,1); break;
    case 13: sendCommandi(26,1); break;
    case 14: sendCommandi(27,1); break;
    case 15: sendCommandi(37,1); break;
    case 16: sendCommandi(38,1); break;
    case 17: sendCommandi(39,1); break;
    case 18: sendCommandi(40,1); break;
    case 19: sendCommandi(81,1); break;
    case 20: sendCommandi(56,1); break;
    case 21:
    {
	GuContext* context = &gu_contexts[gu_curr_context];
	context->unknown_state = 0x10000;
	sendCommandi(201,0x10000|context->texture_function);
    }
    break;
  }

  if (state < 22)
    gu_states |= (1 << state);
}

void sceGuPatchDivide(unsigned int a0, unsigned int a1)
								{	sendCommandi(54,(a1 << 8)|a0);}
void sceGuSetMatrix(int type, const ScePspFMatrix4* matrix)
{
	unsigned int i,j;
	const float* fmatrix = (const float*)matrix;

	switch (type)
	{
		case 0:
		{
			sendCommandf(62,0);

			// 4*4 - most probably projection
			for (i = 0; i < 16; ++i)
				sendCommandf(63,fmatrix[i]);
		}
		break;

		case 1:
		{
			sendCommandf(60,0);

			// 4*4 -> 3*4 - view matrix?
			for (i = 0; i < 4; ++i)
			{
				for (j = 0; j < 3; ++j)
					sendCommandf(61,fmatrix[j+i*4]);
			}
		}
		break;

		case 2:
		{
			sendCommandf(58,0);
			// 4*4 -> 3*4 - ???
			for (i = 0; i < 4; ++i)
			{
				for (j = 0; j < 3; ++j)
					sendCommandf(59,fmatrix[j+i*4]);
			}
		}
		break;

		case 3:
		{
			sendCommandf(64,0);
			// 4*4 -> 3*4 - ???
			for (i = 0; i < 4; ++i)
			{
				for (j = 0; j < 3; ++j)
					sendCommandf(65,fmatrix[j+i*4]);
			}
		}
		break;
	}
}

void sceGuViewport(int cx, int cy, int width, int height)
{
	sendCommandf(66,(float)(width>>1));
	sendCommandf(67,(float)(((-height) + ((-height) >> 31))>>1));
	sendCommandf(69,(float)cx);
	sendCommandf(70,(float)cy);
}
void sceGuTexScale(float u, float v)
{	sendCommandf(72,u);	sendCommandf(73,v);}
void sceGuTexOffset(float u, float v)
{	sendCommandf(74,u);	sendCommandf(75,v);}
void sceGuOffset(unsigned int x, unsigned int y)
{	sendCommandi(76,x << 4);	sendCommandi(77,y << 4);}
void sceGuShadeModel(int mode)
{
	switch(mode)
	{
		case 1: sendCommandi(80,1); break;
		default: sendCommandi(80,0); break;
	}
}
void sceGuColorMaterial(int a0){	sendCommandi(83,a0);}
void sceGuAmbientColor(unsigned int color)
{
	sendCommandi(85,color & 0xffffff);
	sendCommandi(88,color >> 24);
}
void sceGuSpecular(float power){	sendCommandf(91,power);} // specular power
void sceGuFrontFace(int order)
{
	if (order)	sendCommandi(155,0);
	else		sendCommandi(155,1);
}
void sceGuStart(int cid, void* list)
{
	GuContext* context = &gu_contexts[cid];
	unsigned int* local_list = (unsigned int*)(((unsigned int)list) | 0x40000000);

	// setup display list

	context->list.start = local_list;
	context->list.current = local_list;
	context->list.parent_context = gu_curr_context;
	gu_list = &context->list;

	// store current context

	gu_curr_context = cid;

	if (!cid)
	{
		ge_list_executed[0] = sceGeListEnQueue(local_list,local_list,gu_settings.ge_callback_id,0);
		gu_settings.signal_offset = 0;
	}

	if (!gu_init)
	{
		static int dither_matrix[16] =
		{
			-4, 0,-3, 1,
			 2,-2, 3,-1,
			-3, 1,-4, 0,
			 3,-1, 2,-2
		};

		sceGuSetDither((ScePspIMatrix4*)dither_matrix);
		sceGuPatchDivide(16,16);
		sceGuColorMaterial(GU_AMBIENT|GU_DIFFUSE|GU_SPECULAR);

		sceGuSpecular(1.0f);
		sceGuTexScale(1.0f,1.0f);

		gu_init = 1;
	}

	if (!gu_curr_context)
	{
		if (gu_draw_buffer.frame_width)
		{
			sendCommandi(156, ((unsigned int)gu_draw_buffer.frame_buffer) & 0xffffff);
			sendCommandi(157, ((((unsigned int)gu_draw_buffer.frame_buffer) & 0xff000000) >> 8) | gu_draw_buffer.frame_width);
		}
	}
}

void sceGuDrawBuffer(int psm, void* fbp, int frame_width)
{
	gu_draw_buffer.pixel_size = psm;
	gu_draw_buffer.frame_width = frame_width;
	gu_draw_buffer.frame_buffer = fbp;

	if (!gu_draw_buffer.depth_buffer && gu_draw_buffer.height)
		gu_draw_buffer.depth_buffer = (void*)(((unsigned int)fbp) + (unsigned int)((gu_draw_buffer.height * frame_width) << 2));

	if (!gu_draw_buffer.depth_width)
		gu_draw_buffer.depth_width = frame_width;

	sendCommandi(210,psm);
	sendCommandi(156,((unsigned int)gu_draw_buffer.frame_buffer) & 0xffffff);
	sendCommandi(157,((((unsigned int)gu_draw_buffer.frame_buffer) & 0xff000000) >> 8)|gu_draw_buffer.frame_width);
	sendCommandi(158,((unsigned int)gu_draw_buffer.depth_buffer) & 0xffffff);
	sendCommandi(159,((((unsigned int)gu_draw_buffer.depth_buffer) & 0xff000000) >> 8)|gu_draw_buffer.depth_width);
}

void sceGuDepthBuffer(void* zbp, int zbw)
{
	gu_draw_buffer.depth_buffer = zbp;

	if (!gu_draw_buffer.depth_width || (gu_draw_buffer.depth_width != zbw))
		gu_draw_buffer.depth_width = zbw;

	sendCommandi(158,((unsigned int)zbp) & 0xffffff);
	sendCommandi(159,((((unsigned int)zbp) & 0xff000000) >> 8)|zbw);
}
//// 0xa0==160 0xbf==191
static int tbpcmd_tbl[8] = { 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7 };		// 0x30A18
static int tbwcmd_tbl[8] = { 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf };		// 0x30A38
static int tsizecmd_tbl[8] = { 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf };	// 0x30A58
int getExp(int val)
{
	unsigned int i;
	for (i = 9; (i > 0) && !((val >> i) & 1); --i);
	return i;
}
void sceGuTexImage(int mipmap, int width, int height, int tbw, const void* tbp)
{
	sendCommandi(tbpcmd_tbl[mipmap],((unsigned int)tbp) & 0xffffff);
	sendCommandi(tbwcmd_tbl[mipmap],((((unsigned int)tbp) >> 8) & 0x0f0000)|tbw);
	sendCommandi(tsizecmd_tbl[mipmap],(getExp(height) << 8)|(getExp(width)));
	sceGuTexFlush();
}
////
void sceGuTexMode(int tpsm, int maxmips, int a2, int swizzle)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->texture_mode = tpsm;

	sendCommandi(194,(maxmips << 16) | (a2 << 8) | (swizzle));
	sendCommandi(195,tpsm);

	sceGuTexFlush();
}
void sceGuTexFilter(int min, int mag)
{	sendCommandi(198,(mag << 8)|min);}
void sceGuTexFunc(int tfx, int tcc)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->texture_function = (tcc << 8) | tfx;

	sendCommandi(201,((tcc << 8)|tfx)|context->unknown_state);
}
void sceGuTexEnvColor(unsigned int color)
{	sendCommandi(202,color & 0xffffff);}
void sceGuTexFlush(void)
{	sendCommandf(203,0.0f);}
void sceGuScissor(int x, int y, int w, int h)
{
	GuContext* context = &gu_contexts[gu_curr_context];

	context->scissor_start[0] = x;
	context->scissor_start[1] = y;
	context->scissor_end[0] = w-1;
	context->scissor_end[1] = h-1;

	if (context->scissor_enable)
	{
		sendCommandi(212,(context->scissor_start[1] << 10)|context->scissor_start[0]);
		sendCommandi(213,(context->scissor_end[1] << 10)|context->scissor_end[0]);
	}
}
void sceGuDepthRange(int near, int far)
{
	GuContext* context = &gu_contexts[gu_curr_context];

	unsigned int max = (unsigned int)near + (unsigned int)far;
	int val = (int)((max >> 31) + max);
	float z = (float)(val >> 1);

	context->near_plane = near;
        context->far_plane = far;

        sendCommandf(68,z - ((float)near));
        sendCommandf(71,z + ((float)context->depth_offset));

	if (near > far)
        {
          int temp = near;
          near = far;
          far = temp;
        }

        sendCommandi(214,near);
        sendCommandi(215,far);
}
void sceGuDepthFunc(int function){	sendCommandi(222,function);}
void sceGuSetDither(const ScePspIMatrix4* matrix)
{
	sendCommandi(226,(matrix->x.x & 0x0f)|((matrix->x.y & 0x0f) << 4)|((matrix->x.z & 0x0f) << 8)|((matrix->x.w & 0x0f) << 12));
	sendCommandi(227,(matrix->y.x & 0x0f)|((matrix->y.y & 0x0f) << 4)|((matrix->y.z & 0x0f) << 8)|((matrix->y.w & 0x0f) << 12));
	sendCommandi(228,(matrix->z.x & 0x0f)|((matrix->z.y & 0x0f) << 4)|((matrix->z.z & 0x0f) << 8)|((matrix->z.w & 0x0f) << 12));
	sendCommandi(229,(matrix->w.x & 0x0f)|((matrix->w.y & 0x0f) << 4)|((matrix->w.z & 0x0f) << 8)|((matrix->w.w & 0x0f) << 12));
}


void* sceGuSwapBuffers(void)
{
	// flush_font();

	// switch pointers

	void* temp = gu_draw_buffer.disp_buffer;
	gu_draw_buffer.disp_buffer = gu_draw_buffer.frame_buffer;
	gu_draw_buffer.frame_buffer = temp;

	if (gu_display_on)
		sceDisplaySetFrameBuf((void*)((unsigned int)ge_edram_address + (unsigned int)gu_draw_buffer.disp_buffer), gu_draw_buffer.frame_width, gu_draw_buffer.pixel_size, 0);

	gu_current_frame ^= 1;

	return gu_draw_buffer.frame_buffer;
}

int sceGuSync(int mode, int a1)
{
	switch (mode)
	{
		case 0: return sceGeDrawSync(a1); break;
		case 3: return sceGeDrawSync(ge_list_executed[0]);
		case 4: return sceGeDrawSync(ge_list_executed[1]);
		default: case 1: case 2: return 0;
	}
}
int sceGuDisplay(int state)
{
	if(state)	sceDisplaySetFrameBuf((void*)((unsigned int)ge_edram_address+(unsigned int)gu_draw_buffer.disp_buffer),gu_draw_buffer.frame_width,gu_draw_buffer.pixel_size,1);
	else		sceDisplaySetFrameBuf(0,0,0,1);

	gu_display_on = state;
	return state;
}

//////

void* sceGuGetMemory(int size)
{
	// some kind of 4-byte alignment?
	size += 3;
	size += ((unsigned int)(size >> 31)) >> 30;
	size = (size >> 2) << 2;

	unsigned int* orig_ptr = gu_list->current;
	unsigned int* new_ptr = (unsigned int*)(((unsigned int)orig_ptr) + size + 8);

	int lo = (8 << 24) | (((unsigned int)new_ptr) & 0xffffff);
	int hi = (16 << 24) | ((((unsigned int)new_ptr) >> 8) & 0xf0000);

	orig_ptr[0] = hi;
	orig_ptr[1] = lo;

	gu_list->current = new_ptr;

	if (!gu_curr_context)
		sceGeListUpdateStallAddr(ge_list_executed[0],new_ptr);

	return orig_ptr + 2;
}
//////
void sceGuClearColor(unsigned int color)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->clear_color = color;
}
void sceGuClearDepth(unsigned int depth)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->clear_depth = depth;
}
//////


//////
void drawRegion(int x, int y, int width, int height)
{
  sendCommandi(21,(y << 10) | x);
  sendCommandi(22,(((y + height)-1) << 10) | ((x + width)-1));
}

void sceGuDispBuffer(int width, int height, void* dispbp, int dispbw)
{
	gu_draw_buffer.width = width;
	gu_draw_buffer.height = height;
	gu_draw_buffer.disp_buffer = dispbp;

	if (!gu_draw_buffer.frame_width || (gu_draw_buffer.frame_width != dispbw))
		gu_draw_buffer.frame_width = dispbw;

	drawRegion(0,0,gu_draw_buffer.width,gu_draw_buffer.height);
	sceDisplaySetMode(0,gu_draw_buffer.width,gu_draw_buffer.height);

	if (gu_display_on)
		sceDisplaySetFrameBuf((void*)(((unsigned int)ge_edram_address) + ((unsigned int)gu_draw_buffer.disp_buffer)), dispbw, gu_draw_buffer.pixel_size, 1);
}
//////
void sceGuClear(int flags)
{
  GuContext* context = &gu_contexts[gu_curr_context];
  unsigned int filter;

  switch (gu_draw_buffer.pixel_size)
  {
    case 0: filter = context->clear_color & 0xffffff; break;
    case 1: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 31); break;
    case 2: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 28); break;
    case 3: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 24); break;
    default: filter = 0; break;
  }

  short* buffer;
  int count;

  if (!(flags & 0x10))
  {
    buffer = (short*)sceGuGetMemory(12*sizeof(short));
    count = 2;

	buffer[0] = 0;						// 0-1
	buffer[1] = 0;						// 2-3
	buffer[2] = 0;						// 4-5
    buffer[3] = 0;						// 6-6
    buffer[4] = context->clear_depth;	// 8-9
	// 10-11 - align
    ((unsigned int*)buffer)[3] = filter;// 12-15
    buffer[8] = gu_draw_buffer.width;	// 16-17
    buffer[9] = gu_draw_buffer.height;	// 18-19
    buffer[10] = context->clear_depth;	// 20-21
  }
  else
  {
    short* curr;
    unsigned int i;

    buffer = (short*)sceGuGetMemory(96*sizeof(short));
    curr = buffer;
    count = 16;

    for (i = 0; i < 16; ++i, curr += 6)
    {
      unsigned int j,k;

      j = ((int)((i >> 31) + i)) >> 1;
      k = (i - (j << 1));

      *((unsigned int*)curr) = filter;
      curr[2] = (j-k) << 6;
      curr[3] = k * gu_draw_buffer.height;
      curr[4] = context->clear_depth;
    }

  }

   sendCommandi(211,((flags & 0x07) << 8) | 0x01);
   sceGuDrawArray(6,GU_COLOR_8888|GU_VERTEX_16BIT|GU_TRANSFORM_2D,count,0,buffer);
   sendCommandi(211,0);
}


