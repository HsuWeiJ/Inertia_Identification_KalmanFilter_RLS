;***************************************************************
;* TMS320C2000 G3 C/C++ Codegen                               PC v20.2.5.LTS *
;* Date/Time created: Thu Feb  2 17:04:15 2023                 *
;***************************************************************
	.compiler_opts --abi=coffabi --cla_support=cla0 --float_support=fpu32 --hll_source=on --mem_model:code=flat --mem_model:data=large --object_format=coff --quiet --silicon_errata_fpu1_workaround=off --silicon_version=28 --symdebug:dwarf --symdebug:dwarf_version=3 --tmu_support=tmu0 --vcu_support=vcu2 
	.asg	XAR2, FP

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../vector/qsort_SP_RV.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TMS320C2000 G3 C/C++ Codegen PC v20.2.5.LTS Copyright (c) 1996-2018 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\Users\jason\workspace_v10_4\MonoMtrServo_379D\F2837x_RAM")
;	C:\ti\ccs1040\ccs\tools\compiler\ti-cgt-c2000_20.2.5.LTS\bin\opt2000.exe C:\\Users\\jason\\AppData\\Local\\Temp\\{CC6A8177-5FA2-4F25-A939-C7794C07C1B1} C:\\Users\\jason\\AppData\\Local\\Temp\\{CE7B3FD7-12C7-4205-910B-7DA437E22376} 
;	C:\ti\ccs1040\ccs\tools\compiler\ti-cgt-c2000_20.2.5.LTS\bin\ac2000.exe -@C:\\Users\\jason\\AppData\\Local\\Temp\\{C0A199B3-D985-4738-98B1-28E3A4BA7087} 
	.sect	".text"
	.clink
	.global	_qsort_SP_RV

$C$DW$1	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$1, DW_AT_name("qsort_SP_RV")
	.dwattr $C$DW$1, DW_AT_low_pc(_qsort_SP_RV)
	.dwattr $C$DW$1, DW_AT_high_pc(0x00)
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("_qsort_SP_RV")
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_TI_begin_file("../vector/qsort_SP_RV.c")
	.dwattr $C$DW$1, DW_AT_TI_begin_line(0x29)
	.dwattr $C$DW$1, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$1, DW_AT_TI_max_frame_size(-10)
	.dwpsn	file "../vector/qsort_SP_RV.c",line 42,column 1,is_stmt,address _qsort_SP_RV,isa 0

	.dwfde $C$DW$CIE, _qsort_SP_RV
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_name("base")
	.dwattr $C$DW$2, DW_AT_TI_symbol_name("_base")
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$2, DW_AT_location[DW_OP_reg12]

$C$DW$3	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$3, DW_AT_name("nmemb")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("_nmemb")
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$3, DW_AT_location[DW_OP_reg0]


;***************************************************************
;* FNAME: _qsort_SP_RV                  FR SIZE:   8           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter,  0 Auto,  6 SOE     *
;***************************************************************

_qsort_SP_RV:
;* AR6   assigned to $O$C1
;* AR5   assigned to $O$C2
;* AR6   assigned to $O$C3
;* AR3   assigned to _nmemb
$C$DW$4	.dwtag  DW_TAG_variable
	.dwattr $C$DW$4, DW_AT_name("nmemb")
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("_nmemb")
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$4, DW_AT_location[DW_OP_reg10]

;* AR2   assigned to _basep
$C$DW$5	.dwtag  DW_TAG_variable
	.dwattr $C$DW$5, DW_AT_name("basep")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("_basep")
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$5, DW_AT_location[DW_OP_reg8]

;* AR1   assigned to _i
$C$DW$6	.dwtag  DW_TAG_variable
	.dwattr $C$DW$6, DW_AT_name("i")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("_i")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$6, DW_AT_location[DW_OP_reg6]

;* AR0   assigned to _j
$C$DW$7	.dwtag  DW_TAG_variable
	.dwattr $C$DW$7, DW_AT_name("j")
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("_j")
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$7, DW_AT_location[DW_OP_reg4]

;* PL    assigned to _pivot
$C$DW$8	.dwtag  DW_TAG_variable
	.dwattr $C$DW$8, DW_AT_name("pivot")
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("_pivot")
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$8, DW_AT_location[DW_OP_reg2]

;* AR4   assigned to _pivp
$C$DW$9	.dwtag  DW_TAG_variable
	.dwattr $C$DW$9, DW_AT_name("pivp")
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("_pivp")
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$9, DW_AT_location[DW_OP_reg12]

;* R0    assigned to _temp
$C$DW$10	.dwtag  DW_TAG_variable
	.dwattr $C$DW$10, DW_AT_name("temp")
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("_temp")
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$10, DW_AT_location[DW_OP_regx 0x2b]

	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
        MOVL      *SP++,XAR1            ; [CPU_ALU] 
	.dwcfi	save_reg_to_mem, 7, 2
	.dwcfi	cfa_offset, -4
        MOVL      *SP++,XAR2            ; [CPU_ALU] 
	.dwcfi	save_reg_to_mem, 9, 4
	.dwcfi	cfa_offset, -6
        MOVL      *SP++,XAR3            ; [CPU_ALU] 
	.dwcfi	save_reg_to_mem, 11, 6
	.dwcfi	cfa_offset, -8
        ADDB      SP,#2                 ; [CPU_ARAU] 
	.dwcfi	cfa_offset, -10
        MOVZ      AR3,AL                ; [CPU_ALU] |42| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 45,column 22,is_stmt,isa 0
        MOVZ      AR6,AR3               ; [CPU_ALU] |45| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 42,column 1,is_stmt,isa 0
        MOVL      XAR2,XAR4             ; [CPU_ALU] |42| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 44,column 22,is_stmt,isa 0
        MOVB      XAR1,#0               ; [CPU_ALU] |44| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 45,column 22,is_stmt,isa 0
        SUBB      XAR6,#1               ; [CPU_ARAU] |45| 
        MOV       ACC,AR6 << #1         ; [CPU_ALU] |45| 
        MOVZ      AR0,AL                ; [CPU_ALU] |45| 
        MOV       AL,AR3                ; [CPU_ALU] |45| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 46,column 20,is_stmt,isa 0
        AND       AL,AL,#0xfffe         ; [CPU_ALU] |46| 
        MOV       PL,AL                 ; [CPU_ALU] |46| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 42,column 1,is_stmt,isa 0
        MOVL      ACC,XAR4              ; [CPU_ALU] |42| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 47,column 20,is_stmt,isa 0
        ADDU      ACC,PL                ; [CPU_ALU] |47| 
        MOVL      XAR4,ACC              ; [CPU_ALU] |47| 
        MOV       AL,AR3                ; [CPU_ALU] |47| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 49,column 5,is_stmt,isa 0
        CMPB      AL,#1                 ; [CPU_ALU] |49| 
        B         $C$L12,LOS            ; [CPU_ALU] |49| 
        ; branchcc occurs ; [] |49| 
        MOV       AL,AR0                ; [CPU_ALU] 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 51,column 12,is_stmt,isa 0
        B         $C$L11,EQ             ; [CPU_ALU] |51| 
        ; branchcc occurs ; [] |51| 
$C$L1:    
	.dwpsn	file "../vector/qsort_SP_RV.c",line 53,column 15,is_stmt,isa 0
        MOV32     R1H,*+XAR2[AR1]       ; [CPU_FPU] |53| 
        MOV32     R0H,*+XAR4[0]         ; [CPU_FPU] |53| 
        CMPF32    R1H,R0H               ; [CPU_FPU] |53| 
        MOVST0    ZF, NF                ; [CPU_FPU] |53| 
        B         $C$L3,GEQ             ; [CPU_ALU] |53| 
        ; branchcc occurs ; [] |53| 
$C$L2:    
        ADDB      XAR1,#2               ; [CPU_ALU] |53| 
        MOV32     R0H,*+XAR4[0]         ; [CPU_FPU] |53| 
        MOV32     R1H,*+XAR2[AR1]       ; [CPU_FPU] |53| 
        CMPF32    R1H,R0H               ; [CPU_FPU] |53| 
        MOVST0    ZF, NF                ; [CPU_FPU] |53| 
        B         $C$L2,LT              ; [CPU_ALU] |53| 
        ; branchcc occurs ; [] |53| 
$C$L3:    
	.dwpsn	file "../vector/qsort_SP_RV.c",line 54,column 15,is_stmt,isa 0
        MOV32     R1H,*+XAR2[AR0]       ; [CPU_FPU] |54| 
        MOV32     R0H,*+XAR4[0]         ; [CPU_FPU] |54| 
        CMPF32    R1H,R0H               ; [CPU_FPU] |54| 
        MOVST0    ZF, NF                ; [CPU_FPU] |54| 
        B         $C$L5,LEQ             ; [CPU_ALU] |54| 
        ; branchcc occurs ; [] |54| 
$C$L4:    
        SUBB      XAR0,#2               ; [CPU_ARAU] |54| 
        MOV32     R0H,*+XAR4[0]         ; [CPU_FPU] |54| 
        MOV32     R1H,*+XAR2[AR0]       ; [CPU_FPU] |54| 
        CMPF32    R1H,R0H               ; [CPU_FPU] |54| 
        MOVST0    ZF, NF                ; [CPU_FPU] |54| 
        B         $C$L4,GT              ; [CPU_ALU] |54| 
        ; branchcc occurs ; [] |54| 
$C$L5:    
        MOV       AL,AR0                ; [CPU_ALU] 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 56,column 9,is_stmt,isa 0
        CMP       AL,AR1                ; [CPU_ALU] |56| 
        B         $C$L6,HI              ; [CPU_ALU] |56| 
        ; branchcc occurs ; [] |56| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 63,column 14,is_stmt,isa 0
        MOVZ      AR6,AR1               ; [CPU_ALU] |63| 
        MOVU      ACC,AR0               ; [CPU_ALU] |63| 
        CMPL      ACC,XAR6              ; [CPU_ALU] |63| 
        B         $C$L9,NEQ             ; [CPU_ALU] |63| 
        ; branchcc occurs ; [] |63| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 63,column 37,is_stmt,isa 0
        SUBB      XAR0,#2               ; [CPU_ARAU] |63| 
        MOV       AL,AR0                ; [CPU_ALU] |63| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 63,column 30,is_stmt,isa 0
        ADDB      XAR1,#2               ; [CPU_ALU] |63| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 63,column 37,is_stmt,isa 0
        B         $C$L10,NEQ            ; [CPU_ALU] |63| 
        ; branchcc occurs ; [] |63| 
        B         $C$L11,UNC            ; [CPU_ALU] |63| 
        ; branch occurs ; [] |63| 
$C$L6:    
	.dwpsn	file "../vector/qsort_SP_RV.c",line 77,column 5,is_stmt,isa 0
        MOVL      ACC,XAR2              ; [CPU_ALU] |77| 
        ADDU      ACC,AR1               ; [CPU_ALU] |77| 
        MOVL      XAR5,ACC              ; [CPU_ALU] |77| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 78,column 5,is_stmt,isa 0
        MOVL      ACC,XAR2              ; [CPU_ALU] |78| 
        ADDU      ACC,AR0               ; [CPU_ALU] |78| 
        MOVL      XAR6,ACC              ; [CPU_ALU] |78| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 59,column 13,is_stmt,isa 0
        MOVZ      AR7,PL                ; [CPU_ALU] |59| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 77,column 5,is_stmt,isa 0
        MOV32     R0H,*+XAR5[0]         ; [CPU_FPU] |77| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 59,column 13,is_stmt,isa 0
        MOVU      ACC,AR1               ; [CPU_ALU] |59| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 78,column 5,is_stmt,isa 0
        MOVL      XT,*+XAR6[0]          ; [CPU_ALU] |78| 
        MOVL      *+XAR5[0],XT          ; [CPU_ALU] |78| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 59,column 13,is_stmt,isa 0
        CMPL      ACC,XAR7              ; [CPU_ALU] |59| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 79,column 5,is_stmt,isa 0
        MOV32     *+XAR6[0],R0H         ; [CPU_FPU] |79| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 59,column 13,is_stmt,isa 0
        B         $C$L7,EQ              ; [CPU_ALU] |59| 
        ; branchcc occurs ; [] |59| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 60,column 18,is_stmt,isa 0
        MOVZ      AR6,PL                ; [CPU_ALU] |60| 
        MOVU      ACC,AR0               ; [CPU_ALU] |60| 
        CMPL      ACC,XAR6              ; [CPU_ALU] |60| 
        B         $C$L8,NEQ             ; [CPU_ALU] |60| 
        ; branchcc occurs ; [] |60| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 60,column 37,is_stmt,isa 0
        MOV       PL,AR1                ; [CPU_ALU] |60| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 60,column 48,is_stmt,isa 0
        MOVL      XAR4,XAR5             ; [CPU_ALU] |60| 
        B         $C$L8,UNC             ; [CPU_ALU] |60| 
        ; branch occurs ; [] |60| 
$C$L7:    
	.dwpsn	file "../vector/qsort_SP_RV.c",line 59,column 33,is_stmt,isa 0
        MOV       PL,AR0                ; [CPU_ALU] |59| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 59,column 44,is_stmt,isa 0
        MOVL      ACC,XAR2              ; [CPU_ALU] |59| 
        ADDU      ACC,PL                ; [CPU_ALU] |59| 
        MOVL      XAR4,ACC              ; [CPU_ALU] |59| 
$C$L8:    
	.dwpsn	file "../vector/qsort_SP_RV.c",line 61,column 13,is_stmt,isa 0
        ADDB      XAR1,#2               ; [CPU_ALU] |61| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 61,column 20,is_stmt,isa 0
        SUBB      XAR0,#2               ; [CPU_ARAU] |61| 
$C$L9:    
        MOV       AL,AR0                ; [CPU_ALU] 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 51,column 12,is_stmt,isa 0
        CMP       AL,AR1                ; [CPU_ALU] |51| 
        B         $C$L1,HI              ; [CPU_ALU] |51| 
        ; branchcc occurs ; [] |51| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 66,column 5,is_stmt,isa 0
        CMPB      AL,#0                 ; [CPU_ALU] |66| 
        B         $C$L11,EQ             ; [CPU_ALU] |66| 
        ; branchcc occurs ; [] |66| 
$C$L10:    
	.dwpsn	file "../vector/qsort_SP_RV.c",line 66,column 15,is_stmt,isa 0
        LSR       AL,1                  ; [CPU_ALU] |66| 
        MOVL      XAR4,XAR2             ; [CPU_FPU] |66| 
        ADDB      AL,#1                 ; [CPU_ALU] |66| 
$C$DW$11	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$11, DW_AT_low_pc(0x00)
	.dwattr $C$DW$11, DW_AT_name("_qsort_SP_RV")
	.dwattr $C$DW$11, DW_AT_TI_call

        LCR       #_qsort_SP_RV         ; [CPU_ALU] |66| 
        ; call occurs [#_qsort_SP_RV] ; [] |66| 
$C$L11:    
	.dwpsn	file "../vector/qsort_SP_RV.c",line 67,column 5,is_stmt,isa 0
        MOV       AL,AR1                ; [CPU_ALU] |67| 
        LSR       AL,1                  ; [CPU_ALU] |67| 
        MOVZ      AR6,AL                ; [CPU_ALU] |67| 
        MOV       AL,AR3                ; [CPU_ALU] |67| 
        ADDB      AL,#-1                ; [CPU_ALU] |67| 
        CMP       AL,AR6                ; [CPU_ALU] |67| 
        B         $C$L12,LOS            ; [CPU_ALU] |67| 
        ; branchcc occurs ; [] |67| 
	.dwpsn	file "../vector/qsort_SP_RV.c",line 67,column 26,is_stmt,isa 0
        MOVL      ACC,XAR2              ; [CPU_ALU] |67| 
        ADDU      ACC,AR1               ; [CPU_ALU] |67| 
        MOVL      XAR4,ACC              ; [CPU_ALU] |67| 
        MOV       AL,AR3                ; [CPU_ALU] |67| 
        SUB       AL,AR6                ; [CPU_ALU] |67| 
$C$DW$12	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$12, DW_AT_low_pc(0x00)
	.dwattr $C$DW$12, DW_AT_name("_qsort_SP_RV")
	.dwattr $C$DW$12, DW_AT_TI_call

        LCR       #_qsort_SP_RV         ; [CPU_ALU] |67| 
        ; call occurs [#_qsort_SP_RV] ; [] |67| 
$C$L12:    
        SUBB      SP,#2                 ; [CPU_ARAU] 
	.dwcfi	cfa_offset, -8
        MOVL      XAR3,*--SP            ; [CPU_ALU] 
	.dwcfi	cfa_offset, -6
	.dwcfi	restore_reg, 11
        MOVL      XAR2,*--SP            ; [CPU_ALU] 
	.dwcfi	cfa_offset, -4
	.dwcfi	restore_reg, 9
        MOVL      XAR1,*--SP            ; [CPU_ALU] 
	.dwcfi	cfa_offset, -2
	.dwcfi	restore_reg, 7
$C$DW$13	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$13, DW_AT_low_pc(0x00)
	.dwattr $C$DW$13, DW_AT_TI_return

        LRETR     ; [CPU_ALU] 
        ; return occurs ; [] 
	.dwattr $C$DW$1, DW_AT_TI_end_file("../vector/qsort_SP_RV.c")
	.dwattr $C$DW$1, DW_AT_TI_end_line(0x45)
	.dwattr $C$DW$1, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$1


;***************************************************************
;* TYPE INFORMATION                                            *
;***************************************************************
$C$DW$T$2	.dwtag  DW_TAG_unspecified_type
	.dwattr $C$DW$T$2, DW_AT_name("void")

$C$DW$T$3	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$3, DW_AT_type(*$C$DW$T$2)
	.dwattr $C$DW$T$3, DW_AT_address_class(0x20)

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

$C$DW$T$20	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$20, DW_AT_name("__uint16_t")
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$20, DW_AT_language(DW_LANG_C)

$C$DW$T$21	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$21, DW_AT_name("uint16_t")
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$21, DW_AT_language(DW_LANG_C)

$C$DW$14	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$21)

$C$DW$T$22	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$14)

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

$C$DW$T$30	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$30, DW_AT_type(*$C$DW$T$5)
	.dwattr $C$DW$T$30, DW_AT_address_class(0x20)

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

$C$DW$15	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$15, DW_AT_name("AL")
	.dwattr $C$DW$15, DW_AT_location[DW_OP_reg0]

$C$DW$16	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$16, DW_AT_name("AH")
	.dwattr $C$DW$16, DW_AT_location[DW_OP_reg1]

$C$DW$17	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$17, DW_AT_name("PL")
	.dwattr $C$DW$17, DW_AT_location[DW_OP_reg2]

$C$DW$18	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$18, DW_AT_name("PH")
	.dwattr $C$DW$18, DW_AT_location[DW_OP_reg3]

$C$DW$19	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$19, DW_AT_name("SP")
	.dwattr $C$DW$19, DW_AT_location[DW_OP_reg20]

$C$DW$20	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$20, DW_AT_name("XT")
	.dwattr $C$DW$20, DW_AT_location[DW_OP_reg21]

$C$DW$21	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$21, DW_AT_name("T")
	.dwattr $C$DW$21, DW_AT_location[DW_OP_reg22]

$C$DW$22	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$22, DW_AT_name("ST0")
	.dwattr $C$DW$22, DW_AT_location[DW_OP_reg23]

$C$DW$23	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$23, DW_AT_name("ST1")
	.dwattr $C$DW$23, DW_AT_location[DW_OP_reg24]

$C$DW$24	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$24, DW_AT_name("PC")
	.dwattr $C$DW$24, DW_AT_location[DW_OP_reg25]

$C$DW$25	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$25, DW_AT_name("RPC")
	.dwattr $C$DW$25, DW_AT_location[DW_OP_reg26]

$C$DW$26	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$26, DW_AT_name("FP")
	.dwattr $C$DW$26, DW_AT_location[DW_OP_reg28]

$C$DW$27	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$27, DW_AT_name("DP")
	.dwattr $C$DW$27, DW_AT_location[DW_OP_reg29]

$C$DW$28	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$28, DW_AT_name("SXM")
	.dwattr $C$DW$28, DW_AT_location[DW_OP_reg30]

$C$DW$29	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$29, DW_AT_name("PM")
	.dwattr $C$DW$29, DW_AT_location[DW_OP_reg31]

$C$DW$30	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$30, DW_AT_name("OVM")
	.dwattr $C$DW$30, DW_AT_location[DW_OP_regx 0x20]

$C$DW$31	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$31, DW_AT_name("PAGE0")
	.dwattr $C$DW$31, DW_AT_location[DW_OP_regx 0x21]

$C$DW$32	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$32, DW_AT_name("AMODE")
	.dwattr $C$DW$32, DW_AT_location[DW_OP_regx 0x22]

$C$DW$33	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$33, DW_AT_name("EALLOW")
	.dwattr $C$DW$33, DW_AT_location[DW_OP_regx 0x4e]

$C$DW$34	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$34, DW_AT_name("INTM")
	.dwattr $C$DW$34, DW_AT_location[DW_OP_regx 0x23]

$C$DW$35	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$35, DW_AT_name("IFR")
	.dwattr $C$DW$35, DW_AT_location[DW_OP_regx 0x24]

$C$DW$36	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$36, DW_AT_name("IER")
	.dwattr $C$DW$36, DW_AT_location[DW_OP_regx 0x25]

$C$DW$37	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$37, DW_AT_name("V")
	.dwattr $C$DW$37, DW_AT_location[DW_OP_regx 0x26]

$C$DW$38	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$38, DW_AT_name("PSEUDOH")
	.dwattr $C$DW$38, DW_AT_location[DW_OP_regx 0x4c]

$C$DW$39	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$39, DW_AT_name("VOL")
	.dwattr $C$DW$39, DW_AT_location[DW_OP_regx 0x4d]

$C$DW$40	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$40, DW_AT_name("AR0")
	.dwattr $C$DW$40, DW_AT_location[DW_OP_reg4]

$C$DW$41	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$41, DW_AT_name("XAR0")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_reg5]

$C$DW$42	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$42, DW_AT_name("AR1")
	.dwattr $C$DW$42, DW_AT_location[DW_OP_reg6]

$C$DW$43	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$43, DW_AT_name("XAR1")
	.dwattr $C$DW$43, DW_AT_location[DW_OP_reg7]

$C$DW$44	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$44, DW_AT_name("AR2")
	.dwattr $C$DW$44, DW_AT_location[DW_OP_reg8]

$C$DW$45	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$45, DW_AT_name("XAR2")
	.dwattr $C$DW$45, DW_AT_location[DW_OP_reg9]

$C$DW$46	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$46, DW_AT_name("AR3")
	.dwattr $C$DW$46, DW_AT_location[DW_OP_reg10]

$C$DW$47	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$47, DW_AT_name("XAR3")
	.dwattr $C$DW$47, DW_AT_location[DW_OP_reg11]

$C$DW$48	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$48, DW_AT_name("AR4")
	.dwattr $C$DW$48, DW_AT_location[DW_OP_reg12]

$C$DW$49	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$49, DW_AT_name("XAR4")
	.dwattr $C$DW$49, DW_AT_location[DW_OP_reg13]

$C$DW$50	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$50, DW_AT_name("AR5")
	.dwattr $C$DW$50, DW_AT_location[DW_OP_reg14]

$C$DW$51	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$51, DW_AT_name("XAR5")
	.dwattr $C$DW$51, DW_AT_location[DW_OP_reg15]

$C$DW$52	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$52, DW_AT_name("AR6")
	.dwattr $C$DW$52, DW_AT_location[DW_OP_reg16]

$C$DW$53	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$53, DW_AT_name("XAR6")
	.dwattr $C$DW$53, DW_AT_location[DW_OP_reg17]

$C$DW$54	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$54, DW_AT_name("AR7")
	.dwattr $C$DW$54, DW_AT_location[DW_OP_reg18]

$C$DW$55	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$55, DW_AT_name("XAR7")
	.dwattr $C$DW$55, DW_AT_location[DW_OP_reg19]

$C$DW$56	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$56, DW_AT_name("R0H")
	.dwattr $C$DW$56, DW_AT_location[DW_OP_regx 0x2b]

$C$DW$57	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$57, DW_AT_name("R1H")
	.dwattr $C$DW$57, DW_AT_location[DW_OP_regx 0x2f]

$C$DW$58	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$58, DW_AT_name("R2H")
	.dwattr $C$DW$58, DW_AT_location[DW_OP_regx 0x33]

$C$DW$59	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$59, DW_AT_name("R3H")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_regx 0x37]

$C$DW$60	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$60, DW_AT_name("R4H")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_regx 0x3b]

$C$DW$61	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$61, DW_AT_name("R5H")
	.dwattr $C$DW$61, DW_AT_location[DW_OP_regx 0x3f]

$C$DW$62	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$62, DW_AT_name("R6H")
	.dwattr $C$DW$62, DW_AT_location[DW_OP_regx 0x43]

$C$DW$63	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$63, DW_AT_name("R7H")
	.dwattr $C$DW$63, DW_AT_location[DW_OP_regx 0x47]

$C$DW$64	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$64, DW_AT_name("RB")
	.dwattr $C$DW$64, DW_AT_location[DW_OP_regx 0x4a]

$C$DW$65	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$65, DW_AT_name("STF")
	.dwattr $C$DW$65, DW_AT_location[DW_OP_regx 0x28]

$C$DW$66	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$66, DW_AT_name("FPUHAZ")
	.dwattr $C$DW$66, DW_AT_location[DW_OP_reg27]

$C$DW$67	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$67, DW_AT_name("STF_HWDIV")
	.dwattr $C$DW$67, DW_AT_location[DW_OP_regx 0x4f]

$C$DW$68	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$68, DW_AT_name("VCRC")
	.dwattr $C$DW$68, DW_AT_location[DW_OP_regx 0x50]

$C$DW$69	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$69, DW_AT_name("VSTATUS")
	.dwattr $C$DW$69, DW_AT_location[DW_OP_regx 0x51]

	.dwendtag $C$DW$CU

