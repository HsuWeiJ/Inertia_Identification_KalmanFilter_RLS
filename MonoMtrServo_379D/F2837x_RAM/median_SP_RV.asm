;***************************************************************
;* TMS320C2000 G3 C/C++ Codegen                               PC v20.2.5.LTS *
;* Date/Time created: Thu Feb  2 17:04:22 2023                 *
;***************************************************************
	.compiler_opts --abi=coffabi --cla_support=cla0 --float_support=fpu32 --hll_source=on --mem_model:code=flat --mem_model:data=large --object_format=coff --quiet --silicon_errata_fpu1_workaround=off --silicon_version=28 --symdebug:dwarf --symdebug:dwarf_version=3 --tmu_support=tmu0 --vcu_support=vcu2 
	.asg	XAR2, FP

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../vector/median_SP_RV.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TMS320C2000 G3 C/C++ Codegen PC v20.2.5.LTS Copyright (c) 1996-2018 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\Users\jason\workspace_v10_4\MonoMtrServo_379D\F2837x_RAM")
;	C:\ti\ccs1040\ccs\tools\compiler\ti-cgt-c2000_20.2.5.LTS\bin\opt2000.exe C:\\Users\\jason\\AppData\\Local\\Temp\\{10001C11-3F98-4683-950F-AFBAF27A369A} C:\\Users\\jason\\AppData\\Local\\Temp\\{A12CD030-A27E-42CF-9563-6005C504D452} 
;	C:\ti\ccs1040\ccs\tools\compiler\ti-cgt-c2000_20.2.5.LTS\bin\ac2000.exe -@C:\\Users\\jason\\AppData\\Local\\Temp\\{11BCEE8A-EC63-4338-BE11-8A0D51B8AC59} 
	.sect	".text"
	.clink
	.global	__median_find_average_SP_RV

$C$DW$1	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$1, DW_AT_name("_median_find_average_SP_RV")
	.dwattr $C$DW$1, DW_AT_low_pc(__median_find_average_SP_RV)
	.dwattr $C$DW$1, DW_AT_high_pc(0x00)
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("__median_find_average_SP_RV")
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$1, DW_AT_TI_begin_file("../vector/median_SP_RV.c")
	.dwattr $C$DW$1, DW_AT_TI_begin_line(0xbc)
	.dwattr $C$DW$1, DW_AT_TI_begin_column(0x07)
	.dwattr $C$DW$1, DW_AT_TI_max_frame_size(-6)
	.dwpsn	file "../vector/median_SP_RV.c",line 189,column 1,is_stmt,address __median_find_average_SP_RV,isa 0

	.dwfde $C$DW$CIE, __median_find_average_SP_RV
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_name("x")
	.dwattr $C$DW$2, DW_AT_TI_symbol_name("_x")
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$2, DW_AT_location[DW_OP_reg12]

$C$DW$3	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$3, DW_AT_name("median_low")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("_median_low")
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$3, DW_AT_location[DW_OP_regx 0x2b]

$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_name("N")
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("_N")
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$4, DW_AT_location[DW_OP_reg0]


;***************************************************************
;* FNAME: __median_find_average_SP_RV   FR SIZE:   4           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter,  0 Auto,  2 SOE     *
;***************************************************************

__median_find_average_SP_RV:
;* R3    assigned to $O$C1
;* R3    assigned to $O$C2
;* AR4   assigned to _x
$C$DW$5	.dwtag  DW_TAG_variable
	.dwattr $C$DW$5, DW_AT_name("x")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("_x")
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$5, DW_AT_location[DW_OP_reg12]

;* R0    assigned to _median_low
$C$DW$6	.dwtag  DW_TAG_variable
	.dwattr $C$DW$6, DW_AT_name("median_low")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("_median_low")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$28)
	.dwattr $C$DW$6, DW_AT_location[DW_OP_regx 0x2b]

;* AL    assigned to _N
$C$DW$7	.dwtag  DW_TAG_variable
	.dwattr $C$DW$7, DW_AT_name("N")
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("_N")
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$7, DW_AT_location[DW_OP_reg0]

;* R2    assigned to _median_delta
$C$DW$8	.dwtag  DW_TAG_variable
	.dwattr $C$DW$8, DW_AT_name("median_delta")
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("_median_delta")
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$8, DW_AT_location[DW_OP_regx 0x33]

;* R1    assigned to _median_high
$C$DW$9	.dwtag  DW_TAG_variable
	.dwattr $C$DW$9, DW_AT_name("median_high")
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("_median_high")
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$9, DW_AT_location[DW_OP_regx 0x2f]

;* AR5   assigned to _higher_count
$C$DW$10	.dwtag  DW_TAG_variable
	.dwattr $C$DW$10, DW_AT_name("higher_count")
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("_higher_count")
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$10, DW_AT_location[DW_OP_reg14]

;* AR6   assigned to _i
$C$DW$11	.dwtag  DW_TAG_variable
	.dwattr $C$DW$11, DW_AT_name("i")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("_i")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$11, DW_AT_location[DW_OP_reg16]

	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
        MOV32     *SP++,R4H             ; [CPU_FPU] 
	.dwcfi	save_reg_to_mem, 59, 2
	.dwcfi	cfa_offset, -4
        ADDB      SP,#2                 ; [CPU_ARAU] 
	.dwcfi	cfa_offset, -6
	.dwpsn	file "../vector/median_SP_RV.c",line 199,column 5,is_stmt,isa 0
        MOVIZ     R1H,#32639            ; [CPU_FPU] |199| 
	.dwpsn	file "../vector/median_SP_RV.c",line 206,column 14,is_stmt,isa 0
        AND       AH,AL,#0xfffe         ; [CPU_ALU] |206| 
	.dwpsn	file "../vector/median_SP_RV.c",line 200,column 5,is_stmt,isa 0
        MOVB      XAR5,#0               ; [CPU_ALU] |200| 
	.dwpsn	file "../vector/median_SP_RV.c",line 206,column 9,is_stmt,isa 0
        MOVB      XAR6,#0               ; [CPU_ALU] |206| 
	.dwpsn	file "../vector/median_SP_RV.c",line 199,column 5,is_stmt,isa 0
        MOVXI     R1H,#65535            ; [CPU_FPU] |199| 
        SUBF32    R2H,R1H,R0H           ; [CPU_FPU] |199| 
	.dwpsn	file "../vector/median_SP_RV.c",line 206,column 14,is_stmt,isa 0
        B         $C$L4,EQ              ; [CPU_ALU] |206| 
        ; branchcc occurs ; [] |206| 
$C$L1:    
	.dwpsn	file "../vector/median_SP_RV.c",line 209,column 9,is_stmt,isa 0
        MOV32     R3H,*+XAR4[0]         ; [CPU_FPU] |209| 
        CMPF32    R3H,R0H               ; [CPU_FPU] |209| 
        MOVST0    ZF, NF                ; [CPU_FPU] |209| 
        B         $C$L2,LEQ             ; [CPU_ALU] |209| 
        ; branchcc occurs ; [] |209| 
	.dwpsn	file "../vector/median_SP_RV.c",line 213,column 13,is_stmt,isa 0
        SUBF32    R4H,R3H,R0H           ; [CPU_FPU] |213| 
	.dwpsn	file "../vector/median_SP_RV.c",line 211,column 13,is_stmt,isa 0
        ADDB      XAR5,#1               ; [CPU_ALU] |211| 
	.dwpsn	file "../vector/median_SP_RV.c",line 213,column 13,is_stmt,isa 0
        CMPF32    R4H,R2H               ; [CPU_FPU] |213| 
        MOVST0    ZF, NF                ; [CPU_FPU] |213| 
        B         $C$L2,GEQ             ; [CPU_ALU] |213| 
        ; branchcc occurs ; [] |213| 
	.dwpsn	file "../vector/median_SP_RV.c",line 216,column 17,is_stmt,isa 0
        MOV32     R1H,R3H               ; [CPU_FPU] |216| 
	.dwpsn	file "../vector/median_SP_RV.c",line 218,column 17,is_stmt,isa 0
        SUBF32    R2H,R1H,R0H           ; [CPU_FPU] |218| 
$C$L2:    
	.dwpsn	file "../vector/median_SP_RV.c",line 225,column 9,is_stmt,isa 0
        ADDB      XAR4,#2               ; [CPU_ALU] |225| 
        MOV32     R3H,*+XAR4[0]         ; [CPU_FPU] |225| 
        CMPF32    R3H,R0H               ; [CPU_FPU] |225| 
        MOVST0    ZF, NF                ; [CPU_FPU] |225| 
        B         $C$L3,LEQ             ; [CPU_ALU] |225| 
        ; branchcc occurs ; [] |225| 
	.dwpsn	file "../vector/median_SP_RV.c",line 229,column 13,is_stmt,isa 0
        SUBF32    R4H,R3H,R0H           ; [CPU_FPU] |229| 
	.dwpsn	file "../vector/median_SP_RV.c",line 227,column 13,is_stmt,isa 0
        ADDB      XAR5,#1               ; [CPU_ALU] |227| 
	.dwpsn	file "../vector/median_SP_RV.c",line 229,column 13,is_stmt,isa 0
        CMPF32    R4H,R2H               ; [CPU_FPU] |229| 
        MOVST0    ZF, NF                ; [CPU_FPU] |229| 
        B         $C$L3,GEQ             ; [CPU_ALU] |229| 
        ; branchcc occurs ; [] |229| 
	.dwpsn	file "../vector/median_SP_RV.c",line 232,column 17,is_stmt,isa 0
        MOV32     R1H,R3H               ; [CPU_FPU] |232| 
	.dwpsn	file "../vector/median_SP_RV.c",line 234,column 17,is_stmt,isa 0
        SUBF32    R2H,R1H,R0H           ; [CPU_FPU] |234| 
$C$L3:    
	.dwpsn	file "../vector/median_SP_RV.c",line 206,column 14,is_stmt,isa 0
        MOV       AH,AL                 ; [CPU_ALU] |206| 
        ADDB      XAR6,#1               ; [CPU_ALU] |206| 
        LSR       AH,1                  ; [CPU_ALU] |206| 
	.dwpsn	file "../vector/median_SP_RV.c",line 238,column 9,is_stmt,isa 0
        ADDB      XAR4,#2               ; [CPU_ALU] |238| 
	.dwpsn	file "../vector/median_SP_RV.c",line 206,column 14,is_stmt,isa 0
        CMP       AH,AR6                ; [CPU_ALU] |206| 
        B         $C$L1,HI              ; [CPU_ALU] |206| 
        ; branchcc occurs ; [] |206| 
$C$L4:    
	.dwpsn	file "../vector/median_SP_RV.c",line 245,column 9,is_stmt,isa 0
        LSR       AL,1                  ; [CPU_ALU] |245| 
        CMP       AL,AR5                ; [CPU_ALU] |245| 
        B         $C$L5,HI              ; [CPU_ALU] |245| 
        ; branchcc occurs ; [] |245| 
        ADDF32    R0H,R0H,R1H           ; [CPU_FPU] |245| 
        NOP       ; [CPU_ALU] 
        MPYF32    R0H,R0H,#16128        ; [CPU_FPU] |245| 
        NOP       ; [CPU_ALU] 
$C$L5:    
        SUBB      SP,#2                 ; [CPU_ARAU] 
	.dwcfi	cfa_offset, -4
        MOV32     R4H,*--SP             ; [CPU_FPU] 
	.dwcfi	cfa_offset, -2
	.dwcfi	restore_reg, 59
$C$DW$12	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$12, DW_AT_low_pc(0x00)
	.dwattr $C$DW$12, DW_AT_TI_return

        LRETR     ; [CPU_ALU] 
        ; return occurs ; [] 
	.dwattr $C$DW$1, DW_AT_TI_end_file("../vector/median_SP_RV.c")
	.dwattr $C$DW$1, DW_AT_TI_end_line(0xfd)
	.dwattr $C$DW$1, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$1

	.sect	".text"
	.clink
	.global	_median_SP_RV

$C$DW$13	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$13, DW_AT_name("median_SP_RV")
	.dwattr $C$DW$13, DW_AT_low_pc(_median_SP_RV)
	.dwattr $C$DW$13, DW_AT_high_pc(0x00)
	.dwattr $C$DW$13, DW_AT_TI_symbol_name("_median_SP_RV")
	.dwattr $C$DW$13, DW_AT_external
	.dwattr $C$DW$13, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$13, DW_AT_TI_begin_file("../vector/median_SP_RV.c")
	.dwattr $C$DW$13, DW_AT_TI_begin_line(0x36)
	.dwattr $C$DW$13, DW_AT_TI_begin_column(0x07)
	.dwattr $C$DW$13, DW_AT_TI_max_frame_size(-6)
	.dwpsn	file "../vector/median_SP_RV.c",line 55,column 1,is_stmt,address _median_SP_RV,isa 0

	.dwfde $C$DW$CIE, _median_SP_RV
$C$DW$14	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$14, DW_AT_name("x")
	.dwattr $C$DW$14, DW_AT_TI_symbol_name("_x")
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$14, DW_AT_location[DW_OP_reg12]

$C$DW$15	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$15, DW_AT_name("N")
	.dwattr $C$DW$15, DW_AT_TI_symbol_name("_N")
	.dwattr $C$DW$15, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$15, DW_AT_location[DW_OP_reg0]


;***************************************************************
;* FNAME: _median_SP_RV                 FR SIZE:   4           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter,  0 Auto,  2 SOE     *
;***************************************************************

_median_SP_RV:
;* AR6   assigned to $O$C2
;* AR5   assigned to $O$C3
;* R1    assigned to $O$C4
;* R0    assigned to $O$C5
;* AR7   assigned to $O$C6
;* AR6   assigned to $O$C7
;* AR7   assigned to $O$C8
;* AR6   assigned to $O$C9
;* AR7   assigned to $O$C11
;* AR6   assigned to $O$C12
;* AR6   assigned to $O$C13
;* AR5   assigned to $O$C14
;* R1    assigned to $O$C15
;* R0    assigned to $O$C16
;* AR6   assigned to $O$C17
;* AR5   assigned to $O$C18
;* R1    assigned to $O$C19
;* R0    assigned to $O$C20
;* AR6   assigned to $O$C21
;* AR5   assigned to $O$C22
;* R1    assigned to $O$C23
;* R0    assigned to $O$C24
;* R1    assigned to $O$T1
;* AR4   assigned to _x
$C$DW$16	.dwtag  DW_TAG_variable
	.dwattr $C$DW$16, DW_AT_name("x")
	.dwattr $C$DW$16, DW_AT_TI_symbol_name("_x")
	.dwattr $C$DW$16, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$16, DW_AT_location[DW_OP_reg12]

;* PL    assigned to _N
$C$DW$17	.dwtag  DW_TAG_variable
	.dwattr $C$DW$17, DW_AT_name("N")
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("_N")
	.dwattr $C$DW$17, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$17, DW_AT_location[DW_OP_reg2]

;* AR7   assigned to _p
$C$DW$18	.dwtag  DW_TAG_variable
	.dwattr $C$DW$18, DW_AT_name("p")
	.dwattr $C$DW$18, DW_AT_TI_symbol_name("_p")
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$18, DW_AT_location[DW_OP_reg18]

;* PH    assigned to _low
$C$DW$19	.dwtag  DW_TAG_variable
	.dwattr $C$DW$19, DW_AT_name("low")
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("_low")
	.dwattr $C$DW$19, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$19, DW_AT_location[DW_OP_reg3]

;* T     assigned to _high
$C$DW$20	.dwtag  DW_TAG_variable
	.dwattr $C$DW$20, DW_AT_name("high")
	.dwattr $C$DW$20, DW_AT_TI_symbol_name("_high")
	.dwattr $C$DW$20, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$20, DW_AT_location[DW_OP_reg22]

;* AR2   assigned to _median
$C$DW$21	.dwtag  DW_TAG_variable
	.dwattr $C$DW$21, DW_AT_name("median")
	.dwattr $C$DW$21, DW_AT_TI_symbol_name("_median")
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$21, DW_AT_location[DW_OP_reg8]

;* AR7   assigned to _middle
$C$DW$22	.dwtag  DW_TAG_variable
	.dwattr $C$DW$22, DW_AT_name("middle")
	.dwattr $C$DW$22, DW_AT_TI_symbol_name("_middle")
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$22, DW_AT_location[DW_OP_reg18]

;* AR0   assigned to _ll
$C$DW$23	.dwtag  DW_TAG_variable
	.dwattr $C$DW$23, DW_AT_name("ll")
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("_ll")
	.dwattr $C$DW$23, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$23, DW_AT_location[DW_OP_reg4]

;* AR5   assigned to _hh
$C$DW$24	.dwtag  DW_TAG_variable
	.dwattr $C$DW$24, DW_AT_name("hh")
	.dwattr $C$DW$24, DW_AT_TI_symbol_name("_hh")
	.dwattr $C$DW$24, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$24, DW_AT_location[DW_OP_reg14]

;* R0    assigned to _t
$C$DW$25	.dwtag  DW_TAG_variable
	.dwattr $C$DW$25, DW_AT_name("t")
	.dwattr $C$DW$25, DW_AT_TI_symbol_name("_t")
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$25, DW_AT_location[DW_OP_regx 0x2b]

;* R0    assigned to _t
$C$DW$26	.dwtag  DW_TAG_variable
	.dwattr $C$DW$26, DW_AT_name("t")
	.dwattr $C$DW$26, DW_AT_TI_symbol_name("_t")
	.dwattr $C$DW$26, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$26, DW_AT_location[DW_OP_regx 0x2b]

;* R0    assigned to _t
$C$DW$27	.dwtag  DW_TAG_variable
	.dwattr $C$DW$27, DW_AT_name("t")
	.dwattr $C$DW$27, DW_AT_TI_symbol_name("_t")
	.dwattr $C$DW$27, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$27, DW_AT_location[DW_OP_regx 0x2b]

;* R0    assigned to _t
$C$DW$28	.dwtag  DW_TAG_variable
	.dwattr $C$DW$28, DW_AT_name("t")
	.dwattr $C$DW$28, DW_AT_TI_symbol_name("_t")
	.dwattr $C$DW$28, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$28, DW_AT_location[DW_OP_regx 0x2b]

;* R0    assigned to _t
$C$DW$29	.dwtag  DW_TAG_variable
	.dwattr $C$DW$29, DW_AT_name("t")
	.dwattr $C$DW$29, DW_AT_TI_symbol_name("_t")
	.dwattr $C$DW$29, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$29, DW_AT_location[DW_OP_regx 0x2b]

;* R0    assigned to _t
$C$DW$30	.dwtag  DW_TAG_variable
	.dwattr $C$DW$30, DW_AT_name("t")
	.dwattr $C$DW$30, DW_AT_TI_symbol_name("_t")
	.dwattr $C$DW$30, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$30, DW_AT_location[DW_OP_regx 0x2b]

;* R0    assigned to _t
$C$DW$31	.dwtag  DW_TAG_variable
	.dwattr $C$DW$31, DW_AT_name("t")
	.dwattr $C$DW$31, DW_AT_TI_symbol_name("_t")
	.dwattr $C$DW$31, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$31, DW_AT_location[DW_OP_regx 0x2b]

	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
        MOVL      *SP++,XAR2            ; [CPU_ALU] 
	.dwcfi	save_reg_to_mem, 9, 2
	.dwcfi	cfa_offset, -4
        ADDB      SP,#2                 ; [CPU_ARAU] 
	.dwcfi	cfa_offset, -6
        MOV       PL,AL                 ; [CPU_ALU] |55| 
	.dwpsn	file "../vector/median_SP_RV.c",line 64,column 5,is_stmt,isa 0
        ADDB      AL,#-1                ; [CPU_ALU] |64| 
        MOV       T,AL                  ; [CPU_ALU] |64| 
	.dwpsn	file "../vector/median_SP_RV.c",line 63,column 5,is_stmt,isa 0
        MOV       PH,#0                 ; [CPU_ALU] |63| 
	.dwpsn	file "../vector/median_SP_RV.c",line 65,column 5,is_stmt,isa 0
        MOV       AH,T                  ; [CPU_ALU] |65| 
        LSR       AH,1                  ; [CPU_ALU] |65| 
        MOVZ      AR2,AH                ; [CPU_ALU] |65| 
        B         $C$L8,UNC             ; [CPU_ALU] 
        ; branch occurs ; [] 
$C$L6:    
        MOV       AL,PH                 ; [CPU_ALU] 
	.dwpsn	file "../vector/median_SP_RV.c",line 124,column 9,is_stmt,isa 0
        MOV       ACC,AL << 1           ; [CPU_ALU] |124| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |124| 
        MOVL      XAR6,ACC              ; [CPU_ALU] |124| 
        MOV       ACC,AR5 << 1          ; [CPU_ALU] |124| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |124| 
        MOVL      XAR7,ACC              ; [CPU_ALU] |124| 
        MOV32     R0H,*+XAR6[0]         ; [CPU_FPU] |124| 
        MOVL      ACC,*+XAR7[0]         ; [CPU_ALU] |124| 
        MOVL      *+XAR6[0],ACC         ; [CPU_ALU] |124| 
        MOV       AH,AR2                ; [CPU_ALU] |124| 
	.dwpsn	file "../vector/median_SP_RV.c",line 127,column 9,is_stmt,isa 0
        CMP       AH,AR5                ; [CPU_ALU] |127| 
	.dwpsn	file "../vector/median_SP_RV.c",line 124,column 9,is_stmt,isa 0
        MOV32     *+XAR7[0],R0H         ; [CPU_FPU] |124| 
	.dwpsn	file "../vector/median_SP_RV.c",line 127,column 9,is_stmt,isa 0
        B         $C$L7,LO              ; [CPU_ALU] |127| 
        ; branchcc occurs ; [] |127| 
	.dwpsn	file "../vector/median_SP_RV.c",line 127,column 27,is_stmt,isa 0
        MOV       PH,AR0                ; [CPU_ALU] |127| 
$C$L7:    
	.dwpsn	file "../vector/median_SP_RV.c",line 128,column 9,is_stmt,isa 0
        CMP       AH,AR5                ; [CPU_ALU] |128| 
        B         $C$L8,HI              ; [CPU_ALU] |128| 
        ; branchcc occurs ; [] |128| 
	.dwpsn	file "../vector/median_SP_RV.c",line 128,column 27,is_stmt,isa 0
        SUBB      XAR5,#1               ; [CPU_ARAU] |128| 
        MOV       T,AR5                 ; [CPU_ALU] |128| 
$C$L8:    
        MOV       AH,PH                 ; [CPU_ALU] 
	.dwpsn	file "../vector/median_SP_RV.c",line 70,column 9,is_stmt,isa 0
        CMP       AH,T                  ; [CPU_ALU] |70| 
        B         $C$L16,HIS            ; [CPU_ALU] |70| 
        ; branchcc occurs ; [] |70| 
	.dwpsn	file "../vector/median_SP_RV.c",line 82,column 9,is_stmt,isa 0
        MOV       AH,T                  ; [CPU_ALU] |82| 
        SUB       AH,PH                 ; [CPU_ALU] |82| 
        CMPB      AH,#1                 ; [CPU_ALU] |82| 
        B         $C$L15,EQ             ; [CPU_ALU] |82| 
        ; branchcc occurs ; [] |82| 
	.dwpsn	file "../vector/median_SP_RV.c",line 99,column 9,is_stmt,isa 0
        MOV       AH,T                  ; [CPU_ALU] |99| 
        CLRC      SXM                   ; [CPU_ALU] 
        ADD       AH,PH                 ; [CPU_ALU] |99| 
        LSR       AH,1                  ; [CPU_ALU] |99| 
        MOVZ      AR7,AH                ; [CPU_ALU] |99| 
	.dwpsn	file "../vector/median_SP_RV.c",line 100,column 9,is_stmt,isa 0
        MOV       ACC,T << 1            ; [CPU_ALU] |100| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |100| 
        MOVL      XAR6,ACC              ; [CPU_ALU] |100| 
        MOV       ACC,AR7 << 1          ; [CPU_ALU] |100| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |100| 
        MOVL      XAR5,ACC              ; [CPU_ALU] |100| 
        MOV32     R1H,*+XAR6[0]         ; [CPU_FPU] |100| 
        MOV32     R0H,*+XAR5[0]         ; [CPU_FPU] |100| 
        CMPF32    R0H,R1H               ; [CPU_FPU] |100| 
        MOVST0    ZF, NF                ; [CPU_FPU] |100| 
        B         $C$L9,LEQ             ; [CPU_ALU] |100| 
        ; branchcc occurs ; [] |100| 
	.dwpsn	file "../vector/median_SP_RV.c",line 100,column 37,is_stmt,isa 0
        MOV32     *+XAR5[0],R1H         ; [CPU_FPU] |100| 
        MOV32     *+XAR6[0],R0H         ; [CPU_FPU] |100| 
$C$L9:    
	.dwpsn	file "../vector/median_SP_RV.c",line 101,column 9,is_stmt,isa 0
        MOVZ      AR5,PH                ; [CPU_ALU] |101| 
        MOV       ACC,T << 1            ; [CPU_ALU] |101| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |101| 
        MOVL      XAR6,ACC              ; [CPU_ALU] |101| 
        MOV       ACC,AR5 << 1          ; [CPU_ALU] |101| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |101| 
        MOVL      XAR5,ACC              ; [CPU_ALU] |101| 
        MOV32     R1H,*+XAR6[0]         ; [CPU_FPU] |101| 
        MOV32     R0H,*+XAR5[0]         ; [CPU_FPU] |101| 
        CMPF32    R0H,R1H               ; [CPU_FPU] |101| 
        MOVST0    ZF, NF                ; [CPU_FPU] |101| 
        B         $C$L10,LEQ            ; [CPU_ALU] |101| 
        ; branchcc occurs ; [] |101| 
	.dwpsn	file "../vector/median_SP_RV.c",line 101,column 38,is_stmt,isa 0
        MOV32     *+XAR5[0],R1H         ; [CPU_FPU] |101| 
        MOV32     *+XAR6[0],R0H         ; [CPU_FPU] |101| 
$C$L10:    
        MOV       AL,PH                 ; [CPU_ALU] 
	.dwpsn	file "../vector/median_SP_RV.c",line 102,column 9,is_stmt,isa 0
        MOV       ACC,AL << 1           ; [CPU_ALU] |102| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |102| 
        MOVL      XAR6,ACC              ; [CPU_ALU] |102| 
        MOV       ACC,AR7 << 1          ; [CPU_ALU] |102| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |102| 
        MOVL      XAR5,ACC              ; [CPU_ALU] |102| 
        MOV32     R1H,*+XAR6[0]         ; [CPU_FPU] |102| 
        MOV32     R0H,*+XAR5[0]         ; [CPU_FPU] |102| 
        CMPF32    R0H,R1H               ; [CPU_FPU] |102| 
        MOVST0    ZF, NF                ; [CPU_FPU] |102| 
        B         $C$L11,LEQ            ; [CPU_ALU] |102| 
        ; branchcc occurs ; [] |102| 
	.dwpsn	file "../vector/median_SP_RV.c",line 102,column 40,is_stmt,isa 0
        MOV32     *+XAR5[0],R1H         ; [CPU_FPU] |102| 
        MOV32     *+XAR6[0],R0H         ; [CPU_FPU] |102| 
$C$L11:    
	.dwpsn	file "../vector/median_SP_RV.c",line 105,column 9,is_stmt,isa 0
        MOV       ACC,AR7 << 1          ; [CPU_ALU] |105| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |105| 
        MOVL      XAR6,ACC              ; [CPU_ALU] |105| 
        MOVB      AH,#1                 ; [CPU_ALU] |105| 
        ADD       AH,PH                 ; [CPU_ALU] |105| 
        MOVZ      AR0,AH                ; [CPU_ALU] |105| 
        MOV       ACC,AR0 << 1          ; [CPU_ALU] |105| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |105| 
        MOVL      XAR7,ACC              ; [CPU_ALU] |105| 
        MOV32     R0H,*+XAR6[0]         ; [CPU_FPU] |105| 
	.dwpsn	file "../vector/median_SP_RV.c",line 109,column 9,is_stmt,isa 0
        MOVZ      AR5,T                 ; [CPU_ALU] |109| 
	.dwpsn	file "../vector/median_SP_RV.c",line 105,column 9,is_stmt,isa 0
        MOVL      ACC,*+XAR7[0]         ; [CPU_ALU] |105| 
        MOVL      *+XAR6[0],ACC         ; [CPU_ALU] |105| 
        MOV32     *+XAR7[0],R0H         ; [CPU_FPU] |105| 
$C$L12:    
	.dwpsn	file "../vector/median_SP_RV.c",line 113,column 13,is_stmt,isa 0
        MOV       AL,AR0                ; [CPU_ALU] |113| 
        CLRC      SXM                   ; [CPU_ALU] 
        MOV       ACC,AL << 1           ; [CPU_ALU] |113| 
        CLRC      SXM                   ; [CPU_ALU] 
        ADDL      ACC,XAR4              ; [CPU_ALU] |113| 
        ADDB      ACC,#2                ; [CPU_ALU] |113| 
        MOVL      XAR7,ACC              ; [CPU_ALU] |113| 
$C$L13:    
        MOV       AL,PH                 ; [CPU_ALU] 
	.dwpsn	file "../vector/median_SP_RV.c",line 114,column 29,is_stmt,isa 0
        MOV       ACC,AL << 1           ; [CPU_ALU] |114| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |114| 
	.dwpsn	file "../vector/median_SP_RV.c",line 114,column 16,is_stmt,isa 0
        MOVL      XAR6,ACC              ; [CPU_ALU] |114| 
        ADDB      XAR0,#1               ; [CPU_ALU] |114| 
	.dwpsn	file "../vector/median_SP_RV.c",line 114,column 29,is_stmt,isa 0
        MOV32     R1H,*XAR7++           ; [CPU_FPU] |114| 
        MOV32     R0H,*+XAR6[0]         ; [CPU_FPU] |114| 
        CMPF32    R0H,R1H               ; [CPU_FPU] |114| 
        MOVST0    ZF, NF                ; [CPU_FPU] |114| 
        B         $C$L13,GT             ; [CPU_ALU] |114| 
        ; branchcc occurs ; [] |114| 
	.dwpsn	file "../vector/median_SP_RV.c",line 115,column 13,is_stmt,isa 0
        MOV       ACC,AR5 << 1          ; [CPU_ALU] |115| 
        CLRC      SXM                   ; [CPU_ALU] 
        ADDL      ACC,XAR4              ; [CPU_ALU] |115| 
        SUBB      ACC,#2                ; [CPU_ALU] |115| 
        MOVL      XAR7,ACC              ; [CPU_ALU] |115| 
$C$L14:    
        MOV       AL,PH                 ; [CPU_ALU] 
	.dwpsn	file "../vector/median_SP_RV.c",line 116,column 29,is_stmt,isa 0
        MOV       ACC,AL << 1           ; [CPU_ALU] |116| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |116| 
	.dwpsn	file "../vector/median_SP_RV.c",line 116,column 16,is_stmt,isa 0
        MOVL      XAR6,ACC              ; [CPU_ALU] |116| 
	.dwpsn	file "../vector/median_SP_RV.c",line 116,column 29,is_stmt,isa 0
        SUBB      XAR7,#2               ; [CPU_ALU] |116| 
        MOV32     R1H,*+XAR7[2]         ; [CPU_FPU] |116| 
	.dwpsn	file "../vector/median_SP_RV.c",line 116,column 16,is_stmt,isa 0
        SUBB      XAR5,#1               ; [CPU_ARAU] |116| 
	.dwpsn	file "../vector/median_SP_RV.c",line 116,column 29,is_stmt,isa 0
        MOV32     R0H,*+XAR6[0]         ; [CPU_FPU] |116| 
        CMPF32    R1H,R0H               ; [CPU_FPU] |116| 
        MOVST0    ZF, NF                ; [CPU_FPU] |116| 
        B         $C$L14,GT             ; [CPU_ALU] |116| 
        ; branchcc occurs ; [] |116| 
        MOV       AH,AR0                ; [CPU_ALU] 
	.dwpsn	file "../vector/median_SP_RV.c",line 118,column 26,is_stmt,isa 0
        CMP       AH,AR5                ; [CPU_ALU] |118| 
        B         $C$L6,HI              ; [CPU_ALU] |118| 
        ; branchcc occurs ; [] |118| 
	.dwpsn	file "../vector/median_SP_RV.c",line 120,column 13,is_stmt,isa 0
        MOV       AL,AR0                ; [CPU_ALU] |120| 
        MOV       ACC,AL << 1           ; [CPU_ALU] |120| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |120| 
        MOVL      XAR6,ACC              ; [CPU_ALU] |120| 
        MOV       ACC,AR5 << 1          ; [CPU_ALU] |120| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |120| 
        MOVL      XAR7,ACC              ; [CPU_ALU] |120| 
        MOV32     R0H,*+XAR6[0]         ; [CPU_FPU] |120| 
        MOVL      ACC,*+XAR7[0]         ; [CPU_ALU] |120| 
        MOVL      *+XAR6[0],ACC         ; [CPU_ALU] |120| 
        MOV32     *+XAR7[0],R0H         ; [CPU_FPU] |120| 
	.dwpsn	file "../vector/median_SP_RV.c",line 121,column 9,is_stmt,isa 0
        B         $C$L12,UNC            ; [CPU_ALU] |121| 
        ; branch occurs ; [] |121| 
$C$L15:    
        CLRC      SXM                   ; [CPU_ALU] 
	.dwpsn	file "../vector/median_SP_RV.c",line 84,column 13,is_stmt,isa 0
        MOV       ACC,T << 1            ; [CPU_ALU] |84| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |84| 
        MOVL      XAR6,ACC              ; [CPU_ALU] |84| 
        MOV       ACC,PH << 1           ; [CPU_ALU] |84| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |84| 
        MOVL      XAR5,ACC              ; [CPU_ALU] |84| 
        MOV32     R1H,*+XAR6[0]         ; [CPU_FPU] |84| 
        MOV32     R0H,*+XAR5[0]         ; [CPU_FPU] |84| 
        CMPF32    R0H,R1H               ; [CPU_FPU] |84| 
        MOVST0    ZF, NF                ; [CPU_FPU] |84| 
        B         $C$L16,LEQ            ; [CPU_ALU] |84| 
        ; branchcc occurs ; [] |84| 
	.dwpsn	file "../vector/median_SP_RV.c",line 84,column 35,is_stmt,isa 0
        MOV32     *+XAR5[0],R1H         ; [CPU_FPU] |84| 
        MOV32     *+XAR6[0],R0H         ; [CPU_FPU] |84| 
$C$L16:    
	.dwpsn	file "../vector/median_SP_RV.c",line 78,column 17,is_stmt,isa 0
        TBIT      PL,#0                 ; [CPU_ALU] |78| 
        B         $C$L17,NTC            ; [CPU_ALU] |78| 
        ; branchcc occurs ; [] |78| 
        CLRC      SXM                   ; [CPU_ALU] 
        MOV       ACC,AR2 << 1          ; [CPU_ALU] |78| 
        ADDL      XAR4,ACC              ; [CPU_ALU] |78| 
        MOV32     R0H,*+XAR4[0]         ; [CPU_FPU] |78| 
        B         $C$L18,UNC            ; [CPU_ALU] |78| 
        ; branch occurs ; [] |78| 
$C$L17:    
        CLRC      SXM                   ; [CPU_ALU] 
        MOV       ACC,AR2 << 1          ; [CPU_ALU] |78| 
        ADDL      ACC,XAR4              ; [CPU_ALU] |78| 
        MOVL      XAR5,ACC              ; [CPU_ALU] |78| 
        MOV       AL,PL                 ; [CPU_ALU] |78| 
        MOV32     R0H,*+XAR5[0]         ; [CPU_FPU] |78| 
$C$DW$32	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$32, DW_AT_low_pc(0x00)
	.dwattr $C$DW$32, DW_AT_name("__median_find_average_SP_RV")
	.dwattr $C$DW$32, DW_AT_TI_call

        LCR       #__median_find_average_SP_RV ; [CPU_ALU] |78| 
        ; call occurs [#__median_find_average_SP_RV] ; [] |78| 
$C$L18:    
        SUBB      SP,#2                 ; [CPU_ARAU] 
	.dwcfi	cfa_offset, -4
        MOVL      XAR2,*--SP            ; [CPU_ALU] 
	.dwcfi	cfa_offset, -2
	.dwcfi	restore_reg, 9
$C$DW$33	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$33, DW_AT_low_pc(0x00)
	.dwattr $C$DW$33, DW_AT_TI_return

        LRETR     ; [CPU_ALU] 
        ; return occurs ; [] 
	.dwattr $C$DW$13, DW_AT_TI_end_file("../vector/median_SP_RV.c")
	.dwattr $C$DW$13, DW_AT_TI_end_line(0x84)
	.dwattr $C$DW$13, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$13


;***************************************************************
;* TYPE INFORMATION                                            *
;***************************************************************
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

$C$DW$T$20	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$20, DW_AT_name("__uint16_t")
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$20, DW_AT_language(DW_LANG_C)

$C$DW$T$21	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$21, DW_AT_name("uint16_t")
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$21, DW_AT_language(DW_LANG_C)

$C$DW$34	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$34, DW_AT_type(*$C$DW$T$21)

$C$DW$T$22	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$34)

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

$C$DW$T$23	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$16)
	.dwattr $C$DW$T$23, DW_AT_address_class(0x20)

$C$DW$35	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$35, DW_AT_type(*$C$DW$T$23)

$C$DW$T$24	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$35)

$C$DW$36	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$36, DW_AT_type(*$C$DW$T$16)

$C$DW$T$28	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$28, DW_AT_type(*$C$DW$36)

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

$C$DW$37	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$37, DW_AT_name("AL")
	.dwattr $C$DW$37, DW_AT_location[DW_OP_reg0]

$C$DW$38	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$38, DW_AT_name("AH")
	.dwattr $C$DW$38, DW_AT_location[DW_OP_reg1]

$C$DW$39	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$39, DW_AT_name("PL")
	.dwattr $C$DW$39, DW_AT_location[DW_OP_reg2]

$C$DW$40	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$40, DW_AT_name("PH")
	.dwattr $C$DW$40, DW_AT_location[DW_OP_reg3]

$C$DW$41	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$41, DW_AT_name("SP")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_reg20]

$C$DW$42	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$42, DW_AT_name("XT")
	.dwattr $C$DW$42, DW_AT_location[DW_OP_reg21]

$C$DW$43	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$43, DW_AT_name("T")
	.dwattr $C$DW$43, DW_AT_location[DW_OP_reg22]

$C$DW$44	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$44, DW_AT_name("ST0")
	.dwattr $C$DW$44, DW_AT_location[DW_OP_reg23]

$C$DW$45	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$45, DW_AT_name("ST1")
	.dwattr $C$DW$45, DW_AT_location[DW_OP_reg24]

$C$DW$46	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$46, DW_AT_name("PC")
	.dwattr $C$DW$46, DW_AT_location[DW_OP_reg25]

$C$DW$47	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$47, DW_AT_name("RPC")
	.dwattr $C$DW$47, DW_AT_location[DW_OP_reg26]

$C$DW$48	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$48, DW_AT_name("FP")
	.dwattr $C$DW$48, DW_AT_location[DW_OP_reg28]

$C$DW$49	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$49, DW_AT_name("DP")
	.dwattr $C$DW$49, DW_AT_location[DW_OP_reg29]

$C$DW$50	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$50, DW_AT_name("SXM")
	.dwattr $C$DW$50, DW_AT_location[DW_OP_reg30]

$C$DW$51	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$51, DW_AT_name("PM")
	.dwattr $C$DW$51, DW_AT_location[DW_OP_reg31]

$C$DW$52	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$52, DW_AT_name("OVM")
	.dwattr $C$DW$52, DW_AT_location[DW_OP_regx 0x20]

$C$DW$53	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$53, DW_AT_name("PAGE0")
	.dwattr $C$DW$53, DW_AT_location[DW_OP_regx 0x21]

$C$DW$54	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$54, DW_AT_name("AMODE")
	.dwattr $C$DW$54, DW_AT_location[DW_OP_regx 0x22]

$C$DW$55	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$55, DW_AT_name("EALLOW")
	.dwattr $C$DW$55, DW_AT_location[DW_OP_regx 0x4e]

$C$DW$56	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$56, DW_AT_name("INTM")
	.dwattr $C$DW$56, DW_AT_location[DW_OP_regx 0x23]

$C$DW$57	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$57, DW_AT_name("IFR")
	.dwattr $C$DW$57, DW_AT_location[DW_OP_regx 0x24]

$C$DW$58	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$58, DW_AT_name("IER")
	.dwattr $C$DW$58, DW_AT_location[DW_OP_regx 0x25]

$C$DW$59	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$59, DW_AT_name("V")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_regx 0x26]

$C$DW$60	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$60, DW_AT_name("PSEUDOH")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_regx 0x4c]

$C$DW$61	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$61, DW_AT_name("VOL")
	.dwattr $C$DW$61, DW_AT_location[DW_OP_regx 0x4d]

$C$DW$62	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$62, DW_AT_name("AR0")
	.dwattr $C$DW$62, DW_AT_location[DW_OP_reg4]

$C$DW$63	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$63, DW_AT_name("XAR0")
	.dwattr $C$DW$63, DW_AT_location[DW_OP_reg5]

$C$DW$64	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$64, DW_AT_name("AR1")
	.dwattr $C$DW$64, DW_AT_location[DW_OP_reg6]

$C$DW$65	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$65, DW_AT_name("XAR1")
	.dwattr $C$DW$65, DW_AT_location[DW_OP_reg7]

$C$DW$66	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$66, DW_AT_name("AR2")
	.dwattr $C$DW$66, DW_AT_location[DW_OP_reg8]

$C$DW$67	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$67, DW_AT_name("XAR2")
	.dwattr $C$DW$67, DW_AT_location[DW_OP_reg9]

$C$DW$68	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$68, DW_AT_name("AR3")
	.dwattr $C$DW$68, DW_AT_location[DW_OP_reg10]

$C$DW$69	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$69, DW_AT_name("XAR3")
	.dwattr $C$DW$69, DW_AT_location[DW_OP_reg11]

$C$DW$70	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$70, DW_AT_name("AR4")
	.dwattr $C$DW$70, DW_AT_location[DW_OP_reg12]

$C$DW$71	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$71, DW_AT_name("XAR4")
	.dwattr $C$DW$71, DW_AT_location[DW_OP_reg13]

$C$DW$72	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$72, DW_AT_name("AR5")
	.dwattr $C$DW$72, DW_AT_location[DW_OP_reg14]

$C$DW$73	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$73, DW_AT_name("XAR5")
	.dwattr $C$DW$73, DW_AT_location[DW_OP_reg15]

$C$DW$74	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$74, DW_AT_name("AR6")
	.dwattr $C$DW$74, DW_AT_location[DW_OP_reg16]

$C$DW$75	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$75, DW_AT_name("XAR6")
	.dwattr $C$DW$75, DW_AT_location[DW_OP_reg17]

$C$DW$76	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$76, DW_AT_name("AR7")
	.dwattr $C$DW$76, DW_AT_location[DW_OP_reg18]

$C$DW$77	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$77, DW_AT_name("XAR7")
	.dwattr $C$DW$77, DW_AT_location[DW_OP_reg19]

$C$DW$78	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$78, DW_AT_name("R0H")
	.dwattr $C$DW$78, DW_AT_location[DW_OP_regx 0x2b]

$C$DW$79	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$79, DW_AT_name("R1H")
	.dwattr $C$DW$79, DW_AT_location[DW_OP_regx 0x2f]

$C$DW$80	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$80, DW_AT_name("R2H")
	.dwattr $C$DW$80, DW_AT_location[DW_OP_regx 0x33]

$C$DW$81	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$81, DW_AT_name("R3H")
	.dwattr $C$DW$81, DW_AT_location[DW_OP_regx 0x37]

$C$DW$82	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$82, DW_AT_name("R4H")
	.dwattr $C$DW$82, DW_AT_location[DW_OP_regx 0x3b]

$C$DW$83	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$83, DW_AT_name("R5H")
	.dwattr $C$DW$83, DW_AT_location[DW_OP_regx 0x3f]

$C$DW$84	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$84, DW_AT_name("R6H")
	.dwattr $C$DW$84, DW_AT_location[DW_OP_regx 0x43]

$C$DW$85	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$85, DW_AT_name("R7H")
	.dwattr $C$DW$85, DW_AT_location[DW_OP_regx 0x47]

$C$DW$86	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$86, DW_AT_name("RB")
	.dwattr $C$DW$86, DW_AT_location[DW_OP_regx 0x4a]

$C$DW$87	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$87, DW_AT_name("STF")
	.dwattr $C$DW$87, DW_AT_location[DW_OP_regx 0x28]

$C$DW$88	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$88, DW_AT_name("FPUHAZ")
	.dwattr $C$DW$88, DW_AT_location[DW_OP_reg27]

$C$DW$89	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$89, DW_AT_name("STF_HWDIV")
	.dwattr $C$DW$89, DW_AT_location[DW_OP_regx 0x4f]

$C$DW$90	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$90, DW_AT_name("VCRC")
	.dwattr $C$DW$90, DW_AT_location[DW_OP_regx 0x50]

$C$DW$91	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$91, DW_AT_name("VSTATUS")
	.dwattr $C$DW$91, DW_AT_location[DW_OP_regx 0x51]

	.dwendtag $C$DW$CU

