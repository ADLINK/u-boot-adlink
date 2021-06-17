#
# Copyright 2019 NXP
#
# SPDX-License-Identifier:      GPL-2.0+
#

ifeq ($(CONFIG_IMX8M_LPDDR4), y)
	obj-$(CONFIG_IMX8M_LPDDR4) += lpddr4_timing.o lpddr4_timing_b0.o
else
	obj-$(CONFIG_DDR3L_1GB) += ddr/ddr3l/ddr_init_1g.o
	obj-$(CONFIG_DDR3L_2GB) += ddr/ddr3l/ddr_init_2g.o
	obj-$(CONFIG_DDR3L_4GB) += ddr/ddr3l/ddr_init_4g.o
	obj-$(CONFIG_DDR3L_4GB_MT) += ddr/ddr3l/ddr_init_4g_MT41K512M16VRN.o
	obj-y += ddr/ddr3l/ddrphy_train.o ddr/ddr3l/helper.o
endif

obj-y += lec-imx8m.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
endif
