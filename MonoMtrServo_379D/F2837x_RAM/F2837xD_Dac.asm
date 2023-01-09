;***************************************************************
;* TMS320C2000 G3 C/C++ Codegen                               PC v20.2.0.LTS *
;* Date/Time created: Tue Sep  7 11:06:10 2021                 *
;***************************************************************
	.compiler_opts --abi=coffabi --cla_support=cla0 --float_support=fpu32 --hll_source=on --mem_model:code=flat --mem_model:data=large --object_format=coff --quiet --silicon_errata_fpu1_workaround=off --silicon_version=28 --symdebug:dwarf --symdebug:dwarf_version=3 --tmu_support=tmu0 --vcu_support=vcu2 
	.asg	XAR2, FP

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../F2837xD_Dac.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TMS320C2000 G3 C/C++ Codegen PC v20.2.0.LTS Copyright (c) 1996-2018 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\Users\Motortech\workspace_v10_2\MonoMtrServo_379D\F2837x_RAM")
;**************************************************************
;* CINIT RECORDS                                              *
;**************************************************************
	.sect	".cinit"
	.align	1
	.field  	-1,16
	.field  	_dacAval+0,32
	.bits		0x800,16
			; _dacAval @ 0

	.sect	".cinit"
	.align	1
	.field  	-1,16
	.field  	_dacBval+0,32
	.bits		0x800,16
			; _dacBval @ 0

	.sect	".cinit"
	.align	1
	.field  	-1,16
	.field  	_dacCval+0,32
	.bits		0x800,16
			; _dacCval @ 0

	.sect	".cinit:_DAC_PTR"
	.clink
	.align	1
	.field  	-$C$IR_1,16
	.field  	_DAC_PTR+0,32
	.bits		0,32
			; _DAC_PTR[0] @ 0
	.bits	_DacaRegs,32		; _DAC_PTR[1] @ 32
	.bits	_DacbRegs,32		; _DAC_PTR[2] @ 64
	.bits	_DaccRegs,32		; _DAC_PTR[3] @ 96
$C$IR_1:	.set	8


$C$DW$1	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$1, DW_AT_name("F28x_usDelay")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("_F28x_usDelay")
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$1

	.global	_dacAval
_dacAval:	.usect	".ebss",1,1,0
$C$DW$3	.dwtag  DW_TAG_variable
	.dwattr $C$DW$3, DW_AT_name("dacAval")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("_dacAval")
	.dwattr $C$DW$3, DW_AT_location[DW_OP_addr _dacAval]
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$3, DW_AT_external

	.global	_dacBval
_dacBval:	.usect	".ebss",1,1,0
$C$DW$4	.dwtag  DW_TAG_variable
	.dwattr $C$DW$4, DW_AT_name("dacBval")
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("_dacBval")
	.dwattr $C$DW$4, DW_AT_location[DW_OP_addr _dacBval]
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$4, DW_AT_external

	.global	_dacCval
_dacCval:	.usect	".ebss",1,1,0
$C$DW$5	.dwtag  DW_TAG_variable
	.dwattr $C$DW$5, DW_AT_name("dacCval")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("_dacCval")
	.dwattr $C$DW$5, DW_AT_location[DW_OP_addr _dacCval]
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$5, DW_AT_external

$C$DW$6	.dwtag  DW_TAG_variable
	.dwattr $C$DW$6, DW_AT_name("DacaRegs")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("_DacaRegs")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$6, DW_AT_declaration
	.dwattr $C$DW$6, DW_AT_external

$C$DW$7	.dwtag  DW_TAG_variable
	.dwattr $C$DW$7, DW_AT_name("DacbRegs")
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("_DacbRegs")
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$7, DW_AT_declaration
	.dwattr $C$DW$7, DW_AT_external

$C$DW$8	.dwtag  DW_TAG_variable
	.dwattr $C$DW$8, DW_AT_name("DaccRegs")
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("_DaccRegs")
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$8, DW_AT_declaration
	.dwattr $C$DW$8, DW_AT_external

	.global	_DAC_PTR
_DAC_PTR:	.usect	".ebss:_DAC_PTR",8,1,1
	.clink ".ebss:_DAC_PTR"
$C$DW$9	.dwtag  DW_TAG_variable
	.dwattr $C$DW$9, DW_AT_name("DAC_PTR")
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("_DAC_PTR")
	.dwattr $C$DW$9, DW_AT_location[DW_OP_addr _DAC_PTR]
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$38)
	.dwattr $C$DW$9, DW_AT_external

	.sblock	".ebss"
	.sblock	".ebss:_DAC_PTR"
;	C:\ti\ccs1000\ccs\tools\compiler\ti-cgt-c2000_20.2.0.LTS\bin\opt2000.exe C:\\Users\\MOTORT~1\\AppData\\Local\\Temp\\{6FB6A778-9CD4-45E7-B954-531819754C39} C:\\Users\\MOTORT~1\\AppData\\Local\\Temp\\{842BED37-0521-4D81-A177-0701FF1309EB} 
;	C:\ti\ccs1000\ccs\tools\compiler\ti-cgt-c2000_20.2.0.LTS\bin\ac2000.exe -@C:\\Users\\MOTORT~1\\AppData\\Local\\Temp\\{A1242610-E5C1-4CEB-BE10-3350F2F886D9} 
	.sect	".text"
	.clink
	.global	_configureDAC

$C$DW$10	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$10, DW_AT_name("configureDAC")
	.dwattr $C$DW$10, DW_AT_low_pc(_configureDAC)
	.dwattr $C$DW$10, DW_AT_high_pc(0x00)
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("_configureDAC")
	.dwattr $C$DW$10, DW_AT_external
	.dwattr $C$DW$10, DW_AT_TI_begin_file("../F2837xD_Dac.c")
	.dwattr $C$DW$10, DW_AT_TI_begin_line(0x16)
	.dwattr $C$DW$10, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$10, DW_AT_TI_max_frame_size(-2)
	.dwpsn	file "../F2837xD_Dac.c",line 23,column 1,is_stmt,address _configureDAC,isa 0

	.dwfde $C$DW$CIE, _configureDAC
$C$DW$11	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$11, DW_AT_name("dac_num")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("_dac_num")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$11, DW_AT_location[DW_OP_reg0]


;***************************************************************
;* FNAME: _configureDAC                 FR SIZE:   0           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            0 Parameter,  0 Auto,  0 SOE     *
;***************************************************************

_configureDAC:
;* AR4   assigned to $O$C1
	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
 EALLOW
        CLRC      SXM                   ; [CPU_ALU] 
	.dwpsn	file "../F2837xD_Dac.c",line 25,column 5,is_stmt,isa 0
        MOVL      XAR4,#_DAC_PTR        ; [CPU_ARAU] |25| 
        MOV       ACC,AL << 1           ; [CPU_ALU] |25| 
        ADDL      XAR4,ACC              ; [CPU_ALU] |25| 
        MOVL      XAR4,*+XAR4[0]        ; [CPU_ALU] |25| 
	.dwpsn	file "../F2837xD_Dac.c",line 28,column 5,is_stmt,isa 0
        MOVL      XAR5,#398             ; [CPU_ARAU] |28| 
        SPM       #0                    ; [CPU_ALU] 
        MOVL      ACC,XAR5              ; [CPU_ALU] |28| 
	.dwpsn	file "../F2837xD_Dac.c",line 25,column 5,is_stmt,isa 0
        AND       *+XAR4[1],#0xfffe     ; [CPU_ALU] |25| 
	.dwpsn	file "../F2837xD_Dac.c",line 26,column 5,is_stmt,isa 0
        OR        *+XAR4[4],#0x0001     ; [CPU_ALU] |26| 
	.dwpsn	file "../F2837xD_Dac.c",line 27,column 5,is_stmt,isa 0
        MOV       *+XAR4[3],#0          ; [CPU_ALU] |27| 
	.dwpsn	file "../F2837xD_Dac.c",line 28,column 5,is_stmt,isa 0
$C$DW$12	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$12, DW_AT_low_pc(0x00)
	.dwattr $C$DW$12, DW_AT_name("_F28x_usDelay")
	.dwattr $C$DW$12, DW_AT_TI_call

        LCR       #_F28x_usDelay        ; [CPU_ALU] |28| 
        ; call occurs [#_F28x_usDelay] ; [] |28| 
 EDIS
        SPM       #0                    ; [CPU_ALU] 
$C$DW$13	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$13, DW_AT_low_pc(0x00)
	.dwattr $C$DW$13, DW_AT_TI_return

        LRETR     ; [CPU_ALU] 
        ; return occurs ; [] 
	.dwattr $C$DW$10, DW_AT_TI_end_file("../F2837xD_Dac.c")
	.dwattr $C$DW$10, DW_AT_TI_end_line(0x1e)
	.dwattr $C$DW$10, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$10

;**************************************************************
;* UNDEFINED EXTERNAL REFERENCES                              *
;**************************************************************
	.global	_F28x_usDelay
	.global	_DacaRegs
	.global	_DacbRegs
	.global	_DaccRegs

;***************************************************************
;* TYPE INFORMATION                                            *
;***************************************************************

$C$DW$T$20	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$20, DW_AT_name("DACCTL_BITS")
	.dwattr $C$DW$T$20, DW_AT_byte_size(0x01)
$C$DW$14	.dwtag  DW_TAG_member
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$14, DW_AT_name("DACREFSEL")
	.dwattr $C$DW$14, DW_AT_TI_symbol_name("_DACREFSEL")
	.dwattr $C$DW$14, DW_AT_bit_offset(0x0f)
	.dwattr $C$DW$14, DW_AT_bit_size(0x01)
	.dwattr $C$DW$14, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$14, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$15	.dwtag  DW_TAG_member
	.dwattr $C$DW$15, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$15, DW_AT_name("rsvd1")
	.dwattr $C$DW$15, DW_AT_TI_symbol_name("_rsvd1")
	.dwattr $C$DW$15, DW_AT_bit_offset(0x0e)
	.dwattr $C$DW$15, DW_AT_bit_size(0x01)
	.dwattr $C$DW$15, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$15, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$16	.dwtag  DW_TAG_member
	.dwattr $C$DW$16, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$16, DW_AT_name("LOADMODE")
	.dwattr $C$DW$16, DW_AT_TI_symbol_name("_LOADMODE")
	.dwattr $C$DW$16, DW_AT_bit_offset(0x0d)
	.dwattr $C$DW$16, DW_AT_bit_size(0x01)
	.dwattr $C$DW$16, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$16, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$17	.dwtag  DW_TAG_member
	.dwattr $C$DW$17, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$17, DW_AT_name("rsvd2")
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("_rsvd2")
	.dwattr $C$DW$17, DW_AT_bit_offset(0x0c)
	.dwattr $C$DW$17, DW_AT_bit_size(0x01)
	.dwattr $C$DW$17, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$17, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$18	.dwtag  DW_TAG_member
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$18, DW_AT_name("SYNCSEL")
	.dwattr $C$DW$18, DW_AT_TI_symbol_name("_SYNCSEL")
	.dwattr $C$DW$18, DW_AT_bit_offset(0x08)
	.dwattr $C$DW$18, DW_AT_bit_size(0x04)
	.dwattr $C$DW$18, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$18, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$19	.dwtag  DW_TAG_member
	.dwattr $C$DW$19, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$19, DW_AT_name("rsvd3")
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("_rsvd3")
	.dwattr $C$DW$19, DW_AT_bit_offset(0x00)
	.dwattr $C$DW$19, DW_AT_bit_size(0x08)
	.dwattr $C$DW$19, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$19, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$20


$C$DW$T$21	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$21, DW_AT_name("DACCTL_REG")
	.dwattr $C$DW$T$21, DW_AT_byte_size(0x01)
$C$DW$20	.dwtag  DW_TAG_member
	.dwattr $C$DW$20, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$20, DW_AT_name("all")
	.dwattr $C$DW$20, DW_AT_TI_symbol_name("_all")
	.dwattr $C$DW$20, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$20, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$21	.dwtag  DW_TAG_member
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$21, DW_AT_name("bit")
	.dwattr $C$DW$21, DW_AT_TI_symbol_name("_bit")
	.dwattr $C$DW$21, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$21, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$21


$C$DW$T$22	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$22, DW_AT_name("DACLOCK_BITS")
	.dwattr $C$DW$T$22, DW_AT_byte_size(0x01)
$C$DW$22	.dwtag  DW_TAG_member
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$22, DW_AT_name("DACCTL")
	.dwattr $C$DW$22, DW_AT_TI_symbol_name("_DACCTL")
	.dwattr $C$DW$22, DW_AT_bit_offset(0x0f)
	.dwattr $C$DW$22, DW_AT_bit_size(0x01)
	.dwattr $C$DW$22, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$22, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$23	.dwtag  DW_TAG_member
	.dwattr $C$DW$23, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$23, DW_AT_name("DACVAL")
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("_DACVAL")
	.dwattr $C$DW$23, DW_AT_bit_offset(0x0e)
	.dwattr $C$DW$23, DW_AT_bit_size(0x01)
	.dwattr $C$DW$23, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$23, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$24	.dwtag  DW_TAG_member
	.dwattr $C$DW$24, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$24, DW_AT_name("DACOUTEN")
	.dwattr $C$DW$24, DW_AT_TI_symbol_name("_DACOUTEN")
	.dwattr $C$DW$24, DW_AT_bit_offset(0x0d)
	.dwattr $C$DW$24, DW_AT_bit_size(0x01)
	.dwattr $C$DW$24, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$24, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$25	.dwtag  DW_TAG_member
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$25, DW_AT_name("rsvd1")
	.dwattr $C$DW$25, DW_AT_TI_symbol_name("_rsvd1")
	.dwattr $C$DW$25, DW_AT_bit_offset(0x00)
	.dwattr $C$DW$25, DW_AT_bit_size(0x0d)
	.dwattr $C$DW$25, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$25, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$22


$C$DW$T$23	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$23, DW_AT_name("DACLOCK_REG")
	.dwattr $C$DW$T$23, DW_AT_byte_size(0x01)
$C$DW$26	.dwtag  DW_TAG_member
	.dwattr $C$DW$26, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$26, DW_AT_name("all")
	.dwattr $C$DW$26, DW_AT_TI_symbol_name("_all")
	.dwattr $C$DW$26, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$26, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$27	.dwtag  DW_TAG_member
	.dwattr $C$DW$27, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$27, DW_AT_name("bit")
	.dwattr $C$DW$27, DW_AT_TI_symbol_name("_bit")
	.dwattr $C$DW$27, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$27, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$23


$C$DW$T$24	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$24, DW_AT_name("DACOUTEN_BITS")
	.dwattr $C$DW$T$24, DW_AT_byte_size(0x01)
$C$DW$28	.dwtag  DW_TAG_member
	.dwattr $C$DW$28, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$28, DW_AT_name("DACOUTEN")
	.dwattr $C$DW$28, DW_AT_TI_symbol_name("_DACOUTEN")
	.dwattr $C$DW$28, DW_AT_bit_offset(0x0f)
	.dwattr $C$DW$28, DW_AT_bit_size(0x01)
	.dwattr $C$DW$28, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$28, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$29	.dwtag  DW_TAG_member
	.dwattr $C$DW$29, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$29, DW_AT_name("rsvd1")
	.dwattr $C$DW$29, DW_AT_TI_symbol_name("_rsvd1")
	.dwattr $C$DW$29, DW_AT_bit_offset(0x00)
	.dwattr $C$DW$29, DW_AT_bit_size(0x0f)
	.dwattr $C$DW$29, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$29, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$24


$C$DW$T$25	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$25, DW_AT_name("DACOUTEN_REG")
	.dwattr $C$DW$T$25, DW_AT_byte_size(0x01)
$C$DW$30	.dwtag  DW_TAG_member
	.dwattr $C$DW$30, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$30, DW_AT_name("all")
	.dwattr $C$DW$30, DW_AT_TI_symbol_name("_all")
	.dwattr $C$DW$30, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$30, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$31	.dwtag  DW_TAG_member
	.dwattr $C$DW$31, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$31, DW_AT_name("bit")
	.dwattr $C$DW$31, DW_AT_TI_symbol_name("_bit")
	.dwattr $C$DW$31, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$31, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$25


$C$DW$T$26	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$26, DW_AT_name("DACREV_BITS")
	.dwattr $C$DW$T$26, DW_AT_byte_size(0x01)
$C$DW$32	.dwtag  DW_TAG_member
	.dwattr $C$DW$32, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$32, DW_AT_name("REV")
	.dwattr $C$DW$32, DW_AT_TI_symbol_name("_REV")
	.dwattr $C$DW$32, DW_AT_bit_offset(0x08)
	.dwattr $C$DW$32, DW_AT_bit_size(0x08)
	.dwattr $C$DW$32, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$32, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$33	.dwtag  DW_TAG_member
	.dwattr $C$DW$33, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$33, DW_AT_name("rsvd1")
	.dwattr $C$DW$33, DW_AT_TI_symbol_name("_rsvd1")
	.dwattr $C$DW$33, DW_AT_bit_offset(0x00)
	.dwattr $C$DW$33, DW_AT_bit_size(0x08)
	.dwattr $C$DW$33, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$33, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$26


$C$DW$T$27	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$27, DW_AT_name("DACREV_REG")
	.dwattr $C$DW$T$27, DW_AT_byte_size(0x01)
$C$DW$34	.dwtag  DW_TAG_member
	.dwattr $C$DW$34, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$34, DW_AT_name("all")
	.dwattr $C$DW$34, DW_AT_TI_symbol_name("_all")
	.dwattr $C$DW$34, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$34, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$35	.dwtag  DW_TAG_member
	.dwattr $C$DW$35, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$35, DW_AT_name("bit")
	.dwattr $C$DW$35, DW_AT_TI_symbol_name("_bit")
	.dwattr $C$DW$35, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$35, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$27


$C$DW$T$28	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$28, DW_AT_name("DACTRIM_BITS")
	.dwattr $C$DW$T$28, DW_AT_byte_size(0x01)
$C$DW$36	.dwtag  DW_TAG_member
	.dwattr $C$DW$36, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$36, DW_AT_name("OFFSET_TRIM")
	.dwattr $C$DW$36, DW_AT_TI_symbol_name("_OFFSET_TRIM")
	.dwattr $C$DW$36, DW_AT_bit_offset(0x08)
	.dwattr $C$DW$36, DW_AT_bit_size(0x08)
	.dwattr $C$DW$36, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$36, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$37	.dwtag  DW_TAG_member
	.dwattr $C$DW$37, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$37, DW_AT_name("rsvd1")
	.dwattr $C$DW$37, DW_AT_TI_symbol_name("_rsvd1")
	.dwattr $C$DW$37, DW_AT_bit_offset(0x04)
	.dwattr $C$DW$37, DW_AT_bit_size(0x04)
	.dwattr $C$DW$37, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$37, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$38	.dwtag  DW_TAG_member
	.dwattr $C$DW$38, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$38, DW_AT_name("rsvd2")
	.dwattr $C$DW$38, DW_AT_TI_symbol_name("_rsvd2")
	.dwattr $C$DW$38, DW_AT_bit_offset(0x00)
	.dwattr $C$DW$38, DW_AT_bit_size(0x04)
	.dwattr $C$DW$38, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$38, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$28


$C$DW$T$29	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$29, DW_AT_name("DACTRIM_REG")
	.dwattr $C$DW$T$29, DW_AT_byte_size(0x01)
$C$DW$39	.dwtag  DW_TAG_member
	.dwattr $C$DW$39, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$39, DW_AT_name("all")
	.dwattr $C$DW$39, DW_AT_TI_symbol_name("_all")
	.dwattr $C$DW$39, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$39, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$40	.dwtag  DW_TAG_member
	.dwattr $C$DW$40, DW_AT_type(*$C$DW$T$28)
	.dwattr $C$DW$40, DW_AT_name("bit")
	.dwattr $C$DW$40, DW_AT_TI_symbol_name("_bit")
	.dwattr $C$DW$40, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$40, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$29


$C$DW$T$30	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$30, DW_AT_name("DACVALA_BITS")
	.dwattr $C$DW$T$30, DW_AT_byte_size(0x01)
$C$DW$41	.dwtag  DW_TAG_member
	.dwattr $C$DW$41, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$41, DW_AT_name("DACVALA")
	.dwattr $C$DW$41, DW_AT_TI_symbol_name("_DACVALA")
	.dwattr $C$DW$41, DW_AT_bit_offset(0x04)
	.dwattr $C$DW$41, DW_AT_bit_size(0x0c)
	.dwattr $C$DW$41, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$41, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$42	.dwtag  DW_TAG_member
	.dwattr $C$DW$42, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$42, DW_AT_name("rsvd1")
	.dwattr $C$DW$42, DW_AT_TI_symbol_name("_rsvd1")
	.dwattr $C$DW$42, DW_AT_bit_offset(0x00)
	.dwattr $C$DW$42, DW_AT_bit_size(0x04)
	.dwattr $C$DW$42, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$42, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$30


$C$DW$T$31	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$31, DW_AT_name("DACVALA_REG")
	.dwattr $C$DW$T$31, DW_AT_byte_size(0x01)
$C$DW$43	.dwtag  DW_TAG_member
	.dwattr $C$DW$43, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$43, DW_AT_name("all")
	.dwattr $C$DW$43, DW_AT_TI_symbol_name("_all")
	.dwattr $C$DW$43, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$43, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$44	.dwtag  DW_TAG_member
	.dwattr $C$DW$44, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$44, DW_AT_name("bit")
	.dwattr $C$DW$44, DW_AT_TI_symbol_name("_bit")
	.dwattr $C$DW$44, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$44, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$31


$C$DW$T$32	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$32, DW_AT_name("DACVALS_BITS")
	.dwattr $C$DW$T$32, DW_AT_byte_size(0x01)
$C$DW$45	.dwtag  DW_TAG_member
	.dwattr $C$DW$45, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$45, DW_AT_name("DACVALS")
	.dwattr $C$DW$45, DW_AT_TI_symbol_name("_DACVALS")
	.dwattr $C$DW$45, DW_AT_bit_offset(0x04)
	.dwattr $C$DW$45, DW_AT_bit_size(0x0c)
	.dwattr $C$DW$45, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$45, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$46	.dwtag  DW_TAG_member
	.dwattr $C$DW$46, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$46, DW_AT_name("rsvd1")
	.dwattr $C$DW$46, DW_AT_TI_symbol_name("_rsvd1")
	.dwattr $C$DW$46, DW_AT_bit_offset(0x00)
	.dwattr $C$DW$46, DW_AT_bit_size(0x04)
	.dwattr $C$DW$46, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$46, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$32


$C$DW$T$33	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$33, DW_AT_name("DACVALS_REG")
	.dwattr $C$DW$T$33, DW_AT_byte_size(0x01)
$C$DW$47	.dwtag  DW_TAG_member
	.dwattr $C$DW$47, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$47, DW_AT_name("all")
	.dwattr $C$DW$47, DW_AT_TI_symbol_name("_all")
	.dwattr $C$DW$47, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$47, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$48	.dwtag  DW_TAG_member
	.dwattr $C$DW$48, DW_AT_type(*$C$DW$T$32)
	.dwattr $C$DW$48, DW_AT_name("bit")
	.dwattr $C$DW$48, DW_AT_TI_symbol_name("_bit")
	.dwattr $C$DW$48, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$48, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$33


$C$DW$T$34	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$34, DW_AT_name("DAC_REGS")
	.dwattr $C$DW$T$34, DW_AT_byte_size(0x08)
$C$DW$49	.dwtag  DW_TAG_member
	.dwattr $C$DW$49, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$49, DW_AT_name("DACREV")
	.dwattr $C$DW$49, DW_AT_TI_symbol_name("_DACREV")
	.dwattr $C$DW$49, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$49, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$50	.dwtag  DW_TAG_member
	.dwattr $C$DW$50, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$50, DW_AT_name("DACCTL")
	.dwattr $C$DW$50, DW_AT_TI_symbol_name("_DACCTL")
	.dwattr $C$DW$50, DW_AT_data_member_location[DW_OP_plus_uconst 0x1]
	.dwattr $C$DW$50, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$51	.dwtag  DW_TAG_member
	.dwattr $C$DW$51, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$51, DW_AT_name("DACVALA")
	.dwattr $C$DW$51, DW_AT_TI_symbol_name("_DACVALA")
	.dwattr $C$DW$51, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$51, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$52	.dwtag  DW_TAG_member
	.dwattr $C$DW$52, DW_AT_type(*$C$DW$T$33)
	.dwattr $C$DW$52, DW_AT_name("DACVALS")
	.dwattr $C$DW$52, DW_AT_TI_symbol_name("_DACVALS")
	.dwattr $C$DW$52, DW_AT_data_member_location[DW_OP_plus_uconst 0x3]
	.dwattr $C$DW$52, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$53	.dwtag  DW_TAG_member
	.dwattr $C$DW$53, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$53, DW_AT_name("DACOUTEN")
	.dwattr $C$DW$53, DW_AT_TI_symbol_name("_DACOUTEN")
	.dwattr $C$DW$53, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$53, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$54	.dwtag  DW_TAG_member
	.dwattr $C$DW$54, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$54, DW_AT_name("DACLOCK")
	.dwattr $C$DW$54, DW_AT_TI_symbol_name("_DACLOCK")
	.dwattr $C$DW$54, DW_AT_data_member_location[DW_OP_plus_uconst 0x5]
	.dwattr $C$DW$54, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$55	.dwtag  DW_TAG_member
	.dwattr $C$DW$55, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$55, DW_AT_name("DACTRIM")
	.dwattr $C$DW$55, DW_AT_TI_symbol_name("_DACTRIM")
	.dwattr $C$DW$55, DW_AT_data_member_location[DW_OP_plus_uconst 0x6]
	.dwattr $C$DW$55, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$56	.dwtag  DW_TAG_member
	.dwattr $C$DW$56, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$56, DW_AT_name("rsvd1")
	.dwattr $C$DW$56, DW_AT_TI_symbol_name("_rsvd1")
	.dwattr $C$DW$56, DW_AT_data_member_location[DW_OP_plus_uconst 0x7]
	.dwattr $C$DW$56, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$34

$C$DW$57	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$57, DW_AT_type(*$C$DW$T$34)

$C$DW$T$36	.dwtag  DW_TAG_volatile_type
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$57)

$C$DW$T$37	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$T$37, DW_AT_address_class(0x20)


$C$DW$T$38	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$38, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$T$38, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$38, DW_AT_byte_size(0x08)
$C$DW$58	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$58, DW_AT_upper_bound(0x03)

	.dwendtag $C$DW$T$38

$C$DW$T$2	.dwtag  DW_TAG_unspecified_type
	.dwattr $C$DW$T$2, DW_AT_name("void")

$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)

$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)

$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)

$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x01)

$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x01)

$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x01)

$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x01)

$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x01)

$C$DW$T$19	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$19, DW_AT_name("Uint16")
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$19, DW_AT_language(DW_LANG_C)

$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x02)

$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x02)

$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x04)

$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x04)

$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x02)

$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x02)

$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x04)

	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)

;***************************************************************
;* DWARF CIE ENTRIES                                           *
;***************************************************************

$C$DW$CIE	.dwcie 26
	.dwcfi	cfa_register, 20
	.dwcfi	cfa_offset, 0
	.dwcfi	same_value, 28
	.dwcfi	same_value, 6
	.dwcfi	same_value, 7
	.dwcfi	same_value, 8
	.dwcfi	same_value, 9
	.dwcfi	same_value, 10
	.dwcfi	same_value, 11
	.dwcfi	same_value, 59
	.dwcfi	same_value, 63
	.dwcfi	same_value, 67
	.dwcfi	same_value, 71
	.dwendentry

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

$C$DW$59	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$59, DW_AT_name("AL")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_reg0]

$C$DW$60	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$60, DW_AT_name("AH")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_reg1]

$C$DW$61	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$61, DW_AT_name("PL")
	.dwattr $C$DW$61, DW_AT_location[DW_OP_reg2]

$C$DW$62	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$62, DW_AT_name("PH")
	.dwattr $C$DW$62, DW_AT_location[DW_OP_reg3]

$C$DW$63	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$63, DW_AT_name("SP")
	.dwattr $C$DW$63, DW_AT_location[DW_OP_reg20]

$C$DW$64	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$64, DW_AT_name("XT")
	.dwattr $C$DW$64, DW_AT_location[DW_OP_reg21]

$C$DW$65	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$65, DW_AT_name("T")
	.dwattr $C$DW$65, DW_AT_location[DW_OP_reg22]

$C$DW$66	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$66, DW_AT_name("ST0")
	.dwattr $C$DW$66, DW_AT_location[DW_OP_reg23]

$C$DW$67	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$67, DW_AT_name("ST1")
	.dwattr $C$DW$67, DW_AT_location[DW_OP_reg24]

$C$DW$68	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$68, DW_AT_name("PC")
	.dwattr $C$DW$68, DW_AT_location[DW_OP_reg25]

$C$DW$69	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$69, DW_AT_name("RPC")
	.dwattr $C$DW$69, DW_AT_location[DW_OP_reg26]

$C$DW$70	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$70, DW_AT_name("FP")
	.dwattr $C$DW$70, DW_AT_location[DW_OP_reg28]

$C$DW$71	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$71, DW_AT_name("DP")
	.dwattr $C$DW$71, DW_AT_location[DW_OP_reg29]

$C$DW$72	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$72, DW_AT_name("SXM")
	.dwattr $C$DW$72, DW_AT_location[DW_OP_reg30]

$C$DW$73	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$73, DW_AT_name("PM")
	.dwattr $C$DW$73, DW_AT_location[DW_OP_reg31]

$C$DW$74	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$74, DW_AT_name("OVM")
	.dwattr $C$DW$74, DW_AT_location[DW_OP_regx 0x20]

$C$DW$75	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$75, DW_AT_name("PAGE0")
	.dwattr $C$DW$75, DW_AT_location[DW_OP_regx 0x21]

$C$DW$76	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$76, DW_AT_name("AMODE")
	.dwattr $C$DW$76, DW_AT_location[DW_OP_regx 0x22]

$C$DW$77	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$77, DW_AT_name("EALLOW")
	.dwattr $C$DW$77, DW_AT_location[DW_OP_regx 0x4e]

$C$DW$78	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$78, DW_AT_name("INTM")
	.dwattr $C$DW$78, DW_AT_location[DW_OP_regx 0x23]

$C$DW$79	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$79, DW_AT_name("IFR")
	.dwattr $C$DW$79, DW_AT_location[DW_OP_regx 0x24]

$C$DW$80	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$80, DW_AT_name("IER")
	.dwattr $C$DW$80, DW_AT_location[DW_OP_regx 0x25]

$C$DW$81	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$81, DW_AT_name("V")
	.dwattr $C$DW$81, DW_AT_location[DW_OP_regx 0x26]

$C$DW$82	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$82, DW_AT_name("PSEUDOH")
	.dwattr $C$DW$82, DW_AT_location[DW_OP_regx 0x4c]

$C$DW$83	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$83, DW_AT_name("VOL")
	.dwattr $C$DW$83, DW_AT_location[DW_OP_regx 0x4d]

$C$DW$84	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$84, DW_AT_name("AR0")
	.dwattr $C$DW$84, DW_AT_location[DW_OP_reg4]

$C$DW$85	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$85, DW_AT_name("XAR0")
	.dwattr $C$DW$85, DW_AT_location[DW_OP_reg5]

$C$DW$86	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$86, DW_AT_name("AR1")
	.dwattr $C$DW$86, DW_AT_location[DW_OP_reg6]

$C$DW$87	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$87, DW_AT_name("XAR1")
	.dwattr $C$DW$87, DW_AT_location[DW_OP_reg7]

$C$DW$88	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$88, DW_AT_name("AR2")
	.dwattr $C$DW$88, DW_AT_location[DW_OP_reg8]

$C$DW$89	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$89, DW_AT_name("XAR2")
	.dwattr $C$DW$89, DW_AT_location[DW_OP_reg9]

$C$DW$90	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$90, DW_AT_name("AR3")
	.dwattr $C$DW$90, DW_AT_location[DW_OP_reg10]

$C$DW$91	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$91, DW_AT_name("XAR3")
	.dwattr $C$DW$91, DW_AT_location[DW_OP_reg11]

$C$DW$92	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$92, DW_AT_name("AR4")
	.dwattr $C$DW$92, DW_AT_location[DW_OP_reg12]

$C$DW$93	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$93, DW_AT_name("XAR4")
	.dwattr $C$DW$93, DW_AT_location[DW_OP_reg13]

$C$DW$94	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$94, DW_AT_name("AR5")
	.dwattr $C$DW$94, DW_AT_location[DW_OP_reg14]

$C$DW$95	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$95, DW_AT_name("XAR5")
	.dwattr $C$DW$95, DW_AT_location[DW_OP_reg15]

$C$DW$96	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$96, DW_AT_name("AR6")
	.dwattr $C$DW$96, DW_AT_location[DW_OP_reg16]

$C$DW$97	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$97, DW_AT_name("XAR6")
	.dwattr $C$DW$97, DW_AT_location[DW_OP_reg17]

$C$DW$98	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$98, DW_AT_name("AR7")
	.dwattr $C$DW$98, DW_AT_location[DW_OP_reg18]

$C$DW$99	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$99, DW_AT_name("XAR7")
	.dwattr $C$DW$99, DW_AT_location[DW_OP_reg19]

$C$DW$100	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$100, DW_AT_name("R0H")
	.dwattr $C$DW$100, DW_AT_location[DW_OP_regx 0x2b]

$C$DW$101	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$101, DW_AT_name("R1H")
	.dwattr $C$DW$101, DW_AT_location[DW_OP_regx 0x2f]

$C$DW$102	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$102, DW_AT_name("R2H")
	.dwattr $C$DW$102, DW_AT_location[DW_OP_regx 0x33]

$C$DW$103	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$103, DW_AT_name("R3H")
	.dwattr $C$DW$103, DW_AT_location[DW_OP_regx 0x37]

$C$DW$104	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$104, DW_AT_name("R4H")
	.dwattr $C$DW$104, DW_AT_location[DW_OP_regx 0x3b]

$C$DW$105	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$105, DW_AT_name("R5H")
	.dwattr $C$DW$105, DW_AT_location[DW_OP_regx 0x3f]

$C$DW$106	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$106, DW_AT_name("R6H")
	.dwattr $C$DW$106, DW_AT_location[DW_OP_regx 0x43]

$C$DW$107	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$107, DW_AT_name("R7H")
	.dwattr $C$DW$107, DW_AT_location[DW_OP_regx 0x47]

$C$DW$108	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$108, DW_AT_name("RB")
	.dwattr $C$DW$108, DW_AT_location[DW_OP_regx 0x4a]

$C$DW$109	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$109, DW_AT_name("STF")
	.dwattr $C$DW$109, DW_AT_location[DW_OP_regx 0x28]

$C$DW$110	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$110, DW_AT_name("FPUHAZ")
	.dwattr $C$DW$110, DW_AT_location[DW_OP_reg27]

$C$DW$111	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$111, DW_AT_name("STF_HWDIV")
	.dwattr $C$DW$111, DW_AT_location[DW_OP_regx 0x4f]

$C$DW$112	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$112, DW_AT_name("VCRC")
	.dwattr $C$DW$112, DW_AT_location[DW_OP_regx 0x50]

$C$DW$113	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$113, DW_AT_name("VSTATUS")
	.dwattr $C$DW$113, DW_AT_location[DW_OP_regx 0x51]

	.dwendtag $C$DW$CU

