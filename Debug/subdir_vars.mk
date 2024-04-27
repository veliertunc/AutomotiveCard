################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../28030_RAM_lnk.cmd \
../DSP2803x_Headers_nonBIOS.cmd 

SYSCFG_SRCS += \
../pinmux_64pag.syscfg 

C_SRCS += \
../main.c \
./syscfg/f2803x_pinmux.c 

GEN_FILES += \
./syscfg/f2803x_pinmux.c 

GEN_MISC_DIRS += \
./syscfg 

C_DEPS += \
./main.d \
./syscfg/f2803x_pinmux.d 

OBJS += \
./main.obj \
./syscfg/f2803x_pinmux.obj 

GEN_MISC_FILES += \
./syscfg/f2803x_pinmux.h \
./syscfg/PinmuxConfigSummary.csv 

GEN_MISC_DIRS__QUOTED += \
"syscfg" 

OBJS__QUOTED += \
"main.obj" \
"syscfg\f2803x_pinmux.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\f2803x_pinmux.h" \
"syscfg\PinmuxConfigSummary.csv" 

C_DEPS__QUOTED += \
"main.d" \
"syscfg\f2803x_pinmux.d" 

GEN_FILES__QUOTED += \
"syscfg\f2803x_pinmux.c" 

C_SRCS__QUOTED += \
"../main.c" \
"./syscfg/f2803x_pinmux.c" 

SYSCFG_SRCS__QUOTED += \
"../pinmux_64pag.syscfg" 


