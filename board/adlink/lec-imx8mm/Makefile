#
# Copyright 2022 ADLINK Technology inc.
#
# SPDX-License-Identifier:      GPL-2.0+
#

obj-y += lec-imx8mm.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
obj-$(CONFIG_LPDDR4_4GB) += lpddr4_timing_MT53E1G32D2FW-046_WTB_2133MHz.o
obj-$(CONFIG_LPDDR4_8GB) += lpddr4_timing_MT53E1G64D4HJ-046_WTC_2133MHz.o
endif
