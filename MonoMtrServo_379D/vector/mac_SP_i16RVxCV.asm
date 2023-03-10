;;#############################################################################
;;! \file source/vector/mac_SP_i16RVxCV.asm
;;!
;;! \brief  C-Callable multiply-and-accumulate of a signed 16-bit integer real
;;              vector and a floating pt. complex vector
;;! \author David M. Alter
;;! \date   04/24/15
;;
;; HISTORY:
;;    - original (D. Alter)
;;
;; DESCRIPTION: C-Callable multiply-and-accumulate of a signed 16-bit integer
;;              real vector and a floating pt. complex vector
;                y_re = sum(x[i]*w_re[i])
;                y_im = sum(x[i]*w_im[i])
;;
;; FUNCTION: 
;;   extern complex_float mac_SP_i16RVxCV(const complex_float *w,
;;                            const int16 *x, const Uint16 N)
;;
;; USAGE:       y = mac_SP_i16RVxCV(x, c, N);
;;
;; PARAMETERS:  complex_float *w = input complex array
;;              int16 *x  = input real array
;;              Uint16 N = length of w and x arrays
;; 
;; RETURNS:     complex_float y = complex result
;; 
;; BENCHMARK:   3*N + 28 cycles if N=even (including the call and return)
;;              3*N + 29 cycles if N=odd (including the call and return)
;; 
;; NOTES:
;;   1) N must be at least 5, and can be odd or even.
;;   2) The main loop is unrolled once, but does NOT require N to be even.
;;      The N=odd case is handled by executing one iteration prior to the main
;;      loop, and then executing the unrolled loop for the remaining even 
;;      counts.
;;   3) The input w and return value are of type 'complex_float':
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
    .asg mac_SP_i16RVxCV, _mac_SP_i16RVxCV
    .endif
    
    .global _mac_SP_i16RVxCV
    .text

_mac_SP_i16RVxCV:
    MOV32       *SP++,R7H      ;Save R7H (save-on-entry register)
    MOV32       *SP++,R6H      ;Save R6H (save-on-entry register)
    MOV32       *SP++,R5H      ;Save R5H (save-on-entry register)

    ZERO        R3H            ;Zero R3H (y_re accumulator)
    ZERO        R7H            ;Zero R7H (y_im accumulator)
                               
    TBIT        AL, #0         ;Test if N odd or even (result stored in TC bit)
    ADDB        AL, #1         ;Add 1 to properly handle the N=odd case (no 
                               ;effect on N=even case)
    LSR         AL, #1         ;Divide N by 2 (main loop is spatially unrolled 
                               ;once to eliminate delay slots)
    ADDB        AL, #-3        ;Subtract 3 since RPTB is 'n-1' times, and first
                               ;and last iterations done separately

    I16TOF32    R1H, *XAR5++   ;load first x[i]
    MOV32       R0H, *XAR4++   ;load first w_re[i]

;--- First loop iteration done separately to avoid having to zero R2H and R6H
;    registers, and also for odd/even loop count control.

    MPYF32      R2H, R1H, R0H               ;R2H = x[i]*w_re[i]
    || MOV32    R0H, *XAR4++                ;load w_im[i]
    MPYF32      R6H, R1H, R0H               ;R6H = x[i]*w_im[i]
    || MOV32    R0H, *XAR4++                ;load w_re[i+1]

    BF          line1, TC                   ;skip one MAC set if N was odd

    I16TOF32    R5H, *XAR5++                ;load x[i+1]
    NOP                                     ;delay slot
    MACF32      R3H, R2H, R2H, R5H, R0H     ;y_re += R2H, R2H = x[i+1]*w_re[i+1]
    || MOV32    R0H, *XAR4++                ;load w_im[i+1]
    MACF32      R7H, R6H, R6H, R5H, R0H     ;y_im += R6H, R6H = x[i+1]*w_im[i+1]
    || MOV32    R0H, *XAR4++                ;load w_re[i]

;---Main loop
line1:
    I16TOF32    R1H, *XAR5++                ;load x[i]
    RPTB        end_loop, @AL

    MACF32      R3H, R2H, R2H, R1H, R0H     ;y_re += R2H, R2H = x[i]*w_re[i]
    || MOV32    R0H, *XAR4++                ;load w_im[i]
    I16TOF32    R5H, *XAR5++                ;load x[i+1]
    MACF32      R7H, R6H, R6H, R1H, R0H     ;y_im += R6H, R6H = x[i]*w_im[i]
    || MOV32    R0H, *XAR4++                ;load w_re[i+1]
                
    MACF32      R3H, R2H, R2H, R5H, R0H     ;y_re += R2H, R2H = x[i+1]*w_re[i+1]
    || MOV32    R0H, *XAR4++                ;load w_im[i+1]
    I16TOF32    R1H, *XAR5++                ;load x[i]
    MACF32      R7H, R6H, R6H, R5H, R0H     ;y_im += R6H, R6H = x[i+1]*w_im[i+1]
    || MOV32    R0H, *XAR4++                ;load w_re[i]

end_loop:

;--- Last loop iteration done separately to avoid pointer overrun and loading
;    from possibly undefined memory
    MACF32      R3H, R2H, R2H, R1H, R0H     ;y_re += R2H, R2H = x[i]*w_re[i]
    || MOV32    R0H, *XAR4++                ;load w_im[i]
    I16TOF32    R5H, *XAR5++                ;load x[i+1]
    MACF32      R7H, R6H, R6H, R1H, R0H     ;y_im += R6H, R6H = x[i]*w_im[i]
    || MOV32    R0H, *XAR4++                ;load w_re[i+1]
                
    MACF32      R3H, R2H, R2H, R5H, R0H     ;y_re += R2H, R2H = x[i+1]*w_re[i+1]
    || MOV32    R0H, *XAR4                  ;load w_im[i+1]
    MACF32      R7H, R6H, R6H, R5H, R0H     ;y_im += R6H, R6H = x[i+1]*w_im[i+1]

;--- Final accumulations and result storage
    NOP                                     ;delay slot
    ADDF32      R3H, R3H, R2H               ;Final accumulate for y_re
    || MOV32    R5H,*--SP                   ;Restore R5H
    ADDF32      R7H, R7H, R6H               ;Final accumulate for y_im
    || MOV32    R6H,*--SP                   ;Restore R6H

;Store the return value
 	.if		__TI_EABI__
    MOV32       R0H, R3H                    ;store real part of return value
    MOV32       R1H, R7H                    ;store imag part of return value
    .else
    MOV32       *+XAR6[0], R3H              ;store real part of return value
    MOV32       *+XAR6[2], R7H              ;store imag part of return value
    .endif
;Finish up
    MOV32       R7H,*--SP                   ;Restore R7H
    LRETR                                   ;return

;end of function _mac_SP_i16RVxCV()
;*********************************************************************

    .end

;;#############################################################################
;;  End of File
;;#############################################################################
