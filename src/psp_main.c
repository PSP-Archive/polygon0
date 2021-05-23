// *******************************

// *******************************

//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//#include<string.h>

#include "shered.h"
#include "_clib.h"
#include "pg.h"

#include"my_gu.h"

///////////
//GUm (matrix)
#include"gumInternal.c"
#include"pspgum.c"
#include"pspgum_vfpu.c"



static unsigned int __attribute__((aligned(16))) list[262144]; // 256k[Bytes]
//extern unsigned char logo_start[];
#include "logo_data.c"	// texture data

/* RGBA 16-16-16 to 5551�ϊ��{���x�ϊ��}�N���B */
#define RGB1(r,g,b) ((((unsigned char)(b    ) & (0x1F<<3))<<(10-3))|(((unsigned char)(g    ) & (0x1F<<3))<<(5-3))|((((unsigned char)(r    )>>3) & 0x1F)   ))
#define RGB2(r,g,b) ((((unsigned char)(b*0.8) & (0x1F<<3))<<(10-3))|(((unsigned char)(g*0.8) & (0x1F<<3))<<(5-3))|((((unsigned char)(r*0.8)>>3) & 0x1F)   ))
#define RGB3(r,g,b) ((((unsigned char)(b*0.5) & (0x1F<<3))<<(10-3))|(((unsigned char)(g*0.5) & (0x1F<<3))<<(5-3))|((((unsigned char)(r*0.5)>>3) & 0x1F)   ))

struct Vertex
{
	float u, v;
	unsigned int color;
	float x,y,z;
};
//[RGB1]    0+_        ���邢
//          /:~=_
//         / :  ~=_
//[RGB2] 4+_3+    ~+1  ����
//        |~='`,  /|
//        |,'~=_'/ |
//[RGB3] 7+_   ~+5'+2  �Â�
//         ~=_  | /
//           ~=_|/
//[RGB1]       ~+6     ���邢
struct Vertex __attribute__((aligned(16))) vertices[12*3] =
{//face#1(up)
	{0, 0, RGB1(0x7f,0x00,0x00),-1,-1, 1}, // 0
	{1, 0, RGB2(0x7f,0x00,0x00),-1, 1, 1}, // 4
	{1, 1, RGB3(0x7f,0x00,0x00), 1, 1, 1}, // 5

	{0, 0, RGB1(0x7f,0x00,0x00),-1,-1, 1}, // 0
	{1, 1, RGB3(0x7f,0x00,0x00), 1, 1, 1}, // 5
	{0, 1, RGB2(0x7f,0x00,0x00), 1,-1, 1}, // 1
//face#6(down)
	{0, 0, RGB2(0x7f,0x33,0x00),-1,-1,-1}, // 3
	{1, 0, RGB3(0x7f,0x33,0x00), 1,-1,-1}, // 2
	{1, 1, RGB1(0x7f,0x33,0x00), 1, 1,-1}, // 6

	{0, 0, RGB2(0x7f,0x33,0x00),-1,-1,-1}, // 3
	{1, 1, RGB1(0x7f,0x33,0x00), 1, 1,-1}, // 6
	{0, 1, RGB3(0x7f,0x33,0x00),-1, 1,-1}, // 7
//face#2(right)
	{0, 0, RGB3(0x00,0x7f,0x33), 1,-1,-1}, // 2
	{1, 0, RGB2(0x00,0x7f,0x33), 1,-1, 1}, // 1
	{1, 1, RGB3(0x00,0x7f,0x33), 1, 1, 1}, // 5

	{0, 0, RGB3(0x00,0x7f,0x33), 1,-1,-1}, // 2
	{1, 1, RGB3(0x00,0x7f,0x33), 1, 1, 1}, // 5
	{0, 1, RGB1(0x00,0x7f,0x33), 1, 1,-1}, // 6
//face#3(left-bihind)
	{0, 0, RGB2(0x33,0x7f,0x00),-1,-1,-1}, // 3
	{1, 0, RGB3(0x33,0x7f,0x00),-1, 1,-1}, // 7
	{1, 1, RGB2(0x33,0x7f,0x00),-1, 1, 1}, // 4

	{0, 0, RGB2(0x33,0x7f,0x00),-1,-1,-1}, // 3
	{1, 1, RGB2(0x33,0x7f,0x00),-1, 1, 1}, // 4
	{0, 1, RGB1(0x33,0x7f,0x00),-1,-1, 1}, // 0
//face#5(front)
	{0, 0, RGB3(0x00,0x33,0x7f),-1, 1,-1}, // 7
	{1, 0, RGB1(0x00,0x33,0x7f), 1, 1,-1}, // 6
	{1, 1, RGB3(0x00,0x33,0x7f), 1, 1, 1}, // 5

	{0, 0, RGB3(0x00,0x33,0x7f),-1, 1,-1}, // 7
	{1, 1, RGB3(0x00,0x33,0x7f), 1, 1, 1}, // 5
	{0, 1, RGB2(0x00,0x33,0x7f),-1, 1, 1}, // 4
//face#4(back)
	{0, 0, RGB2(0x33,0x00,0x7f),-1,-1,-1}, // 3
	{1, 0, RGB1(0x33,0x00,0x7f),-1,-1, 1}, // 0
	{1, 1, RGB2(0x33,0x00,0x7f), 1,-1, 1}, // 1

	{0, 0, RGB2(0x33,0x00,0x7f),-1,-1,-1}, // 3
	{1, 1, RGB2(0x33,0x00,0x7f), 1,-1, 1}, // 1
	{0, 1, RGB3(0x33,0x00,0x7f), 1,-1,-1}, // 2
};
#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

// *******************************

unsigned short *Video;
// unsigned char Video[BUFFER_WIDTH * BUFFER_HEIGHT];	// Off-screen buffer���z���

static float gl_aaa, gl_bbb, gl_ccc, gl_ddd;

volatile int bSleep=0;

// -----------------------------------------------------------------------------

// �z�[���{�^���I�����ɃR�[���o�b�N
int exit_callback(void)
{
	bSleep=1;
	scePowerSetClockFrequency(222,222,111);
// Cleanup the games resources etc (if required)

// Exit game
	sceKernelExitGame();
	return 0;
}

// �d���X�C�b�`���쎞��s����ɃR�[���o�b�N�B
// ���̊֐����܂����s���ł��T�X�y���h�E�X�^���o�C�ɓ���\��������B
void power_callback(int unknown, int pwrflags)
{
	//if(pwrflags & (POWER_CB_SUSPEND|POWER_CB_STANDBY)){
	if(pwrflags & POWER_CB_POWER){
		if (!bSleep){
			bSleep=1;

			// �t�@�C���A�N�Z�X���ɃT�X�y���h�E�X�^���o�C�����
			// 0byte�̃Z�[�u�t�@�C�����ł��Ă��܂����Ƃ�����̂ŁA
			// �������ݒ��̓T�X�y���h�E�X�^���o�C�𖳌����B
			sceKernelPowerLock(0);
//			set_cpu_clock(0);
//			save_config();
//			if (rom_get_loaded() && rom_has_battery())
//				save_sram(get_sram(), rom_get_info()->ram_size);
			sceKernelPowerUnlock(0);
		}
	}
	if(pwrflags & POWER_CB_BATLOW){
		//renderer_set_msg("PSP Battery is Low!");
		if (!bSleep){
			bSleep=1;

			sceKernelPowerLock(0);
//			set_cpu_clock(0);
//			save_config();
//			if (rom_get_loaded() && rom_has_battery())
//				save_sram(get_sram(), rom_get_info()->ram_size);
			sceKernelPowerUnlock(0);

			// �����T�X�y���h�B
			// �o�b�e������10%��؂�p���[�����v���_�ł��n�߂�ƁA
			// ���삪�ɒ[�ɒx���Ȃ�t���[�Y������Z�[�u�ł��Ȃ��Ȃ����肷��B
			// �s�̃Q�[���ł�0%�܂Ŏg���Ă�悤�Ȃ̂���B
			scePowerRequestSuspend();
		}
	}
	if(pwrflags & POWER_CB_RESCOMP){
		bSleep=0;
	}
	// �R�[���o�b�N�֐��̍ēo�^
	// �i��x�Ă΂ꂽ��ēo�^���Ă����Ȃ��Ǝ��ɃR�[���o�b�N����Ȃ��j
	int cbid = sceKernelCreateCallback("Power Callback", power_callback, NULL);
	scePowerRegisterCallback(0, cbid);
}

// �|�[�����O�p�X���b�h
int CallbackThread(int args, void *argp)
{
	int cbid;

	// �R�[���o�b�N�֐��̓o�^
	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	cbid = sceKernelCreateCallback("Power Callback", power_callback, NULL);
	scePowerRegisterCallback(0, cbid);

	// �|�[�����O
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	// �|�[�����O�p�X���b�h�̐���
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
		sceKernelStartThread(thid, 0, 0);

	return thid;
}

// *******************************
//   �p�����[�^�������B
void init_params( void ){
	gl_aaa=  0.0;
	gl_bbb=188.0;
	gl_ccc= 55.5;
	gl_ddd=  0.0;
}
// *******************************
void input_key( void )	// �L�[�i������{�^���j����
{
static unsigned long pad1;
	pad1=pgiGetpad();

	if((pad1&CTRL_START)!=0)	// �X�^�[�g�Œ�~
	{
		while(1) {
			pad1=pgiGetpad();
			if((pad1&CTRL_SELECT)!=0) { break;	}	// �Z���N�g�ŉ���
		}
	}

// [HOME]�I�����Ă���B

	if(((pad1&CTRL_LTRIGGER )!=0)&&((pad1&CTRL_RTRIGGER )!=0)) // �k�{�q�ŁB
		{init_params();	}	//   �p�����[�^�������B

	if ((pad1&CTRL_LTRIGGER )!=0) {	gl_ddd += 0.001;	}	//     �i�k�j�� �A���₷
	if ((pad1&CTRL_RTRIGGER )!=0) {	gl_ddd -= 0.001;	}	//     �i�q�j�� �A���炷

	if ((pad1&CTRL_RIGHT)!=0) {		gl_aaa += 0.03;		}	//   �E�i���j�� �A���₷
	if ((pad1&CTRL_LEFT)!=0) {		gl_aaa -= 0.03;		}	//   ���i���j�� �A���炷

	if ((pad1&CTRL_UP)!=0) {		gl_bbb += 0.8;		}	//   ���i���j�� �A���₷
	if ((pad1&CTRL_DOWN)!=0) { 		gl_bbb -= 0.8;		}	//   ���i���j�� �A���炷

	if ((pad1&CTRL_SQUARE)!=0) {	gl_ddd += 0.03;		}	// �l�p�i���j�� �A���₷
	if ((pad1&CTRL_CROSS)!=0) {		gl_ddd -= 0.03;		}	// �o�c�i�~�j�� �A���炷
	if ((pad1&CTRL_TRIANGLE)!=0){	gl_ccc += 0.05; 	}	// �O�p�i���j�� �A���₷
	if ((pad1&CTRL_CIRCLE)!=0) {	gl_ccc -= 0.05;		}	//   �ہi���j�� �A���炷
}

// *******************************
void xmain(void)
{
	pgInit();
	SetupCallbacks();

	init_params();	//   �p�����[�^�������B

	// setup GU
	void* fbp0 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_5551);/*8888*/
	void* fbp1 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_5551);/*8888*/
	void* zbp  = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);

	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_5551,fbp0,BUF_WIDTH);/*8888*/
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,fbp1,BUF_WIDTH);
	sceGuDepthBuffer(zbp,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(65535,0);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0,0);

	v_sync();	//sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);


for(;;)
	{
		sceGuStart(GU_DIRECT,list);

		// clear screen
		sceGuClearColor(0xff333333); // 0xff554433
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup matrices for cube
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
	//	sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);
		sceGumPerspective(35.0f,10.0f/9.0f,0.25f, 800.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();
#if 1
		{
			ScePspFVector3 pos = { 0, 0, -5.5f };
			ScePspFVector3 rot;

rot.x = gl_ccc * 0.79f * (GU_PI/180.0f);
rot.y = gl_ccc * 0.98f * (GU_PI/180.0f);
rot.z = gl_ccc * 1.32f * (GU_PI/180.0f);
//			rot.x = gl_aaa   * (GU_PI/180.0f);
//			rot.y = (gl_bbb+0.75) * 0.004 * (GU_PI/180.0f);
//			rot.z = gl_ccc * 0.132f * (GU_PI/180.0f);

			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rot);
		}
#endif

		// setup texture
		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,logo_start);
		sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGB);
		sceGuTexEnvColor(0xffff00);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexScale(1.0f,1.0f);
		sceGuTexOffset(0.0f,0.0f);
		sceGuAmbientColor(0xffffffff);

		// draw cube
		{
		float i,j;
		ScePspFVector3 pos;
		ScePspFVector3 rot;
			for(i=-0.03;i<0.03;i+=0.005){
				for(j=-0.03;j<0.03;j+=0.001){
pos.x = i+gl_ddd+gl_ddd;
pos.y = j+gl_ddd;
pos.z = -i;
					sceGumTranslate(&pos);

			rot.x = gl_aaa * (GU_PI/180.0f);
			rot.y = gl_bbb * (GU_PI/180.0f);
			rot.z = gl_ccc * (GU_PI/180.0f);

					sceGumRotateXYZ(&rot);
					sceGumDrawArray(
						GU_TRIANGLES,
	GU_TEXTURE_32BITF|/*32*/
	GU_COLOR_5551|/*8888*/
	GU_VERTEX_32BITF|
	GU_TRANSFORM_3D,
						12*3,0,vertices);
				}
			}
		}
		sceGuFinish();
		sceGuSync(0,0);
		pgPrint(1*8,17*8,RGB(0x12,0x03,0x34),"16BIT COLORS. RGBA:5551");
		v_sync();	//sceDisplayWaitVblankStart();

		input_key();			// �L�[�i������{�^���j����

		sceGuSwapBuffers();

	}
//	return 0;	// �����ɂ͐�΂ɂ��Ȃ��B�i���ꂫ����\������j[HOME]�I�����Ă���B
}

// *******************************

