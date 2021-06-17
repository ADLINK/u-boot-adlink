#
# (C) Copyright 2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

MINIMAL=

ifdef CONFIG_SPL_BUILD
ifdef CONFIG_SPL_INIT_MINIMAL
MINIMAL=y
endif
endif

ifdef MINIMAL
# necessary to create built-in.o
obj- := __dummy__.o
else

obj-$(CONFIG_POWER_PFUZE100)	+= pfuze.o
obj-$(CONFIG_$(SPL_)DM_PMIC_PFUZE100)	+= pfuze.o
obj-y				+= mmc.o

ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_USB_TCPC) += tcpc.o
endif

endif
