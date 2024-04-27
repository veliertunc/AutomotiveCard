################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../28030_RAM_lnk.cmd \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/headers/cmd/DSP2803x_Headers_nonBIOS.cmd 

SYSCFG_SRCS += \
../pinmux_64pag.syscfg 

ASM_SRCS += \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_CodeStartBranch.asm \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_usDelay.asm 

C_SRCS += \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_DefaultIsr.c \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/headers/source/DSP2803x_GlobalVariableDefs.c \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_PieCtrl.c \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_PieVect.c \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_Sci.c \
D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_SysCtrl.c \
../main.c \
./syscfg/f2803x_pinmux.c 

GEN_FILES += \
./syscfg/f2803x_pinmux.c 

GEN_MISC_DIRS += \
./syscfg 

C_DEPS += \
./DSP2803x_DefaultIsr.d \
./DSP2803x_GlobalVariableDefs.d \
./DSP2803x_PieCtrl.d \
./DSP2803x_PieVect.d \
./DSP2803x_Sci.d \
./DSP2803x_SysCtrl.d \
./main.d \
./syscfg/f2803x_pinmux.d 

OBJS += \
./DSP2803x_CodeStartBranch.obj \
./DSP2803x_DefaultIsr.obj \
./DSP2803x_GlobalVariableDefs.obj \
./DSP2803x_PieCtrl.obj \
./DSP2803x_PieVect.obj \
./DSP2803x_Sci.obj \
./DSP2803x_SysCtrl.obj \
./DSP2803x_usDelay.obj \
./main.obj \
./syscfg/f2803x_pinmux.obj 

ASM_DEPS += \
./DSP2803x_CodeStartBranch.d \
./DSP2803x_usDelay.d 

GEN_MISC_FILES += \
./syscfg/f2803x_pinmux.h \
./syscfg/PinmuxConfigSummary.csv 

GEN_MISC_DIRS__QUOTED += \
"syscfg" 

OBJS__QUOTED += \
"DSP2803x_CodeStartBranch.obj" \
"DSP2803x_DefaultIsr.obj" \
"DSP2803x_GlobalVariableDefs.obj" \
"DSP2803x_PieCtrl.obj" \
"DSP2803x_PieVect.obj" \
"DSP2803x_Sci.obj" \
"DSP2803x_SysCtrl.obj" \
"DSP2803x_usDelay.obj" \
"main.obj" \
"syscfg\f2803x_pinmux.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\f2803x_pinmux.h" \
"syscfg\PinmuxConfigSummary.csv" 

C_DEPS__QUOTED += \
"DSP2803x_DefaultIsr.d" \
"DSP2803x_GlobalVariableDefs.d" \
"DSP2803x_PieCtrl.d" \
"DSP2803x_PieVect.d" \
"DSP2803x_Sci.d" \
"DSP2803x_SysCtrl.d" \
"main.d" \
"syscfg\f2803x_pinmux.d" 

GEN_FILES__QUOTED += \
"syscfg\f2803x_pinmux.c" 

ASM_DEPS__QUOTED += \
"DSP2803x_CodeStartBranch.d" \
"DSP2803x_usDelay.d" 

ASM_SRCS__QUOTED += \
"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_CodeStartBranch.asm" \
"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_usDelay.asm" 

C_SRCS__QUOTED += \
"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_DefaultIsr.c" \
"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/headers/source/DSP2803x_GlobalVariableDefs.c" \
"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_PieCtrl.c" \
"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_PieVect.c" \
"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_Sci.c" \
"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/source/DSP2803x_SysCtrl.c" \
"../main.c" \
"./syscfg/f2803x_pinmux.c" 

SYSCFG_SRCS__QUOTED += \
"../pinmux_64pag.syscfg" 


