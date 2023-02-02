################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./DRV830x_SPI.obj" \
"./F2837xD_Adc.obj" \
"./F2837xD_CodeStartBranch.obj" \
"./F2837xD_Dac_setting.obj" \
"./F2837xD_DefaultISR.obj" \
"./F2837xD_GlobalVariableDefs.obj" \
"./F2837xD_Gpio.obj" \
"./F2837xD_PieCtrl.obj" \
"./F2837xD_PieVect.obj" \
"./F2837xD_SysCtrl.obj" \
"./F2837xD_sdfm_drivers.obj" \
"./F2837xD_usDelay.obj" \
"./MonoMtrServo.obj" \
"./config.obj" \
"./drv8301.obj" \
"./drv8305.obj" \
"./utility Src Files/DLOG_4CH_F.obj" \
"../2837xD_RAM_IQMATH_lnk_cpu1.cmd" \
"../F2837xD_Headers_nonBIOS_cpu1.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-lrts2800_fpu32.lib \
-lIQmath_fpu32.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include utility\ Src\ Files/subdir_vars.mk
-include subdir_rules.mk
-include utility\ Src\ Files/subdir_rules.mk
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
MonoMtrServo_379D.out \

EXE_OUTPUTS__QUOTED += \
"MonoMtrServo_379D.out" \

BIN_OUTPUTS += \
MonoMtrServo_379D.hex \

BIN_OUTPUTS__QUOTED += \
"MonoMtrServo_379D.hex" \


# All Target
all: MonoMtrServo_379D.out

# Tool invocations
MonoMtrServo_379D.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O1 --opt_for_speed=5 --fp_mode=relaxed --advice:performance=all --define=_DEBUG --define=CPU1 --define=LARGE_MODEL -g --diag_warning=225 --quiet --abi=coffabi -k --asm_listing -z -m"MonoMtrServo_379D.map" --heap_size=0x800 --stack_size=0x380 --warn_sections -i"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/lib" -i"C:/Users/jason/workspace_v10_4/MonoMtrServo_379D" -i"C:/ti/controlSUITE/libs/math/IQmath/v160/lib" -i"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" -i"C:/Users/jason/workspace_v10_4/MonoMtrServo_379D" -i"C:/Users/jason/workspace_v10_4/MonoMtrServo_379D/source_files" --reread_libs --xml_link_info="HVPM_Sensorless_linkInfo.xml" --rom_model -o "MonoMtrServo_379D.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

MonoMtrServo_379D.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/hex2000" --diag_wrap=off -o "MonoMtrServo_379D.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "DRV830x_SPI.lst" "F2837xD_Adc.lst" "F2837xD_CodeStartBranch.lst" "F2837xD_Dac_setting.lst" "F2837xD_DefaultISR.lst" "F2837xD_GlobalVariableDefs.lst" "F2837xD_Gpio.lst" "F2837xD_PieCtrl.lst" "F2837xD_PieVect.lst" "F2837xD_SysCtrl.lst" "F2837xD_sdfm_drivers.lst" "F2837xD_usDelay.lst" "MonoMtrServo.lst" "config.lst" "drv8301.lst" "drv8305.lst" "utility Src Files/DLOG_4CH_F.lst" 
	-$(RM) "DRV830x_SPI.obj" "F2837xD_Adc.obj" "F2837xD_CodeStartBranch.obj" "F2837xD_Dac_setting.obj" "F2837xD_DefaultISR.obj" "F2837xD_GlobalVariableDefs.obj" "F2837xD_Gpio.obj" "F2837xD_PieCtrl.obj" "F2837xD_PieVect.obj" "F2837xD_SysCtrl.obj" "F2837xD_sdfm_drivers.obj" "F2837xD_usDelay.obj" "MonoMtrServo.obj" "config.obj" "drv8301.obj" "drv8305.obj" "utility Src Files\DLOG_4CH_F.obj" 
	-$(RM) "DRV830x_SPI.d" "F2837xD_Adc.d" "F2837xD_Dac_setting.d" "F2837xD_DefaultISR.d" "F2837xD_GlobalVariableDefs.d" "F2837xD_Gpio.d" "F2837xD_PieCtrl.d" "F2837xD_PieVect.d" "F2837xD_SysCtrl.d" "F2837xD_sdfm_drivers.d" "MonoMtrServo.d" "config.d" "drv8301.d" "drv8305.d" "utility Src Files\DLOG_4CH_F.d" 
	-$(RM) "DRV830x_SPI.asm" "F2837xD_Adc.asm" "F2837xD_CodeStartBranch.asm" "F2837xD_Dac_setting.asm" "F2837xD_DefaultISR.asm" "F2837xD_GlobalVariableDefs.asm" "F2837xD_Gpio.asm" "F2837xD_PieCtrl.asm" "F2837xD_PieVect.asm" "F2837xD_SysCtrl.asm" "F2837xD_sdfm_drivers.asm" "F2837xD_usDelay.asm" "MonoMtrServo.asm" "config.asm" "drv8301.asm" "drv8305.asm" "utility Src Files/DLOG_4CH_F.asm" 
	-$(RM) "F2837xD_CodeStartBranch.d" "F2837xD_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

