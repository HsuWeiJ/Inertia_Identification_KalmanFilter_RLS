################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O1 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --include_path="C:/ti/c2000/C2000Ware_4_01_00_00/libraries/dsp/FPU/c28/include" --include_path="C:/Users/jason/workspace_v10_4/MonoMtrServo_379D/utility Src Files" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v210/F2837xD_headers/include" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v210/F2837xD_common/include" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/v4.3" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --advice:performance=all --define=_DEBUG --define=CPU1 --define=LARGE_MODEL -g --diag_warning=225 --quiet --abi=coffabi -k --asm_listing --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --tmu_support=tmu0 $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O1 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --include_path="C:/ti/c2000/C2000Ware_4_01_00_00/libraries/dsp/FPU/c28/include" --include_path="C:/Users/jason/workspace_v10_4/MonoMtrServo_379D/utility Src Files" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v210/F2837xD_headers/include" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v210/F2837xD_common/include" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/v4.3" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --advice:performance=all --define=_DEBUG --define=CPU1 --define=LARGE_MODEL -g --diag_warning=225 --quiet --abi=coffabi -k --asm_listing --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --tmu_support=tmu0 $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


