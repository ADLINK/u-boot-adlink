#
# Copyright 2016 Freescale Semiconductor
#
# SPDX-License-Identifier:      GPL-2.0+
#

ifeq ($(CONFIG_IMX8M_LPDDR4), y)	
	obj-$(CONFIG_IMX8M_LPDDR4) += lpddr4_timing.o lpddr4_timing_b0.o
else	
	ifeq ($(DDR_1GB), y)			
		obj-y += ddr/ddr3l/ddr_init_1g.o 
	endif

	ifeq ($(DDR_2GB), y)		
		obj-y += ddr/ddr3l/ddr_init_2g.o 
	endif

	ifeq ($(DDR_4GB), y)		
		obj-y += ddr/ddr3l/ddr_init_4g.o 
	endif
	
	ifeq ($(DDR_4GB_MT41K512M16VRN), y)		
		obj-y += ddr/ddr3l/ddr_init_4g_MT41K512M16VRN.o 
	endif
	obj-y += ddr/ddr3l/ddrphy_train.o ddr/ddr3l/helper.o
endif

obj-y += lec_imx8m.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
endif
