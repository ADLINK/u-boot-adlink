/*
 * Copyright 2017 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <errno.h>
#include <asm/io.h>
#include <asm/arch/ddr.h>
#include <asm/arch/clock.h>
#include "../ddr.h"

#ifdef CONFIG_ENABLE_DDR_TRAINING_DEBUG
#define ddr_printf(args...) printf(args)
#else
#define ddr_printf(args...)
#endif
#include "../wait_ddrphy_training_complete.c"

volatile unsigned int tmp, tmp_t;

void ddr_cfg_phy(void) {
	unsigned int tmp, tmp_t;
	
	//Init DDRPHY register...
	reg32_write(0x3c080440,0x2);
	reg32_write(0x3c080444,0x3);
	reg32_write(0x3c080448,0x4);
	reg32_write(0x3c08044c,0x5);
	reg32_write(0x3c080450,0x0);
	reg32_write(0x3c080454,0x1);
	reg32_write(0x3c04017c,0x3ff);
	reg32_write(0x3c04057c,0x3ff);
	reg32_write(0x3c04417c,0x3ff);
	reg32_write(0x3c04457c,0x3ff);
	reg32_write(0x3c04817c,0x3ff);
	reg32_write(0x3c04857c,0x3ff);
	reg32_write(0x3c04c17c,0x3ff);
	reg32_write(0x3c04c57c,0x3ff);
	reg32_write(0x3c000154,0x3ff);
	reg32_write(0x3c004154,0x3ff);
	reg32_write(0x3c008154,0x3ff);
	reg32_write(0x3c00c154,0x3ff);
	reg32_write(0x3c010154,0xff);
	reg32_write(0x3c014154,0xff);
	reg32_write(0x3c018154,0x3ff);
	reg32_write(0x3c01c154,0x3ff);
	reg32_write(0x3c020154,0x3ff);
	reg32_write(0x3c024154,0x3ff);
	reg32_write(0x3c080314,0xb);
	reg32_write(0x3c0800b8,0x1);
	reg32_write(0x3c080090,0x8);
	reg32_write(0x3c0800e8,0x0);
	reg32_write(0x3c080158,0xa);
	reg32_write(0x3c040134,0x208);
	reg32_write(0x3c040534,0x208);
	reg32_write(0x3c044134,0x208);
	reg32_write(0x3c044534,0x208);
	reg32_write(0x3c048134,0x208);
	reg32_write(0x3c048534,0x208);
	reg32_write(0x3c04c134,0x208);
	reg32_write(0x3c04c534,0x208);
	reg32_write(0x3c040124,0xe38);
	reg32_write(0x3c040524,0xe38);
	reg32_write(0x3c044124,0xe38);
	reg32_write(0x3c044524,0xe38);
	reg32_write(0x3c048124,0xe38);
	reg32_write(0x3c048524,0xe38);
	reg32_write(0x3c04c124,0xe38);
	reg32_write(0x3c04c524,0xe38);
	reg32_write(0x3c00010c,0x63);
	reg32_write(0x3c00410c,0x63);
	reg32_write(0x3c00810c,0x63);
	reg32_write(0x3c00c10c,0x63);
	reg32_write(0x3c01010c,0x63);
	reg32_write(0x3c01410c,0x63);
	reg32_write(0x3c01810c,0x63);
	reg32_write(0x3c01c10c,0x63);
	reg32_write(0x3c02010c,0x63);
	reg32_write(0x3c02410c,0x63);
	reg32_write(0x3c080060,0x5);
	reg32_write(0x3c0801d4,0x0);
	reg32_write(0x3c080140,0x0);
	reg32_write(0x3c080020,0x190);
	reg32_write(0x3c080220,0x9);
	reg32_write(0x3c0802c8,0x0);
	reg32_write(0x3c04010c,0x581);
	reg32_write(0x3c04050c,0x581);
	reg32_write(0x3c04410c,0x581);
	reg32_write(0x3c04450c,0x581);
	reg32_write(0x3c04810c,0x581);
	reg32_write(0x3c04850c,0x581);
	reg32_write(0x3c04c10c,0x581);
	reg32_write(0x3c04c50c,0x581);
	reg32_write(0x3c0803e8,0x1);
	reg32_write(0x3c080064,0x5);
	reg32_write(0x3c0803c0,0x5555);
	reg32_write(0x3c0803c4,0x5555);
	reg32_write(0x3c0803c8,0x5555);
	reg32_write(0x3c0803cc,0x5555);
	reg32_write(0x3c0803d0,0x5555);
	reg32_write(0x3c0803d4,0x5555);
	reg32_write(0x3c0803d8,0x5555);
	reg32_write(0x3c0803dc,0xf000);
	reg32_write(0x3c080094,0x0);
	reg32_write(0x3c0800b4,0x0);
	reg32_write(0x3c080180,0x2);

	//enable APB bus to access DDRPHY RAM
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0000, 0x0);
	//load the 1D training image
	ddr_load_train_code(FW_1D_IMAGE);

	//configure DDRPHY-FW DMEM structure @clock0...
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0099, 0x1);

	//set the PHY input clock to the desired frequency for pstate 0
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54000,0x80);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54003,0x640);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54004,0x2);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54006,0x12c);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54007,0x2000);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54008,0x303);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54009,0x200);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x5400b,0x31f);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x5400c,0xc8);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54012,0x1);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x5402f,0x1c70);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54030,0x4);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x54031,0x18);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x5403a,0x1323);

	//disable APB bus to access DDRPHY RAM
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0000, 0x1);
	//Reset MPU and run
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0099, 0x9);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0099, 0x1);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0099, 0x0);
	wait_ddrphy_training_complete();

	//set the PHY input clock to the desired frequency for pstate 0
	reg32_write(0x3038a088,0x7070000);
	reg32_write(0x3038a084,0x4030000);
	reg32_write(0x303a00ec,0xffff);
	tmp=reg32_read(0x303a00f8);
	tmp |= 0x20;
	reg32_write(0x303a00f8,tmp);
	reg32_write(0x30360068,0xbbe582);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x80;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp |= 0x200;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x20;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x10;
	reg32_write(0x30360060,tmp);
	do{
		tmp=reg32_read(0x30360060);
		if(tmp&0x80000000) break;
	}while(1);
	reg32_write(0x30389808,0x1000000);

	//Halt MPU
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0099, 0x1);
	//enable APB bus to access DDRPHY RAM
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0000, 0x0);

	//Load firmware PIE image
	reg32_write(0x3c240000,0x10);
	reg32_write(0x3c240004,0x400);
	reg32_write(0x3c240008,0x10e);
	reg32_write(0x3c24000c,0x0);
	reg32_write(0x3c240010,0x0);
	reg32_write(0x3c240014,0x8);
	reg32_write(0x3c2400a4,0xb);
	reg32_write(0x3c2400a8,0x480);
	reg32_write(0x3c2400ac,0x109);
	reg32_write(0x3c2400b0,0x8);
	reg32_write(0x3c2400b4,0x448);
	reg32_write(0x3c2400b8,0x139);
	reg32_write(0x3c2400bc,0x8);
	reg32_write(0x3c2400c0,0x478);
	reg32_write(0x3c2400c4,0x109);
	reg32_write(0x3c2400c8,0x2);
	reg32_write(0x3c2400cc,0x10);
	reg32_write(0x3c2400d0,0x139);
	reg32_write(0x3c2400d4,0xf);
	reg32_write(0x3c2400d8,0x7c0);
	reg32_write(0x3c2400dc,0x139);
	reg32_write(0x3c2400e0,0x44);
	reg32_write(0x3c2400e4,0x630);
	reg32_write(0x3c2400e8,0x159);
	reg32_write(0x3c2400ec,0x14f);
	reg32_write(0x3c2400f0,0x630);
	reg32_write(0x3c2400f4,0x159);
	reg32_write(0x3c2400f8,0x47);
	reg32_write(0x3c2400fc,0x630);
	reg32_write(0x3c240100,0x149);
	reg32_write(0x3c240104,0x4f);
	reg32_write(0x3c240108,0x630);
	reg32_write(0x3c24010c,0x179);
	reg32_write(0x3c240110,0x8);
	reg32_write(0x3c240114,0xe0);
	reg32_write(0x3c240118,0x109);
	reg32_write(0x3c24011c,0x0);
	reg32_write(0x3c240120,0x7c8);
	reg32_write(0x3c240124,0x109);
	reg32_write(0x3c240128,0x0);
	reg32_write(0x3c24012c,0x1);
	reg32_write(0x3c240130,0x8);
	reg32_write(0x3c240134,0x0);
	reg32_write(0x3c240138,0x45a);
	reg32_write(0x3c24013c,0x9);
	reg32_write(0x3c240140,0x0);
	reg32_write(0x3c240144,0x448);
	reg32_write(0x3c240148,0x109);
	reg32_write(0x3c24014c,0x40);
	reg32_write(0x3c240150,0x630);
	reg32_write(0x3c240154,0x179);
	reg32_write(0x3c240158,0x1);
	reg32_write(0x3c24015c,0x618);
	reg32_write(0x3c240160,0x109);
	reg32_write(0x3c240164,0x40c0);
	reg32_write(0x3c240168,0x630);
	reg32_write(0x3c24016c,0x149);
	reg32_write(0x3c240170,0x8);
	reg32_write(0x3c240174,0x4);
	reg32_write(0x3c240178,0x48);
	reg32_write(0x3c24017c,0x4040);
	reg32_write(0x3c240180,0x630);
	reg32_write(0x3c240184,0x149);
	reg32_write(0x3c240188,0x0);
	reg32_write(0x3c24018c,0x4);
	reg32_write(0x3c240190,0x48);
	reg32_write(0x3c240194,0x40);
	reg32_write(0x3c240198,0x630);
	reg32_write(0x3c24019c,0x149);
	reg32_write(0x3c2401a0,0x10);
	reg32_write(0x3c2401a4,0x4);
	reg32_write(0x3c2401a8,0x18);
	reg32_write(0x3c2401ac,0x0);
	reg32_write(0x3c2401b0,0x4);
	reg32_write(0x3c2401b4,0x78);
	reg32_write(0x3c2401b8,0x549);
	reg32_write(0x3c2401bc,0x630);
	reg32_write(0x3c2401c0,0x159);
	reg32_write(0x3c2401c4,0xd49);
	reg32_write(0x3c2401c8,0x630);
	reg32_write(0x3c2401cc,0x159);
	reg32_write(0x3c2401d0,0x94a);
	reg32_write(0x3c2401d4,0x630);
	reg32_write(0x3c2401d8,0x159);
	reg32_write(0x3c2401dc,0x441);
	reg32_write(0x3c2401e0,0x630);
	reg32_write(0x3c2401e4,0x149);
	reg32_write(0x3c2401e8,0x42);
	reg32_write(0x3c2401ec,0x630);
	reg32_write(0x3c2401f0,0x149);
	reg32_write(0x3c2401f4,0x1);
	reg32_write(0x3c2401f8,0x630);
	reg32_write(0x3c2401fc,0x149);
	reg32_write(0x3c240200,0x0);
	reg32_write(0x3c240204,0xe0);
	reg32_write(0x3c240208,0x109);
	reg32_write(0x3c24020c,0xa);
	reg32_write(0x3c240210,0x10);
	reg32_write(0x3c240214,0x109);
	reg32_write(0x3c240218,0x9);
	reg32_write(0x3c24021c,0x3c0);
	reg32_write(0x3c240220,0x149);
	reg32_write(0x3c240224,0x9);
	reg32_write(0x3c240228,0x3c0);
	reg32_write(0x3c24022c,0x159);
	reg32_write(0x3c240230,0x18);
	reg32_write(0x3c240234,0x10);
	reg32_write(0x3c240238,0x109);
	reg32_write(0x3c24023c,0x0);
	reg32_write(0x3c240240,0x3c0);
	reg32_write(0x3c240244,0x109);
	reg32_write(0x3c240248,0x18);
	reg32_write(0x3c24024c,0x4);
	reg32_write(0x3c240250,0x48);
	reg32_write(0x3c240254,0x18);
	reg32_write(0x3c240258,0x4);
	reg32_write(0x3c24025c,0x58);
	reg32_write(0x3c240260,0xa);
	reg32_write(0x3c240264,0x10);
	reg32_write(0x3c240268,0x109);
	reg32_write(0x3c24026c,0x2);
	reg32_write(0x3c240270,0x10);
	reg32_write(0x3c240274,0x109);
	reg32_write(0x3c240278,0x7);
	reg32_write(0x3c24027c,0x7c0);
	reg32_write(0x3c240280,0x109);
	reg32_write(0x3c240284,0x10);
	reg32_write(0x3c240288,0x10);
	reg32_write(0x3c24028c,0x109);
	reg32_write(0x3c240290,0x0);
	reg32_write(0x3c240294,0x8140);
	reg32_write(0x3c240298,0x10c);
	reg32_write(0x3c24029c,0x10);
	reg32_write(0x3c2402a0,0x8138);
	reg32_write(0x3c2402a4,0x10c);
	reg32_write(0x3c2402a8,0x8);
	reg32_write(0x3c2402ac,0x7c8);
	reg32_write(0x3c2402b0,0x101);
	reg32_write(0x3c2402b4,0x8);
	reg32_write(0x3c2402b8,0x0);
	reg32_write(0x3c2402bc,0x8);
	reg32_write(0x3c2402c0,0x8);
	reg32_write(0x3c2402c4,0x448);
	reg32_write(0x3c2402c8,0x109);
	reg32_write(0x3c2402cc,0xf);
	reg32_write(0x3c2402d0,0x7c0);
	reg32_write(0x3c2402d4,0x109);
	reg32_write(0x3c2402d8,0x47);
	reg32_write(0x3c2402dc,0x630);
	reg32_write(0x3c2402e0,0x109);
	reg32_write(0x3c2402e4,0x8);
	reg32_write(0x3c2402e8,0x618);
	reg32_write(0x3c2402ec,0x109);
	reg32_write(0x3c2402f0,0x8);
	reg32_write(0x3c2402f4,0xe0);
	reg32_write(0x3c2402f8,0x109);
	reg32_write(0x3c2402fc,0x0);
	reg32_write(0x3c240300,0x7c8);
	reg32_write(0x3c240304,0x109);
	reg32_write(0x3c240308,0x8);
	reg32_write(0x3c24030c,0x8140);
	reg32_write(0x3c240310,0x10c);
	reg32_write(0x3c240314,0x0);
	reg32_write(0x3c240318,0x1);
	reg32_write(0x3c24031c,0x8);
	reg32_write(0x3c240320,0x8);
	reg32_write(0x3c240324,0x4);
	reg32_write(0x3c240328,0x8);
	reg32_write(0x3c24032c,0x8);
	reg32_write(0x3c240330,0x7c8);
	reg32_write(0x3c240334,0x101);
	reg32_write(0x3c240018,0x0);
	reg32_write(0x3c24001c,0x0);
	reg32_write(0x3c240020,0x8);
	reg32_write(0x3c240024,0x0);
	reg32_write(0x3c240028,0x0);
	reg32_write(0x3c24002c,0x0);
	reg32_write(0x3c34039c,0x400);
	reg32_write(0x3c24005c,0x0);
	reg32_write(0x3c240098,0x2c);
	reg32_write(0x3c08002c,0x65);
	reg32_write(0x3c080030,0xc9);
	reg32_write(0x3c080034,0x7d1);
	reg32_write(0x3c080038,0x2c);
	reg32_write(0x3c240030,0x0);
	reg32_write(0x3c240034,0x173);
	reg32_write(0x3c240038,0x60);
	reg32_write(0x3c24003c,0x6110);
	reg32_write(0x3c240040,0x2152);
	reg32_write(0x3c240044,0xdfbd);
	reg32_write(0x3c240048,0xffff);
	reg32_write(0x3c24004c,0x6152);
	reg32_write(0x3c300200, 0x00000000);
	/*
	 * CalBusy.0 =1, indicates the calibrator is actively calibrating.
	 * Wait Calibrating done.
	 */
	tmp_t = 1;
	while(tmp_t) {
		tmp = reg32_read(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x20097);
		tmp_t = tmp & 0x01;
	}
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0000, 0x0);
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0x2006e, 0x0);
	//disable APB bus to access DDRPHY RAM
	reg32_write(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + 4 * 0xd0000, 0x1);
}
void ddr_init(void)
{	
	/** Initialize DDR clock and DDRC registers **/
	printf(" A1 ddr_init 2GB start \r\n");
	reg32_write(0x3038a088,0x7070000);
	reg32_write(0x3038a084,0x4030000);
	reg32_write(0x303a00ec,0xffff);
	tmp=reg32_read(0x303a00f8);
	tmp |= 0x20;
	reg32_write(0x303a00f8,tmp);
	reg32_write(0x30391000,0x8f000000);
	reg32_write(0x30391004,0x8f000000);
	reg32_write(0x30360068,0xbbe582);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x80;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp |= 0x200;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x20;
	reg32_write(0x30360060,tmp);
	tmp=reg32_read(0x30360060);
	tmp &= ~0x10;
	reg32_write(0x30360060,tmp);
	do{
		tmp=reg32_read(0x30360060);
		if(tmp&0x80000000) break;
	}while(1);
	reg32_write(0x30391000,0x8f000006);
	reg32_write(0x3d400304,0x1);
	reg32_write(0x3d400030,0x20);
	reg32_write(0x3d400000,0x83040001);
	reg32_write(0x3d400010,0x40004030);
	reg32_write(0x3d400064,0x610068);
	reg32_write(0x3d4000d0,0xc00200c5);
	reg32_write(0x3d4000d4,0x1000b);
	reg32_write(0x3d4000dc,0x1c700004);
	reg32_write(0x3d4000e0,0x180000);
	reg32_write(0x3d4000e4,0x90000);
	reg32_write(0x3d4000f0,0x2);
	reg32_write(0x3d4000f4,0xee5);
	reg32_write(0x3d400100,0xc101b0e);
	reg32_write(0x3d400104,0x30314);
	reg32_write(0x3d400108,0x4060509);
	reg32_write(0x3d40010c,0x2006);
	reg32_write(0x3d400110,0x6020306);
	reg32_write(0x3d400114,0x4040302);
	reg32_write(0x3d400120,0x905);
	reg32_write(0x3d400180,0x40800020);
	reg32_write(0x3d400184,0xc350);
	reg32_write(0x3d400190,0x3868203);
	reg32_write(0x3d400194,0x20303);
	reg32_write(0x3d4001b4,0x603);
	reg32_write(0x3d400198,0x7000000);
	reg32_write(0x3d4001b0,0x11);
	reg32_write(0x3d4001a0,0x400018);
	reg32_write(0x3d4001a4,0x5003c);
	reg32_write(0x3d4001a8,0x80000000);
	reg32_write(0x3d4001c4,0x1);
	reg32_write(0x3d400200,0x16);
	reg32_write(0x3d400204,0x80808);
	reg32_write(0x3d400208,0x0);
	reg32_write(0x3d40020c,0x0);
	reg32_write(0x3d400210,0x1f1f);
	reg32_write(0x3d400214,0x7070707);
	reg32_write(0x3d400218,0xf070707);
	reg32_write(0x3d400224,0xa020b06);
	reg32_write(0x3d400228,0xa0a0a0a);
	reg32_write(0x3d40022c,0x0);
	reg32_write(0x3d400240,0x600060c);
	reg32_write(0x3d400244,0x1323);
	reg32_write(0x3d400264,0x9);
	reg32_write(0x3d40049c,0x100001);
	reg32_write(0x3d4004a0,0x41f);
	reg32_write(0x30391000,0x8f000000);
	reg32_write(0x3d400304,0x0);
	reg32_write(0x3d400030,0xa8);
	reg32_write(0x3d400320,0x0);
	tmp=reg32_read(0x3d400060);
	tmp |= 0x1;
	reg32_write(0x3d400060,tmp);
	reg32_write(0x30391000,0x8f000004);
	reg32_write(0x30391000,0x8f000000);
	reg32_write(0x3d400320,0x0);
	reg32_write(0x3d4001b0,0x0);
	do{
		tmp=reg32_read(0x3d400308);
		if(tmp&0x36000000) break;
	}while(1);
	reg32_write(0x3d400490,0x0);
	do{
		tmp=reg32_read(0x3d4003fc);
		if((tmp&0x10001)==0) break;
	}while(1);
	reg32_write(0x3d400030,0xa8);
	do{
		tmp=reg32_read(0x3d400004);
		if(tmp&0x3) break;
	}while(1);

	/* Configure DDR PHY's registers */
	ddr_cfg_phy();

	reg32_write(DDRC_RFSHCTL3(0), 0x00000000);
	reg32_write(DDRC_SWCTL(0), 0x0000);
	/*
	 * ------------------- 9 -------------------
	 * Set DFIMISC.dfi_init_start to 1
	 *  -----------------------------------------
	 */
	reg32_write(DDRC_DFIMISC(0), 0x00000030);
	reg32_write(DDRC_SWCTL(0), 0x0001);

	/* wait DFISTAT.dfi_init_complete to 1 */
	tmp_t = 0;
	while(tmp_t==0){
		tmp  = reg32_read(DDRC_DFISTAT(0));
		tmp_t = tmp & 0x01;
		tmp  = reg32_read(DDRC_MRSTAT(0));
	}

	reg32_write(DDRC_SWCTL(0), 0x0000);

	/* clear DFIMISC.dfi_init_complete_en */
	reg32_write(DDRC_DFIMISC(0), 0x00000010);
	reg32_write(DDRC_DFIMISC(0), 0x00000011);
	reg32_write(DDRC_PWRCTL(0), 0x00000088);

	tmp = reg32_read(DDRC_CRCPARSTAT(0));
	/*
	 * set SWCTL.sw_done to enable quasi-dynamic register
	 * programming outside reset.
	 */
	reg32_write(DDRC_SWCTL(0), 0x00000001);

	/* wait SWSTAT.sw_done_ack to 1 */
	while((reg32_read(DDRC_SWSTAT(0)) & 0x1) == 0)
		;

	/* wait STAT.operating_mode([1:0] for ddr3) to normal state */
	while ((reg32_read(DDRC_STAT(0)) & 0x3) != 0x1)
		;

	reg32_write(DDRC_PWRCTL(0), 0x00000088);
	/* reg32_write(DDRC_PWRCTL(0), 0x018a); */
	tmp = reg32_read(DDRC_CRCPARSTAT(0));

	/* enable port 0 */
	reg32_write(DDRC_PCTRL_0(0), 0x00000001);
	/* enable DDR auto-refresh mode */
	tmp = reg32_read(DDRC_RFSHCTL3(0)) & ~0x1;
	reg32_write(DDRC_RFSHCTL3(0), tmp);
}
