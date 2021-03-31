#
# Copyright 2019 NXP
#
# SPDX-License-Identifier:      GPL-2.0+
#

obj-y += lec-imx8mp.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
ifeq ($(DDRTYPE),DDR_2GB)
obj-$(CONFIG_IMX8M_LPDDR4) += lpddr4_timing_MT53D512M32D2DS-053_WTD_1500MHz.o
else
ifeq ($(DDRTYPE),DDR_2GK)
obj-$(CONFIG_IMX8M_LPDDR4) += lpddr4_timing_MT53D512M32D2DS-046_ITD_2000MHz.o
else
ifeq ($(DDRTYPE),DDR_4GB)
obj-$(CONFIG_IMX8M_LPDDR4) += lpddr4_timing_MT53D1024M32D4DT-053_WTD_1500MHz.o
else
$(error Incorrect LPDDR4 Configuration (DDRTYPE=$(DDRTYPE)))
endif #DDRTYPE_4GB
endif #DDRTYPE_2GK
endif #DDRTYPE_2GB
endif #CONFIG_SPL_BUILD
