#
# Copyright 2022 ADLINK Technology inc.
#
# SPDX-License-Identifier:      GPL-2.0+
#

obj-y += lec-imx8mm.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
obj-$(CONFIG_IMX8M_LPDDR4) += lpddr4_timing_MT53E1G32D2FW-046_WTB_1500MHz.o
obj-$(CONFIG_IMX8M_LPDDR4) += lpddr4_timing_MT53E512M32D1ZW-046_WTB_1500MHz.o
endif
