################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/TI/ccs1270/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./syscfg/f2803x_pinmux.obj" \
"./src/DSP2803x_Adc.obj" \
"./src/DSP2803x_CodeStartBranch.obj" \
"./src/DSP2803x_CpuTimers.obj" \
"./src/DSP2803x_DefaultIsr.obj" \
"./src/DSP2803x_ECan.obj" \
"./src/DSP2803x_EQep.obj" \
"./src/DSP2803x_GlobalVariableDefs.obj" \
"./src/DSP2803x_Gpio.obj" \
"./src/DSP2803x_I2C.obj" \
"./src/DSP2803x_PieCtrl.obj" \
"./src/DSP2803x_PieVect.obj" \
"./src/DSP2803x_Sci.obj" \
"./src/DSP2803x_SysCtrl.obj" \
"./src/DSP2803x_usDelay.obj" \
"../28030_RAM_lnk.cmd" \
"../DSP2803x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-lrts2800_ml.lib \
-lIQmath.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
AutomotiveCard.out 

EXE_OUTPUTS__QUOTED += \
"AutomotiveCard.out" 


# All Target
all: AutomotiveCard.out

# Tool invocations
AutomotiveCard.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"D:/TI/ccs1270/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_suppress=10063 --diag_warning=225 --issue_remarks --verbose_diagnostics --quiet --abi=coffabi -z -m"AutomotiveCard.map" --stack_size=0X200 --warn_sections -i"D:/TI/ccs1270/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib" -i"D:/TI/ccs1270/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" -i"D:/Workspace/C2000/AutomotiveCard" -i"D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/lib" -i"D:/TI/c2000/C2000Ware_5_02_00_00/libraries/math/IQmath/c28/lib" --reread_libs --issue_remarks --verbose_diagnostics --xml_link_info="Example_2803x_Pinmux_linkInfo.xml" --entry_point=code_start --rom_model -o "AutomotiveCard.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "syscfg\f2803x_pinmux.obj" "src\DSP2803x_Adc.obj" "src\DSP2803x_CodeStartBranch.obj" "src\DSP2803x_CpuTimers.obj" "src\DSP2803x_DefaultIsr.obj" "src\DSP2803x_ECan.obj" "src\DSP2803x_EQep.obj" "src\DSP2803x_GlobalVariableDefs.obj" "src\DSP2803x_Gpio.obj" "src\DSP2803x_I2C.obj" "src\DSP2803x_PieCtrl.obj" "src\DSP2803x_PieVect.obj" "src\DSP2803x_Sci.obj" "src\DSP2803x_SysCtrl.obj" "src\DSP2803x_usDelay.obj" 
	-$(RM) "main.d" "syscfg\f2803x_pinmux.d" "src\DSP2803x_Adc.d" "src\DSP2803x_CpuTimers.d" "src\DSP2803x_DefaultIsr.d" "src\DSP2803x_ECan.d" "src\DSP2803x_EQep.d" "src\DSP2803x_GlobalVariableDefs.d" "src\DSP2803x_Gpio.d" "src\DSP2803x_I2C.d" "src\DSP2803x_PieCtrl.d" "src\DSP2803x_PieVect.d" "src\DSP2803x_Sci.d" "src\DSP2803x_SysCtrl.d" 
	-$(RM) "src\DSP2803x_CodeStartBranch.d" "src\DSP2803x_usDelay.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

