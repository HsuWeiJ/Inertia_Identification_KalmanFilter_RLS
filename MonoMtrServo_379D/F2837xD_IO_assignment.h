//----------------------------------------------------------------------------------
//	FILE:			F2837xS_IO_assignment.h
//
//	Description:	Contains IO assignments for the project
//
//	Version: 		1.0
//
//  Target:  		TMS320F28377D
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments � 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// 4 Nov 2015 - CPU IO assignments
//----------------------------------------------------------------------------------


#ifndef F2837xD_IO_ASSIGNMENT_H_
#define F2837xD_IO_ASSIGNMENT_H_

#include "MonoMtrServo-Settings.h"

/******************************************************************************
Peripheral Assignments:
   MOTOR 1:
     - EPWMs ==>> A, B, C -> EPWM1, EPWM2, EPWM3
     - QEP   ==>> EQep3
     - SPI   ==>> Spia

     Analog signals - Motor 1
     Va   ADC (A)14
     Vb   ADC C3
     Vc   ADC B3
     Vdc  ADC A3
     Ia   ADC C2
     Ib   ADC B2
     Ic   ADC A2

    PWMDACs -> EPWM7, EPWM8
    DACs    -> DACA, DACB
    ECAPs   -> ECAP1, ECAP2, ECAP3, ECAP4 // only for level8

    DAC-C  ---> General purpose display (??) // wait to add

******************************************************************************/

// *************************************************
// ************ GPIO pin assignments ***************
// *************************************************

// General purpose useage (used by QEP1-I)
#define  BLUE_LED_GPIO    31
#define  BLUE_LED_MUX      0

#define  TEMP_GPIO        34
#define  TEMP_MUX          0


// ***************************************************************
// MOTOR 1 EPWMDAC selections
// ========================
#define  MOTOR1_EPWMDAC_A_GPIO     157
#define  MOTOR1_EPWMDAC_A_MUX      1

#define  MOTOR1_EPWMDAC_Ab_GPIO    158
#define  MOTOR1_EPWMDAC_Ab_MUX     1

#define  MOTOR1_EPWMDAC_B_GPIO     159
#define  MOTOR1_EPWMDAC_B_MUX      1

#define  MOTOR1_EPWMDAC_Bb_GPIO    160
#define  MOTOR1_EPWMDAC_Bb_MUX     1


// ***************************************************************
// MOTOR 1 EPWM selections
// ========================
#define  MOTOR1_EPWM_A_GPIO     0
#define  MOTOR1_EPWM_A_MUX      1

#define  MOTOR1_EPWM_B_GPIO     2
#define  MOTOR1_EPWM_B_MUX      1

#define  MOTOR1_EPWM_C_GPIO     4
#define  MOTOR1_EPWM_C_MUX      1

// ***************************************************************
// MOTOR 1 EQEP selections
// ========================
#define  MOTOR1_QEPA_GPIO       20
#define  MOTOR1_QEPA_MUX         1

#define  MOTOR1_QEPB_GPIO       21
#define  MOTOR1_QEPB_MUX         1

#define  MOTOR1_QEPI_GPIO       99
#define  MOTOR1_QEPI_MUX         5

// ***************************************************************
// MOTOR 1 - SPI selections
// =========================
#define  MOTOR1_SDI_GPIO       58
#define  MOTOR1_SDI_MUX        15

#define  MOTOR1_SDO_GPIO       59
#define  MOTOR1_SDO_MUX        15

#define  MOTOR1_CLK_GPIO       60
#define  MOTOR1_CLK_MUX        15

// ***************************************************************
// MOTOR 1 DRVxx selections
// ========================
#define  MOTOR1_SCS_GPIO        61
#define  MOTOR1_SCS_MUX         15

#define  MOTOR1_EN_GATE_GPIO   124
#define  MOTOR1_EN_GATE_MUX      0

#define  MOTOR1_FAULT_GPIO      19
#define  MOTOR1_FAULT_MUX        0

#if (MOTOR1_DRV == DRV8301)
  #define  MOTOR1_DC_CAL_GPIO    73
  #define  MOTOR1_DC_CAL_MUX      0

  #define  MOTOR1_OCTW_GPIO      89
  #define  MOTOR1_OCTW_MUX        0
#else
  #define  MOTOR1_WAKE_GPIO     125
  #define  MOTOR1_WAKE_MUX        0

  #define  MOTOR1_PWRGD_GPIO     // tied to RESET# input of MCU - no use in code
#endif

// ***************************************************************
// USER GPIO SELECTIONS
// =========================

#define GPIO25       25
#define GPIO25_MUX   0

// ***************************************************************
// SPIDAC GPIO SELECTIONS
// =========================
#define  SPIDAC_MOSI_GPIO      63
#define  SPIDAC_MOSI_MUX       15

#define  SPIDAC_MISO_GPIO      64
#define  SPIDAC_MISO_MUX       15

#define  SPIDAC_CLK_GPIO       65
#define  SPIDAC_CLK_MUX        15

#define  SPIDAC_CS_GPIO        66
#define  SPIDAC_CS_MUX         15

// ***************************************************************
// ECAP selections
// ========================
#define  ECAP1_GPIO       8
#define  ECAP1_MUX        0

#define  ECAP2_GPIO       9
#define  ECAP2_MUX        0

#define  ECAP3_GPIO       10
#define  ECAP3_MUX        0

#define  ECAP4_GPIO       11
#define  ECAP4_MUX        0

// *************************************************
// ************ ADC pin assignments ***************
// *************************************************

//#define IFB_A1       AdcaResultRegs.ADCRESULT0
//#define IFB_B1       AdcbResultRegs.ADCRESULT0
//#define IFB_C1       AdcaResultRegs.ADCRESULT1
//#define IFB_A1_PPB   ((signed int)AdcaResultRegs.ADCPPB1RESULT.all)
//#define IFB_B1_PPB   ((signed int)AdcbResultRegs.ADCPPB1RESULT.all)
//#define IFB_C1_PPB   ((signed int)AdcaResultRegs.ADCPPB2RESULT.all)
//
//#define VFB_A1       AdcbResultRegs.ADCRESULT1
//#define VFB_B1       AdcbResultRegs.ADCRESULT2
//#define VFB_C1       AdcbResultRegs.ADCRESULT3
//#define VFB_DC1      AdcbResultRegs.ADCRESULT4

// MOTOR 1 Analog definitions
// ============================
#define IFB_A1       AdccResultRegs.ADCRESULT0
#define IFB_B1       AdcbResultRegs.ADCRESULT0
#define IFB_C1       AdcaResultRegs.ADCRESULT2
#define IFB_A1_PPB   ((signed int)AdccResultRegs.ADCPPB1RESULT.all) // need to check
#define IFB_B1_PPB   ((signed int)AdcbResultRegs.ADCPPB1RESULT.all) // need to check
#define IFB_C1_PPB   ((signed int)AdcaResultRegs.ADCPPB1RESULT.all) // need to check

#if (MOTOR1_DRV == DRV8301)
  #define VFB_A1       AdcbResultRegs.ADCRESULT4
  #define VFB_B1       AdcbResultRegs.ADCRESULT3
  #define VFB_C1       AdcbResultRegs.ADCRESULT2
  #define VFB_DC1      AdcbResultRegs.ADCRESULT6
#else
  #define VFB_B1       AdccResultRegs.ADCRESULT4
  #define VFB_C1       AdcbResultRegs.ADCRESULT3
  #define VFB_DC1      AdcaResultRegs.ADCRESULT2
  #define VFB_A1       AdcaResultRegs.ADCRESULT6
#endif

#define ADC_PU_SCALE_FACTOR        0.000244140625     //1/2^12 // need to check
#define ADC_PU_PPB_SCALE_FACTOR    0.000488281250     //1/2^11 // need to check
/*****************************************************************************
 *****************************************************************************/

#endif /* F2837xD_IO_ASSIGNMENT_H_ */
