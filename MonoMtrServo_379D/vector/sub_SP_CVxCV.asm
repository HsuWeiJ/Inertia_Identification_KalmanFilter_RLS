;;#############################################################################
;;! \file source/vector/sub_SP_CVxCV.asm
;;!
;;! \brief  C-Callable subtraction of a complex vector and a complex vector
;;! \author David M. Alter
;;! \date   06/21/13
;;
;; HISTORY:
;;   07/15/11 - original (D. Alter)
;;
;; DESCRIPTION: C-Callable subtraction of a complex vector and a complex vector
;;              y_re[i] = w_re[i] - x_re[i]
;;              y_im[i] = w_im[i] - x_im[i]
;;
;; FUNCTION: 
;;   extern void sub_SP_CVxCV(complex_float *y, const complex_float *w, 
;;                            const complex_float *x, const Uint16 N)
;;
;; USAGE:       sub_SP_CVxCV(y, w, x, N);
;;
;; PARAMETERS:  complex_float *y = result complex array
;;              complex_float *w = input complex array #1
;;              complex_float *x = input complex array #2
;;              Uint16 N = length of w, x, and y arrays
;;
;; RETURNS:     none
;;
;; BENCHMARK:   6*N + 15 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be at least 2.
;;   2) The inputs and return value are of type 'complex_float':
;;
;;      typedef struct {
;;         float32 dat[2];
;;      } complex_float;
;;
;;  Group:            C2000
;;  Target Family:    C28x+FPU32
;;
;;#############################################################################
;;
;;
;; $Copyright: Copyright (C) 2022 Texas Instruments Incorporated -
;;             http://www.ti.com/ ALL RIGHTS RESERVED $
;;#############################################################################
        .if __TI_EABI__
        .asg    sub_SP_CVxCV, _sub_SP_CVxCV
        .endif
    
        .global _sub_SP_CVxCV
        .text
_sub_SP_CVxCV:
        MOVL        XAR6, *-SP[4]    ;XAR6 = &x
        ADDB        AL, #-2          ;subtract 2 from N since RPTB is 'n-1' 
                                     ;times and last iteration done separately

        MOV32       R0H, *XAR5++     ;load first w_re[i]

;---Main loop
        RPTB        end_loop, @AL

        MOV32       R1H, *XAR6++     ;load next x_re[i]
                                     
        SUBF32      R2H, R0H, R1H    ;y_re[i] = w_re[i] - x_re[i]
        || MOV32    R0H, *XAR5++     ;load w_im[i]

        MOV32       R1H, *XAR6++     ;load x_im[i]    

        SUBF32      R3H, R0H, R1H    ;y_im[i] = w_im[i] - x_im[i]
        || MOV32    R0H, *XAR5++     ;load next w_re[i]

        MOV32       *XAR4++, R2H     ;store y_re[i]
        MOV32       *XAR4++, R3H     ;store y_im[i]

end_loop:

;--- Last iteration done separately to avoid possible pointer overrun into 
;    undefined memory
        MOV32        R1H, *XAR6++   ;load next x_re[i]

        SUBF32      R2H, R0H, R1H   ;y_re[i] = w_re[i] - x_re[i]
        || MOV32    R0H, *XAR5      ;load w_im[i]

        MOV32       R1H, *XAR6      ;load x_im[i]    

        SUBF32      R3H, R0H, R1H   ;y_im[i] = w_im[i] - x_im[i]

        MOV32       *XAR4++, R2H    ;store y_re[i]
        MOV32       *XAR4++, R3H    ;store y_im[i]

;Finish up
        LRETR                       ;return

;end of function _sub_SP_CVxCV()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
