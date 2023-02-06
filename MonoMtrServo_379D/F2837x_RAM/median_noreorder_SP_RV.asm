;***************************************************************
;* TMS320C2000 G3 C/C++ Codegen                               PC v20.2.5.LTS *
;* Date/Time created: Thu Feb  2 17:04:35 2023                 *
;***************************************************************
	.compiler_opts --abi=coffabi --cla_support=cla0 --float_support=fpu32 --hll_source=on --mem_model:code=flat --mem_model:data=large --object_format=coff --quiet --silicon_errata_fpu1_workaround=off --silicon_version=28 --symdebug:dwarf --symdebug:dwarf_version=3 --tmu_support=tmu0 --vcu_support=vcu2 
	.asg	XAR2, FP

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../vector/median_noreorder_SP_RV.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TMS320C2000 G3 C/C++ Codegen PC v20.2.5.LTS Copyright (c) 1996-2018 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\Users\jason\workspace_v10_4\MonoMtrServo_379D\F2837x_RAM")

$C$DW$1	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$1, DW_AT_name("memcpy_fast")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("_memcpy_fast")
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$3)

$C$DW$3	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$20)

$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$23)

	.dwendtag $C$DW$1


$C$DW$5	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$5, DW_AT_name("median_SP_RV")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("_median_SP_RV")
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$5, DW_AT_declaration
	.dwattr $C$DW$5, DW_AT_external
$C$DW$6	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$27)

$C$DW$7	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$23)

	.dwendtag $C$DW$5

;	C:\ti\ccs1040\ccs\tools\compiler\ti-cgt-c2000_20.2.5.LTS\bin\opt2000.exe C:\\Users\\jason\\AppData\\Local\\Temp\\{D93A3B01-B770-48EB-9C9D-50B308C734E7} C:\\Users\\jason\\AppData\\Local\\Temp\\{BE1F364A-1486-4FB1-AFF4-BD07161C831F} 
;	C:\ti\ccs1040\ccs\tools\compiler\ti-cgt-c2000_20.2.5.LTS\bin\ac2000.exe -@C:\\Users\\jason\\AppData\\Local\\Temp\\{62176855-CBFC-4DA5-871D-548DCCE8937B} 
	.sect	".text"
	.clink
	.global	_median_noreorder_SP_RV

$C$DW$8	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$8, DW_AT_name("median_noreorder_SP_RV")
	.dwattr $C$DW$8, DW_AT_low_pc(_median_noreorder_SP_RV)
	.dwattr $C$DW$8, DW_AT_high_pc(0x00)
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("_median_noreorder_SP_RV")
	.dwattr $C$DW$8, DW_AT_external
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$8, DW_AT_TI_begin_file("../vector/median_noreorder_SP_RV.c")
	.dwattr $C$DW$8, DW_AT_TI_begin_line(0x2e)
	.dwattr $C$DW$8, DW_AT_TI_begin_column(0x07)
	.dwattr $C$DW$8, DW_AT_TI_max_frame_size(-516)
	.dwpsn	file "../vector/median_noreorder_SP_RV.c",line 47,column 1,is_stmt,address _median_noreorder_SP_RV,isa 0

	.dwfde $C$DW$CIE, _median_noreorder_SP_RV
$C$DW$9	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$9, DW_AT_name("x")
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("_x")
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$9, DW_AT_location[DW_OP_reg12]

$C$DW$10	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$10, DW_AT_name("N")
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("_N")
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$10, DW_AT_location[DW_OP_reg0]


;***************************************************************
;* FNAME: _median_noreorder_SP_RV       FR SIZE: 514           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            0 Parameter, 512 Auto,  2 SOE     *
;***************************************************************

_median_noreorder_SP_RV:
$C$DW$11	.dwtag  DW_TAG_variable
	.dwattr $C$DW$11, DW_AT_name("x_copy")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("_x_copy")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$34)
	.dwattr $C$DW$11, DW_AT_location[DW_OP_breg20 -512]

;* AR1   assigned to _N
$C$DW$12	.dwtag  DW_TAG_variable
	.dwattr $C$DW$12, DW_AT_name("N")
	.dwattr $C$DW$12, DW_AT_TI_symbol_name("_N")
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$12, DW_AT_location[DW_OP_reg6]

	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
        MOVL      *SP++,XAR1            ; [CPU_ALU] 
	.dwcfi	save_reg_to_mem, 7, 2
	.dwcfi	cfa_offset, -4
        ADD       SP,#512               ; [CPU_ALU] 
	.dwcfi	cfa_offset, -516
	.dwpsn	file "../vector/median_noreorder_SP_RV.c",line 50,column 5,is_stmt,isa 0
        MOVZ      AR6,SP                ; [CPU_ALU] |50| 
	.dwpsn	file "../vector/median_noreorder_SP_RV.c",line 47,column 1,is_stmt,isa 0
        MOVZ      AR1,AL                ; [CPU_ALU] |47| 
	.dwpsn	file "../vector/median_noreorder_SP_RV.c",line 50,column 5,is_stmt,isa 0
        ADD       AR6,#-512             ; [CPU_ALU] |50| 
	.dwpsn	file "../vector/median_noreorder_SP_RV.c",line 47,column 1,is_stmt,isa 0
        MOVL      XAR5,XAR4             ; [CPU_ALU] |47| 
	.dwpsn	file "../vector/median_noreorder_SP_RV.c",line 50,column 5,is_stmt,isa 0
        MOV       ACC,AR1 << #1         ; [CPU_ALU] |50| 
        MOVZ      AR4,AR6               ; [CPU_ALU] |50| 
$C$DW$13	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$13, DW_AT_low_pc(0x00)
	.dwattr $C$DW$13, DW_AT_name("_memcpy_fast")
	.dwattr $C$DW$13, DW_AT_TI_call

        LCR       #_memcpy_fast         ; [CPU_ALU] |50| 
        ; call occurs [#_memcpy_fast] ; [] |50| 
	.dwpsn	file "../vector/median_noreorder_SP_RV.c",line 51,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_ALU] |51| 
        ADD       AR4,#-512             ; [CPU_ALU] |51| 
        MOV       AL,AR1                ; [CPU_ALU] |51| 
        MOVZ      AR4,AR4               ; [CPU_ALU] |51| 
$C$DW$14	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$14, DW_AT_low_pc(0x00)
	.dwattr $C$DW$14, DW_AT_name("_median_SP_RV")
	.dwattr $C$DW$14, DW_AT_TI_call

        LCR       #_median_SP_RV        ; [CPU_ALU] |51| 
        ; call occurs [#_median_SP_RV] ; [] |51| 
        ADD       SP,#-512              ; [CPU_ALU] 
	.dwcfi	cfa_offset, -4
        MOVL      XAR1,*--SP            ; [CPU_ALU] 
	.dwcfi	cfa_offset, -2
	.dwcfi	restore_reg, 7
$C$DW$15	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$15, DW_AT_low_pc(0x00)
	.dwattr $C$DW$15, DW_AT_TI_return

        LRETR     ; [CPU_ALU] 
        ; return occurs ; [] 
	.dwattr $C$DW$8, DW_AT_TI_end_file("../vector/median_noreorder_SP_RV.c")
	.dwattr $C$DW$8, DW_AT_TI_end_line(0x35)
	.dwattr $C$DW$8, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$8

;**************************************************************
;* UNDEFINED EXTERNAL REFERENCES                              *
;**************************************************************
	.global	_memcpy_fast
	.global	_median_SP_RV

;***************************************************************
;* TYPE INFORMATION                                            *
;***************************************************************
$C$DW$T$2	.dwtag  DW_TAG_unspecified_type
	.dwattr $C$DW$T$2, DW_AT_name("void")

$C$DW$T$3	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$3, DW_AT_type(*$C$DW$T$2)
	.dwattr $C$DW$T$3, DW_AT_address_class(0x20)

$C$DW$16	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$16, DW_AT_type(*$C$DW$T$2)

$C$DW$T$19	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$16)

$C$DW$T$20	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$T$20, DW_AT_address_class(0x20)

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

$C$DW$T$21	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$21, DW_AT_name("__uint16_t")
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$21, DW_AT_language(DW_LANG_C)

$C$DW$T$22	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$22, DW_AT_name("uint16_t")
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$T$22, DW_AT_language(DW_LANG_C)

$C$DW$17	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$17, DW_AT_type(*$C$DW$T$22)

$C$DW$T$23	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$17)

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

$C$DW$T$27	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$T$27, DW_AT_address_class(0x20)

$C$DW$18	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$16)

$C$DW$T$30	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$30, DW_AT_type(*$C$DW$18)

$C$DW$T$31	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$31, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$T$31, DW_AT_address_class(0x20)


$C$DW$T$34	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$34, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$T$34, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$34, DW_AT_byte_size(0x200)
$C$DW$19	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$19, DW_AT_upper_bound(0xff)

	.dwendtag $C$DW$T$34

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

$C$DW$20	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$20, DW_AT_name("AL")
	.dwattr $C$DW$20, DW_AT_location[DW_OP_reg0]

$C$DW$21	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$21, DW_AT_name("AH")
	.dwattr $C$DW$21, DW_AT_location[DW_OP_reg1]

$C$DW$22	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$22, DW_AT_name("PL")
	.dwattr $C$DW$22, DW_AT_location[DW_OP_reg2]

$C$DW$23	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$23, DW_AT_name("PH")
	.dwattr $C$DW$23, DW_AT_location[DW_OP_reg3]

$C$DW$24	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$24, DW_AT_name("SP")
	.dwattr $C$DW$24, DW_AT_location[DW_OP_reg20]

$C$DW$25	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$25, DW_AT_name("XT")
	.dwattr $C$DW$25, DW_AT_location[DW_OP_reg21]

$C$DW$26	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$26, DW_AT_name("T")
	.dwattr $C$DW$26, DW_AT_location[DW_OP_reg22]

$C$DW$27	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$27, DW_AT_name("ST0")
	.dwattr $C$DW$27, DW_AT_location[DW_OP_reg23]

$C$DW$28	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$28, DW_AT_name("ST1")
	.dwattr $C$DW$28, DW_AT_location[DW_OP_reg24]

$C$DW$29	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$29, DW_AT_name("PC")
	.dwattr $C$DW$29, DW_AT_location[DW_OP_reg25]

$C$DW$30	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$30, DW_AT_name("RPC")
	.dwattr $C$DW$30, DW_AT_location[DW_OP_reg26]

$C$DW$31	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$31, DW_AT_name("FP")
	.dwattr $C$DW$31, DW_AT_location[DW_OP_reg28]

$C$DW$32	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$32, DW_AT_name("DP")
	.dwattr $C$DW$32, DW_AT_location[DW_OP_reg29]

$C$DW$33	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$33, DW_AT_name("SXM")
	.dwattr $C$DW$33, DW_AT_location[DW_OP_reg30]

$C$DW$34	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$34, DW_AT_name("PM")
	.dwattr $C$DW$34, DW_AT_location[DW_OP_reg31]

$C$DW$35	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$35, DW_AT_name("OVM")
	.dwattr $C$DW$35, DW_AT_location[DW_OP_regx 0x20]

$C$DW$36	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$36, DW_AT_name("PAGE0")
	.dwattr $C$DW$36, DW_AT_location[DW_OP_regx 0x21]

$C$DW$37	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$37, DW_AT_name("AMODE")
	.dwattr $C$DW$37, DW_AT_location[DW_OP_regx 0x22]

$C$DW$38	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$38, DW_AT_name("EALLOW")
	.dwattr $C$DW$38, DW_AT_location[DW_OP_regx 0x4e]

$C$DW$39	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$39, DW_AT_name("INTM")
	.dwattr $C$DW$39, DW_AT_location[DW_OP_regx 0x23]

$C$DW$40	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$40, DW_AT_name("IFR")
	.dwattr $C$DW$40, DW_AT_location[DW_OP_regx 0x24]

$C$DW$41	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$41, DW_AT_name("IER")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_regx 0x25]

$C$DW$42	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$42, DW_AT_name("V")
	.dwattr $C$DW$42, DW_AT_location[DW_OP_regx 0x26]

$C$DW$43	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$43, DW_AT_name("PSEUDOH")
	.dwattr $C$DW$43, DW_AT_location[DW_OP_regx 0x4c]

$C$DW$44	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$44, DW_AT_name("VOL")
	.dwattr $C$DW$44, DW_AT_location[DW_OP_regx 0x4d]

$C$DW$45	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$45, DW_AT_name("AR0")
	.dwattr $C$DW$45, DW_AT_location[DW_OP_reg4]

$C$DW$46	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$46, DW_AT_name("XAR0")
	.dwattr $C$DW$46, DW_AT_location[DW_OP_reg5]

$C$DW$47	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$47, DW_AT_name("AR1")
	.dwattr $C$DW$47, DW_AT_location[DW_OP_reg6]

$C$DW$48	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$48, DW_AT_name("XAR1")
	.dwattr $C$DW$48, DW_AT_location[DW_OP_reg7]

$C$DW$49	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$49, DW_AT_name("AR2")
	.dwattr $C$DW$49, DW_AT_location[DW_OP_reg8]

$C$DW$50	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$50, DW_AT_name("XAR2")
	.dwattr $C$DW$50, DW_AT_location[DW_OP_reg9]

$C$DW$51	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$51, DW_AT_name("AR3")
	.dwattr $C$DW$51, DW_AT_location[DW_OP_reg10]

$C$DW$52	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$52, DW_AT_name("XAR3")
	.dwattr $C$DW$52, DW_AT_location[DW_OP_reg11]

$C$DW$53	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$53, DW_AT_name("AR4")
	.dwattr $C$DW$53, DW_AT_location[DW_OP_reg12]

$C$DW$54	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$54, DW_AT_name("XAR4")
	.dwattr $C$DW$54, DW_AT_location[DW_OP_reg13]

$C$DW$55	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$55, DW_AT_name("AR5")
	.dwattr $C$DW$55, DW_AT_location[DW_OP_reg14]

$C$DW$56	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$56, DW_AT_name("XAR5")
	.dwattr $C$DW$56, DW_AT_location[DW_OP_reg15]

$C$DW$57	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$57, DW_AT_name("AR6")
	.dwattr $C$DW$57, DW_AT_location[DW_OP_reg16]

$C$DW$58	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$58, DW_AT_name("XAR6")
	.dwattr $C$DW$58, DW_AT_location[DW_OP_reg17]

$C$DW$59	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$59, DW_AT_name("AR7")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_reg18]

$C$DW$60	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$60, DW_AT_name("XAR7")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_reg19]

$C$DW$61	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$61, DW_AT_name("R0H")
	.dwattr $C$DW$61, DW_AT_location[DW_OP_regx 0x2b]

$C$DW$62	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$62, DW_AT_name("R1H")
	.dwattr $C$DW$62, DW_AT_location[DW_OP_regx 0x2f]

$C$DW$63	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$63, DW_AT_name("R2H")
	.dwattr $C$DW$63, DW_AT_location[DW_OP_regx 0x33]

$C$DW$64	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$64, DW_AT_name("R3H")
	.dwattr $C$DW$64, DW_AT_location[DW_OP_regx 0x37]

$C$DW$65	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$65, DW_AT_name("R4H")
	.dwattr $C$DW$65, DW_AT_location[DW_OP_regx 0x3b]

$C$DW$66	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$66, DW_AT_name("R5H")
	.dwattr $C$DW$66, DW_AT_location[DW_OP_regx 0x3f]

$C$DW$67	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$67, DW_AT_name("R6H")
	.dwattr $C$DW$67, DW_AT_location[DW_OP_regx 0x43]

$C$DW$68	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$68, DW_AT_name("R7H")
	.dwattr $C$DW$68, DW_AT_location[DW_OP_regx 0x47]

$C$DW$69	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$69, DW_AT_name("RB")
	.dwattr $C$DW$69, DW_AT_location[DW_OP_regx 0x4a]

$C$DW$70	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$70, DW_AT_name("STF")
	.dwattr $C$DW$70, DW_AT_location[DW_OP_regx 0x28]

$C$DW$71	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$71, DW_AT_name("FPUHAZ")
	.dwattr $C$DW$71, DW_AT_location[DW_OP_reg27]

$C$DW$72	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$72, DW_AT_name("STF_HWDIV")
	.dwattr $C$DW$72, DW_AT_location[DW_OP_regx 0x4f]

$C$DW$73	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$73, DW_AT_name("VCRC")
	.dwattr $C$DW$73, DW_AT_location[DW_OP_regx 0x50]

$C$DW$74	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$74, DW_AT_name("VSTATUS")
	.dwattr $C$DW$74, DW_AT_location[DW_OP_regx 0x51]

	.dwendtag $C$DW$CU

