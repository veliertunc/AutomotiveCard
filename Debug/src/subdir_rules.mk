################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/TI/ccs1270/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --include_path="D:/TI/ccs1270/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/headers/include" --include_path="D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/include" --include_path="D:/TI/c2000/C2000Ware_5_02_00_00/libraries/math/IQmath/c28/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_suppress=10063 --diag_warning=225 --issue_remarks --verbose_diagnostics --quiet --abi=coffabi --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --include_path="D:/Workspace/C2000/AutomotiveCard/Debug/syscfg" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/%.obj: ../src/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/TI/ccs1270/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --include_path="D:/TI/ccs1270/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/headers/include" --include_path="D:/TI/c2000/C2000Ware_5_02_00_00/device_support/f2803x/common/include" --include_path="D:/TI/c2000/C2000Ware_5_02_00_00/libraries/math/IQmath/c28/include" --advice:performance=all --define=_DEBUG --define=LARGE_MODEL -g --diag_suppress=10063 --diag_warning=225 --issue_remarks --verbose_diagnostics --quiet --abi=coffabi --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --include_path="D:/Workspace/C2000/AutomotiveCard/Debug/syscfg" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


