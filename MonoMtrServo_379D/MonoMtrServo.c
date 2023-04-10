/* ============================================================================
System Name:  	Mono Motor Servo Control using F28377s-XL and BOOSTXL-DRV830x

File Name:	  	MonoMtrServo.c

Target:			F28377s Launch Pad

Author:			C2000 Systems Lab, 30th September 2015

Description:	Motor ISR
				Coded within ADCB1INT ISR @ 10Khz,
				  --> triggered by ADCA SOC6
				      --> set up by EPWM1_SOCA tied to EPWM1 PRD

//----------------------------------------------------------------------------------
//  Copyright Texas Instruments � 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// 4 Nov 2015 - Field Oriented Control of a PMSM with QEP feedback using F28377s-XL
 *              and BOOSTXL-DRV8301 or BOOSTXL-DRV8305EVM
//----------------------------------------------------------------------------------
 *
 *
Peripheral Assignments:
   MOTOR 1:
     - EPWMs ==>> A, B, C -> EPWM1, EPWM2, EPWM3
     - QEP   ==>> EQep1
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

	DAC-C  ---> General purpose display (??) // wait to add

===========================================================================  */

// Include header files used in the main function
// define float maths and then include IQmath library

#include "MonoMtrServo.h"

#include "MonoMtrServo-Settings.h"


// **********************************************************
// Prototypes for local functions within this file
// **********************************************************

#define RLS_TEST 1
#define KALMAN3X3_OR_2X2 1
#define WI_GEARBOX 0

// INTERRUPT FUNCTIONS
// ---------------------
#ifdef _FLASH
#pragma CODE_SECTION(MotorControlISR,"ramfuncs");
#endif

#pragma INTERRUPT (MotorControlISR, HPI)

// Prototype statements for functions found within this file.
interrupt void MotorControlISR(void);

// Core Motor Control Functions
// ------------------------------
#if BUILDLEVEL  != LEVEL1
inline void motorCurrentSense(void);
inline void motorVoltageSense(void);
inline void posEncoder(MOTOR_VARS * motor);
#endif

void PwmTripConfig(volatile struct EPWM_REGS * PwmRegs, Uint16 TripNum);
void DMC1_Protection(void);
void DMC2_Protection(void);

// Miscellaneous functions
// -------------------------
_iq refPosGen(_iq out);
_iq ramper(_iq in, _iq out, _iq rampDelta);
_iq ramper_speed(_iq in, _iq out, _iq rampDelta);
void GPIO_TogglePin(Uint16 pin);

// State Machine function prototypes
//------------------------------------
// Alpha states
void A0(void);	//state A0
void B0(void);	//state B0
void C0(void);	//state C0

// A branch states
void A1(void);	//state A1
void A2(void);	//state A2
void A3(void);	//state A3

// B branch states
void B1(void);	//state B1
void B2(void);	//state B2
void B3(void);	//state B3

// C branch states
void C1(void);	//state C1
void C2(void);	//state C2
void C3(void);	//state C3

// Variable declarations
void (*Alpha_State_Ptr)(void);	// Base States pointer
void (*A_Task_Ptr)(void);		// State pointer A branch
void (*B_Task_Ptr)(void);		// State pointer B branch
void (*C_Task_Ptr)(void);		// State pointer C branch

// ****************************************************************************
// Variables for CPU control
// ****************************************************************************
// adc static cal
int *adc_cal;

int16	VTimer0[4];			// Virtual Timers slaved off CPU Timer 0 (A events)
int16	VTimer1[4]; 		// Virtual Timers slaved off CPU Timer 1 (B events)
int16	VTimer2[4]; 		// Virtual Timers slaved off CPU Timer 2 (C events)
int16	SerialCommsTimer;

//*********************** USER Variables *************************************

//****************************************************************************
// Global variables used in this system
//****************************************************************************
char Speed_CMD_Switch = 1;
char DAC_Switch = 8;
char Angle_Switch = 0;

//Back EMF Decoupling
float Vq_Decoupling = 0;
float Vd_Decoupling = 0;

//Trapezoidal Speed CMD
float Speed_CMD_Data[2] = {0 , 0.01};

char Speed_CMD_Index = 0;
uint32_t Speed_CMD_Cnt = 0;
uint32_t Trapezoidal_Width = 30000;
float Speed_CMD;


int Initial_Cnt = 0;
int32 SpeedFBK_Cnt = 0;
int lsw_cnt = 0;
char lsw_flag = 0;

int DAC_Gain_A = 1000;
int DAC_Gain_B = 10;
int DAC_Gain_C = 2;
int DAC_Gain_D = 2;
#if WI_GEARBOX
float Speed_Kp_Gain = 4;
float Speed_Ki_Gain = 1;
#else
//Add brake
//float Speed_Kp_Gain = 5;
//float Speed_Ki_Gain = 30;
float Speed_Kp_Gain = 1;
float Speed_Ki_Gain = 1;
#endif

float test = 0;

//Observer Bandwidth
float Speed_Est_BW = 150 * 2 * PI;
float Acc_Est_BW = 50 * 2 * PI;

//Kalman Filter & RLS relative
Kalman Kalman3X3_Handler;
Kalman Kalman2X2_Handler;
RLS RLS_Handler;
LOW_PASS_FILTER Estimated_Acc = LOW_PASS_FILTER_DEFAULTS ;
LOW_PASS_FILTER RLS_Inertia = LOW_PASS_FILTER_DEFAULTS ;
LOW_PASS_FILTER Iq_FBK = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER Id_FBK = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER Kalman_e = LOW_PASS_FILTER_DEFAULTS;
LOW_PASS_FILTER Iq_test_Kt = LOW_PASS_FILTER_DEFAULTS;

float SpeedCmd[2] = {0.0};
float Kalman3X3_TL[2] = {0.0};
float Kalman2X2_TL[2] = {0.0};
float SpeedCmd0_1=0;
char RLS_Flag = 0;
char RLS_Start_Flag = 0;
float RLS_Gain = 1;
char Hybrid_flag = 0;
int RLS_cnt = 0;
int RLS_prescaler = 1;
float RLS_To_Kalman_J = J;
float Speed_err_threshold = 1e-07;

//Adaptive
char Adaptive_On = 0;

Matrix test1;
Matrix test2;
Matrix test3;
float result[4]={0,0,0,0};
float Te = 0;
float Te_TL_Fbk = 0;
float Te_TL_Cmd = 0;
float Acc_Threshold = 10;

float tt1[9] = {1,2,3,4,5,6,7,8,9};
float tt2[9] = {1,0,0,0,1,0,0,1,1};
float tt3[9] = {0};
float* fp1=tt1;
float* fp2=tt2;
float* fp3=tt3;


#if BUILDLEVEL == LEVEL3

/*******************Current Loop Bandwidth Test at Level 3*******************/
RMPCNTL rc_CurrentCmd_Control_Variation_Rate = RMPCNTL_DEFAULTS;
RAMPGEN rg_CurrentCmd_Generate_Sin = RAMPGEN_DEFAULTS;
float CurrentCmd_Sin_Frequency_pu = 0.2;

#endif

#if BUILDLEVEL == LEVEL4

/*******************Speed Loop Bandwidth Test at Level 4*******************/
RMPCNTL rc_SpeedCmd_SinFrequency_Variation_Rate = RMPCNTL_DEFAULTS;
RMPCNTL rc_SpeedCmd_Trapezoidal = RAMP_SPEED_DEFAULTS;
RAMPGEN rg_SpeedCmd_Generate_Sin = RAMPGEN_DEFAULTS;
float SpeedCmd_Sin_Frequency_pu = 0.001;
float SpeedCmd_Sin_Magnitude_pu = 0.0;

#endif

// ***************************************************************************
// Flag variables
// ***************************************************************************
volatile Uint16 EnableFlag = FALSE;

Uint32 IsrTicker = 0;

Uint16 BackTicker = 0;

int    LedCnt = 500;

int16 OffsetCalCounter;

_iq K1 = _IQ(0.998),		  // Offset filter coefficient K1: 0.05/(T+0.05);
    K2 = _IQ(0.001999);	      // Offset filter coefficient K2: T/(T+0.05);

MOTOR_VARS  motor1 = DRV830x_MOTOR_DEFAULTS;

// ****************************************************************************
// Miscellaneous Variables
// ****************************************************************************
_iq  IdRef_start = _IQ(0.1), // _IQ(0.1)
	 IdRef_run   = _IQ(0.0);

// Variables for position reference generation and control
// =========================================================
_iq   posArray[8] = { _IQ(1.5), _IQ(-1.5), _IQ(2.5), _IQ(-2.5) },
	  cntr1=0 ,
	  posSlewRate = _IQ(0.001);

int16 ptrMax = 2,
      ptr1=0;

#if (BUILDLEVEL==LEVEL1)
Uint16 DRV_RESET = 1;
#else
Uint16 DRV_RESET = 0;
#endif

// ****************************************************************************
// Variables for Datalog module
// ****************************************************************************
float DBUFF_4CH1[200],
      DBUFF_4CH2[200],
      DBUFF_4CH3[200],
      DBUFF_4CH4[200],
      DlogCh1,
      DlogCh2,
      DlogCh3,
      DlogCh4;

// Create an instance of DATALOG Module
DLOG_4CH_F dlog_4ch1;

// ****************************************************************************
// Variables for PWMDAC  module
// ****************************************************************************
int16 PwmDacCh1=0;
int16 PwmDacCh2=0;
int16 PwmDacCh3=0;
int16 PwmDacCh4=0;

// Instance a PWM DAC driver instance
PWMDAC pwmdac1 = PWMDAC_DEFAULTS;

//*******************************************************************************

#if BUILDLEVEL != LEVEL1
// ******************************************************************************
// CURRENT SENSOR SUITE
// - Reads motor currents from inverter bottom leg SHUNTs
// ******************************************************************************
inline void motorCurrentSense()
{
	motor1.currentAs = (float)IFB_A1_PPB* ADC_PU_PPB_SCALE_FACTOR;
	motor1.currentBs = (float)IFB_B1_PPB* ADC_PU_PPB_SCALE_FACTOR;
	motor1.currentCs = -motor1.currentAs - motor1.currentBs;

	return;
}

// ******************************************************************************
// VOLTAGE SENSOR SUITE
// - Reads motor voltages from inverter half-bridge outputs (phases A, B, and C)
//   and DC bus
// ******************************************************************************
inline void motorVoltageSense()
{
    // not used now
//    motor1.voltageAs = (float)VFB_A1* ADC_PU_SCALE_FACTOR;
//    motor1.voltageBs = (float)VFB_B1* ADC_PU_SCALE_FACTOR;
//    motor1.voltageCs = (float)VFB_C1* ADC_PU_SCALE_FACTOR;
    motor1.voltageDC = (float)VFB_DC1* ADC_PU_SCALE_FACTOR;

    return;
}

// ******************************************************************************
// POSITION ENCODER
// - Reads QEP
// - Angles are normalised to the the range 0 to 0.99999 (1.0)
// ******************************************************************************
inline void posEncoder(MOTOR_VARS * motor)
{
//	Uint16 q = motor->eQEP;
	volatile struct EQEP_REGS * v = motor->QepRegs;

	// ----------------------------------
	// motor->lsw = 0 ---> Alignment Routine
	// ----------------------------------
	if (motor->lsw == 0)
	{
		// during alignment, assign the current shaft position as initial position
//		v->QPOSCNT = 0;
//		v->QCLR.bit.IEL = 1;  // Reset position cnt for QEP
	    motor->lsw=1;
	} // end if (motor->lsw=0)

	// ******************************************************************************
	//    Detect calibration angle and call the QEP module
	// ******************************************************************************
	// for once the QEP index pulse is found, go to lsw=2
	if(motor->lsw==1)
	{
		if (v->QFLG.bit.IEL == 1)			// Check the index occurrence
		{
			//motor->qep.CalibratedAngle=v->QPOSILAT;
//			v->QPOSINIT = v->QPOSILAT; //new
//			v->QEPCTL.bit.IEI = IEI_RISING;   // new
		    //motor->qep.CalibratedAngle=0;
		    //w/o gearbox
            //motor->qep.CalibratedAngle=7680;
            //w/i gearbox
            motor->qep.CalibratedAngle= 7665;//7665;
            motor->SpeedRef = 0;
            lsw_flag = 1;
//            if(motor->rc.EqualFlag)
//            {
//
////
//            }

		}   // Keep the latched pos. at the first index
		if(lsw_flag)
		{
            if(lsw_cnt >= 10000)
            {
                motor->lsw=2;
            }
            else
            {
                lsw_cnt++;
            }
		}
	}

	if (motor->lsw!=0)
	{
		QEP_MACRO(v,motor->qep);
	}

	// Reverse the sense of position if needed - comment / uncomment accordingly
	if (motor->PosSenseReverse)
	{
		// Position Sense Reversal
		motor->ElecTheta = 1.0 - motor->qep.ElecTheta;
		motor->MechTheta = 1.0 - motor->qep.MechTheta;
	}
	else
	{
		// Position Sense as is
		motor->ElecTheta = motor->qep.ElecTheta;
		motor->MechTheta = motor->qep.MechTheta;
	}

	return;
}
#endif


// ****************************************************************************
// ****************************************************************************
//TODO  DMC Protection Against Over Current Protection
// ****************************************************************************
// ****************************************************************************

#define  TRIP4   3

void PwmTripConfig(volatile struct EPWM_REGS * PwmRegs, Uint16 TripNum)
{
	EALLOW;

	PwmRegs->DCTRIPSEL.bit.DCAHCOMPSEL = TripNum; //TripNum is input to DCAHCOMPSEL
	PwmRegs->TZDCSEL.bit.DCAEVT1       = TZ_DCAH_HI;
	PwmRegs->DCACTL.bit.EVT1SRCSEL     = DC_EVT1;
	PwmRegs->DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;
	PwmRegs->TZSEL.bit.DCAEVT1         = 1;
	PwmRegs->TZSEL.bit.CBC6    = 0x1;         // Emulator Stop
	PwmRegs->TZCTL.bit.TZA     = TZ_FORCE_LO; // TZA event force EPWMxA go low
	PwmRegs->TZCTL.bit.TZB     = TZ_FORCE_LO; // TZB event force EPWMxB go low
	PwmRegs->TZCLR.bit.DCAEVT1 = 1;           // Clear any spurious OV trip
	PwmRegs->TZCLR.bit.OST     = 1;           // clear any spurious OST set early

	EDIS;
}

//*****************************************************************************
void DMC1_Protection(void)
{
	// Configure GPIO used for Trip Mechanism

#if (MOTOR1_DRV == DRV8301)
	// Configure as Input - Motor 1 - OCTW - (active low), trip PWM based on this
	GPIO_SetupPinOptions(MOTOR1_OCTW_GPIO, GPIO_INPUT, GPIO_INVERT);
	GPIO_SetupPinMux(MOTOR1_OCTW_GPIO, 0, MOTOR1_OCTW_MUX);
#endif

	// Configure as Input - Motor 1 - FAULT - (active low), trip PWM based on this
	GPIO_SetupPinOptions(MOTOR1_FAULT_GPIO, GPIO_INPUT, GPIO_INVERT);
	GPIO_SetupPinMux(MOTOR1_FAULT_GPIO, 0, MOTOR1_FAULT_MUX);

	EALLOW;

	// Enable Mux 0  OR Mux 4 to generate TRIP4
	// Clear everything first
	EPwmXbarRegs.TRIP4MUX0TO15CFG.all  = 0x0000;    // clear all MUXes - MUX  0 to 15
	EPwmXbarRegs.TRIP4MUX16TO31CFG.all = 0x0000;    // clear all MUXes - MUX 16 to 31
	EPwmXbarRegs.TRIP4MUXENABLE.all    = 0x0000;    // Disable all the muxes first

	// Enable Muxes for ORed input of InputXbar1, InputXbar2
	InputXbarRegs.INPUT1SELECT = MOTOR1_FAULT_GPIO; // Select FAULT as INPUTXBAR1
	EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX1 = 1;     // Enable Mux for ored input of inputxbar1
	EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX1   = 1;     // Enable MUX1 to generate TRIP4

#if (MOTOR1_DRV == DRV8301)
	InputXbarRegs.INPUT2SELECT = MOTOR1_OCTW_GPIO;  // Select OCTW as INPUTXBAR2
	EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX3 = 1;     // Enable Mux for ored input of inputxbar2
	EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX3   = 1;     // Enable MUX3 to generate TRIP4
#endif

	EDIS;

	PwmTripConfig(motor1.PwmARegs, TRIP4);
	PwmTripConfig(motor1.PwmBRegs, TRIP4);
	PwmTripConfig(motor1.PwmCRegs, TRIP4);

	return;
}

// ****************************************************************************
// ****************************************************************************
// GENERAL PURPOSE UTILITY FUNCTIONS
// ****************************************************************************
// ****************************************************************************

// slew programmable ramper
_iq ramper(_iq in, _iq out, _iq rampDelta)
{
	_iq err;

	err = in - out;
	if (err > rampDelta)
		return(out + rampDelta);
  	else if (err < -rampDelta)
  		return(out - rampDelta);
    else
    	return(in);
}

//*****************************************************************************
// Ramp Controller for speed reference (Not currently used)
_iq ramper_speed(_iq in, _iq out, _iq rampDelta)
{
	_iq err;

	err = in - out;
	if (err > rampDelta)
	{
		if((out+rampDelta)>1.0)
			return(1.0);
		else
			return (out+rampDelta);
	}
  	else if (err < -rampDelta)
  	{
  		if(out-rampDelta<=0.0)
  			return(0.0);
  		else
  			return(out - rampDelta);
  	}
    else
    	return(in);
}

//*****************************************************************************
// Reference Position Generator for position loop
_iq refPosGen(_iq out)
{
	_iq in = posArray[ptr1];

	out = ramper(in, out, posSlewRate);

	if (in == out)
	if (++cntr1 > 1000)
	{
		cntr1 = 0;
		if (++ptr1 >= ptrMax)
			ptr1 = 0;
	}
	return (out);
}

//*****************************************************************************
//Toggle a GPIO pin
void GPIO_TogglePin(Uint16 pin)
{
	volatile Uint32 *gpioDataReg;
	Uint32 pinMask;

	gpioDataReg = (volatile Uint32 *)&GpioDataRegs + (pin/32)*GPY_DATA_OFFSET;
	pinMask = 1UL << (pin % 32);

	gpioDataReg[GPYTOGGLE] = pinMask;

	return;
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************



void main(void)
{


	// Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks

	// This function derived from the one found in F2837x_SysCtrl.c file
	InitSysCtrl1();

	// Waiting for enable flag set
	while (EnableFlag == FALSE)
	{
	  BackTicker++;
	}

	// Clear all interrupts and initialize PIE vector table:

	// Disable CPU interrupts
	DINT;


	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags
	// are cleared.
	// This function is found in the F28M3Xx_PieCtrl.c file.
	InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;
	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in F28M3Xx_DefaultIsr.c.
	// This function is found in F28M3Xx_PieVect.c.
	InitPieVectTable();

	// Configure a temp output pin for flagging (GPIO78)
	GPIO_SetupPinOptions(TEMP_GPIO, GPIO_OUTPUT, GPIO_ASYNC); // not use
	GPIO_SetupPinMux(TEMP_GPIO, 0, TEMP_MUX); // not use

    GPIO_SetupPinOptions(BLUE_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(BLUE_LED_GPIO, GPIO_MUX_CPU1, BLUE_LED_MUX);

//    for (;;)
//    {
//    	GPIO_TogglePin(BLUE_LED_GPIO);
//    	DELAY_US(500000);
//    }

// Timing sync for background loops
// Timer period definitions found in device specific PeripheralHeaderIncludes.h
	CpuTimer0Regs.PRD.all =  10000;		// A tasks
	CpuTimer1Regs.PRD.all =  20000;		// B tasks
	CpuTimer2Regs.PRD.all =  30000;	    // C tasks

// Tasks State-machine init
	Alpha_State_Ptr = &A0;
	A_Task_Ptr = &A1;
	B_Task_Ptr = &B1;
	C_Task_Ptr = &C1;

// ****************************************************************************
// ****************************************************************************
// Set up peripheral assignments for motor control
// ****************************************************************************
// ****************************************************************************
	motor1.PwmARegs = &EPwm1Regs;    // set up EPWM for motor 1 phase A
	motor1.PwmBRegs = &EPwm2Regs;    // set up EPWM for motor 1 phase B
	motor1.PwmCRegs = &EPwm3Regs;    // set up EPWM for motor 1 phase C
	motor1.QepRegs  = &EQep1Regs;    // set up QEP # for motor 1
	motor1.SpiRegs  = &SpiaRegs;     // set up SPI for motor 1
	motor1.drvScsPin = MOTOR1_SCS_GPIO; // pin for SPI-drv1 chip select

// ****************************************************************************
// ****************************************************************************
// Initialize EPWM modules for inverter PWM generation
// ****************************************************************************
// ****************************************************************************

	EALLOW;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

	// *****************************************
	// Inverter PWM configuration for motor 1
	// ****************************************
	/* Deadband is set externally on DRV830x chip
	 */
	PWM_1ch_UpDwnCnt_CNF_noDB(motor1.PwmARegs, INV_PWM_TICKS);
	PWM_1ch_UpDwnCnt_CNF_noDB(motor1.PwmBRegs, INV_PWM_TICKS);
	PWM_1ch_UpDwnCnt_CNF_noDB(motor1.PwmCRegs, INV_PWM_TICKS);

	// configure Epwms 2 and 3 as slaves
	(motor1.PwmBRegs)->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	(motor1.PwmBRegs)->TBCTL.bit.PHSEN    = TB_ENABLE;
	(motor1.PwmBRegs)->TBPHS.bit.TBPHS    = 2;
	(motor1.PwmBRegs)->TBCTL.bit.PHSDIR   = TB_UP;

	(motor1.PwmCRegs)->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	(motor1.PwmCRegs)->TBCTL.bit.PHSEN    = TB_ENABLE;
	(motor1.PwmCRegs)->TBPHS.bit.TBPHS    = 2;
	(motor1.PwmCRegs)->TBCTL.bit.PHSDIR   = TB_UP;

	InitMotor1EPwmGpio();  // Set up GPIOs for EPWMA of 1,2,3

//---------------------------------------------------------------------------------------

	// Setting up link from EPWM to ADC (EPwm1 is chosen)
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD; // Select SOC from counter at ctr = PRD
	EPwm1Regs.ETPS.bit.SOCAPRD  = ET_1ST;     // Generate pulse on 1st even
	EPwm1Regs.ETSEL.bit.SOCAEN  = 1;          // Enable SOC on A group



// ****************************************************************************
// ****************************************************************************
//TODO ADC Configuration
// ****************************************************************************
// ****************************************************************************
    //Configure the ADC and power it up
	ConfigureADC();

	//Select the channels to convert and end of conversion flag

	EALLOW;

    //Analog signals - Motor 1
    //Ia   ADC C2     SOC0
    //Ib   ADC B2     SOC0
    //Ic   ADC A2     SCO2
	//Va   ADC (A)14  SOC4
    //Vb   ADC C3     SOC3
    //Vc   ADC B3     SOC2
    //Vdc  ADC A3     SOC6

	// On piccolo 133ns for ACQPS
	// hencce ACQPS on soprano is 133/5~30

	// Configure SOCx on ADCs A , B and C (D not used)

	// Motor 1: Ia  @ C2
	// ********************************
	AdccRegs.ADCSOC0CTL.bit.CHSEL     =  2;                    // SOC0 will convert pin C2
	AdccRegs.ADCSOC0CTL.bit.ACQPS     = 30;                    // sample window in SYSCLK cycles
	AdccRegs.ADCSOC0CTL.bit.TRIGSEL   = ADCTRIG5_EPWM1SOCA;    // trigger on ePWM1 SOCA
	// Configure the post processing block (PPB) to eliminate subtraction related calculation
	AdccRegs.ADCPPB1CONFIG.bit.CONFIG = 0;                     // PPB is associated with SOC0
	AdccRegs.ADCPPB1OFFCAL.bit.OFFCAL = 0;                     // Write zero to this for now till offset ISR is run

	// Motor 1: Ib  @ B2
	// ********************************
	AdcbRegs.ADCSOC0CTL.bit.CHSEL     =  2;                    // SOC0 will convert pin B2
	AdcbRegs.ADCSOC0CTL.bit.ACQPS     = 30;                    // sample window in SYSCLK cycles
	AdcbRegs.ADCSOC0CTL.bit.TRIGSEL   = ADCTRIG5_EPWM1SOCA;    // trigger on ePWM1 SOCA
	// Configure the post processing block (PPB) to eliminate subtraction related calculation
	AdcbRegs.ADCPPB1CONFIG.bit.CONFIG = 0;                     // PPB is associated with SOC0
	AdcbRegs.ADCPPB1OFFCAL.bit.OFFCAL = 0;                     // Write zero to this for now till offset ISR is run

	// Motor 1: Ic  @ A2
	// ********************************
	AdcaRegs.ADCSOC2CTL.bit.CHSEL     =  2;                    // SOC2 will convert pin A1
	AdcaRegs.ADCSOC2CTL.bit.ACQPS     = 30;                    // sample window in SYSCLK cycles
	AdcaRegs.ADCSOC2CTL.bit.TRIGSEL   = ADCTRIG5_EPWM1SOCA;    // trigger on ePWM1 SOCA
	// Configure the post processing block (PPB) to eliminate subtraction related calculation
	AdcaRegs.ADCPPB1CONFIG.bit.CONFIG = 2;                     // PPB is associated with SOC2
	AdcaRegs.ADCPPB1OFFCAL.bit.OFFCAL = 0;                     // Write zero to this for now till offset ISR is run

	// Motor 1: Va  @ (A)14
	// ********************************
	AdcaRegs.ADCSOC4CTL.bit.CHSEL     = 14;                    // SOC4 will convert pin (A)14
	AdcaRegs.ADCSOC4CTL.bit.ACQPS     = 30;                    // sample window in SYSCLK cycles
	AdcaRegs.ADCSOC4CTL.bit.TRIGSEL   = ADCTRIG5_EPWM1SOCA;    // trigger on ePWM1 SOCA

	// Motor 1: Vb  @ C3
	// ********************************
	AdccRegs.ADCSOC3CTL.bit.CHSEL     =  3;                    // SOC3 will convert pin C3
	AdccRegs.ADCSOC3CTL.bit.ACQPS     = 30;                    // sample window in SYSCLK cycles
	AdccRegs.ADCSOC3CTL.bit.TRIGSEL   = ADCTRIG5_EPWM1SOCA;    // trigger on ePWM1 SOCA

	// Motor 1: Vc  @ B3
	// ********************************
	AdcbRegs.ADCSOC2CTL.bit.CHSEL     =  3;                    // SOC2 will convert pin B3
	AdcbRegs.ADCSOC2CTL.bit.ACQPS     = 30;                    // sample window in SYSCLK cycles
	AdcbRegs.ADCSOC2CTL.bit.TRIGSEL   = ADCTRIG5_EPWM1SOCA;    // trigger on ePWM1 SOCA

	// Motor 1: Vdc  @ A3
	// ********************************
	AdcaRegs.ADCSOC6CTL.bit.CHSEL     =  3;                    // SOC6 will convert pin A3
	AdcaRegs.ADCSOC6CTL.bit.ACQPS     = 30;                    // sample window in SYSCLK cycles
	AdcaRegs.ADCSOC6CTL.bit.TRIGSEL   = ADCTRIG5_EPWM1SOCA;    // trigger on ePWM1 SOCA

// ****************************************************************************
// ****************************************************************************
//TODO ISR Mapping
// ****************************************************************************
// ****************************************************************************
	// ADC A EOC of SOC6 is used to trigger Motor control Interrupt
	AdcaRegs.ADCINTSEL1N2.bit.INT1SEL  = 6;
	AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1;
	AdcaRegs.ADCINTSEL1N2.bit.INT1E    = 1;

	PieVectTable.ADCA1_INT         = &MotorControlISR;
	PieCtrlRegs.PIEIER1.bit.INTx1  = 1;  // Enable ADCA1INT in PIE group 1

	IER |= M_INT1;                       // Enable group 1 interrupts

	// SETUP DAC-C (DACs A, B and C are already used up)


	EDIS;

// ****************************************************************************
// ****************************************************************************
// Initialize QEP module
// ****************************************************************************
// ****************************************************************************
	InitMotor1EQepGpio();               // Init motor 1 QEP GPIOs

// ****************************************************************************
// ****************************************************************************
// Initialize PWMDAC module
// ****************************************************************************
// ****************************************************************************
    pwmdac1.PeriodMax = 500;   // @200Mhz: 4500->20kHz, 3000-> 30kHz, 1500->60kHz, min: 500
    pwmdac1.PwmDacInPointer0 = &PwmDacCh1;
    pwmdac1.PwmDacInPointer1 = &PwmDacCh2;
    pwmdac1.PwmDacInPointer2 = &PwmDacCh3;
    pwmdac1.PwmDacInPointer3 = &PwmDacCh4;

    PWMDAC_INIT_MACRO(pwmdac1)
    InitMotor1EPwmDACGpio();  // Set up GPIOs for EPWMA of 7,8

// ****************************************************************************
// ****************************************************************************
// Initialize DAC module
// ****************************************************************************
// ****************************************************************************

    configureDAC(DACA);
    configureDAC(DACB);
//    configureDAC(DACC);

// ****************************************************************************
// ****************************************************************************
// Initialize SPI module for communication with DRV830x
// ****************************************************************************
// ****************************************************************************
	InitMotor1SpiGpio();                    // Init motor 1 SPI GPIOs
	InitSpiDacGpio();
    SPIDAC_setup();                         // Set SPIDAC(SPIB) with registers
	InitSpiRegs_DRV830x(motor1.SpiRegs);    // Init SPI regs
    #if (MOTOR1_DRV == DRV8301)
		InitDRV8301Regs(&motor1);           // Init DRV regs' mirror variables
    #else
		InitDRV8305Regs(&motor1);
    #endif

// ****************************************************************************
// ****************************************************************************
// Initialise USER GPIOs
// ****************************************************************************
// ****************************************************************************

    GPIO_SetupPinOptions(GPIO25, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(GPIO25, 0, GPIO25_MUX);

// ****************************************************************************
// ****************************************************************************
// Initialise DRV830x interface GPIOs
// ****************************************************************************
// ****************************************************************************
	InitMotor1_DRV_Gpio();                   // DRV init for motor 1

// ****************************************************************************
// ****************************************************************************
// Initialise DRV830x
// ****************************************************************************
// ****************************************************************************
	GPIO_WritePin(MOTOR1_EN_GATE_GPIO, 1);  // Enable DRV
	DELAY_US(50000);		                // delay to allow DRV830x supplies to ramp up

#if (MOTOR1_DRV == DRV8301)
	InitDRV8301(&motor1);
	while (motor1.drv8301.DRV_fault) ;  // hang on if drv init is faulty
#else
	InitDRV8305(&motor1);
	//while (motor1.drv8305.DRV_fault) ;  // hang on if drv init is faulty
#endif

// ****************************************************************************
// ****************************************************************************
// Paramaeter Initialisation
// ****************************************************************************
// ****************************************************************************
	// Initialize the SMOPOS constant module
	motor1.smo_const.Rs = RS;
	motor1.smo_const.Ls = LS;
	motor1.smo_const.Ib = BASE_CURRENT;
	motor1.smo_const.Vb = BASE_VOLTAGE;
	motor1.smo_const.Ts = motor1.T;
    SMO_CONST_MACRO(motor1.smo_const)

	// Initialize the SMOPOS module
    motor1.smo.Fsmopos = _IQ(motor1.smo_const.Fsmopos);
    motor1.smo.Gsmopos = _IQ(motor1.smo_const.Gsmopos);
    motor1.smo.Kslide = _IQ(0.2);
    motor1.smo.Kslf = _IQ(0.15);

	// Initialize the SPEED_EST module SMOPOS based speed calculation
    motor1.speed1.K1 = _IQ21(1/(BASE_FREQ*motor1.T));
    motor1.speed1.K2 = _IQ(1/(1+motor1.T*2*PI*5));  // Low-pass cut-off frequency
    motor1.speed1.K3 = _IQ(1)-motor1.speed1.K2;
    motor1.speed1.BaseRpm = 120*(BASE_FREQ/POLES);

	// Init QEP parameters
    motor1.qep.LineEncoder = 4096; // these are the number of slots in the QEP encoder
    motor1.qep.MechScaler  = _IQ30(0.25/motor1.qep.LineEncoder);
    motor1.qep.PolePairs   = POLES/2;
    motor1.qep.CalibratedAngle = 7410;
    QEP_INIT_MACRO(motor1.QepRegs,motor1.qep)
    (motor1.QepRegs)->QEPCTL.bit.IEI = 0;        // disable POSCNT=POSINIT @ Index

    // Initialize the Speed module for speed calculation from QEP
    motor1.speed.K1 = _IQ21(1/(BASE_FREQ*motor1.T));
    motor1.speed.K2 = _IQ(1/(1+motor1.T*2*PI*50));      // Low-pass cut-off frequency
    motor1.speed.K3 = _IQ(1)-motor1.speed.K2;
    motor1.speed.BaseRpm = 120*(BASE_FREQ/POLES);

    // Initialize the RAMPGEN module
    motor1.rg.StepAngleMax = _IQ(BASE_FREQ*motor1.T);
#if BUILDLEVEL == LEVEL3
    rg_CurrentCmd_Generate_Sin.StepAngleMax = _IQ(BASE_FREQ*motor1.T);
#endif
#if BUILDLEVEL == LEVEL4
    rg_SpeedCmd_Generate_Sin.StepAngleMax = _IQ(BASE_FREQ*motor1.T);
    // Filter Initialize

    Estimated_Acc.BW = 2 * PI * 5;
    Estimated_Acc.T = TS;

    RLS_Inertia.BW = 2 * PI * 1000;
    RLS_Inertia.T = TS;
    RLS_Inertia.u = J_INI;
    RLS_Inertia.u1 = J_INI;
    RLS_Inertia.y1 = J_INI;

    Iq_FBK.BW = 2 * PI * 500;
    Iq_FBK.T = TS;

    Id_FBK.BW = 2 * PI * 500;
    Id_FBK.T = TS;

    Kalman_e.BW = 2 * PI * 30;
    Kalman_e.T = TS;

    Iq_test_Kt.BW = 2 * PI * 1;
    Iq_test_Kt.T = TS;
#endif

    // Initialize the PID module for Speed Estimation
    motor1.speed_est.param.Kd = 3 * Speed_Est_BW * J;
    motor1.speed_est.param.Kp = 3 * Speed_Est_BW * Speed_Est_BW * J;
    motor1.speed_est.param.Ki = Speed_Est_BW * Speed_Est_BW * Speed_Est_BW * J;
    motor1.speed_est.param.Kt = KT;
    motor1.speed_est.param.T_est = TS;
    motor1.speed_est.param.f_est = FS;
    motor1.speed_est.param.J_est = J;
    motor1.speed_est.param.divJ_est = DIV_J;
    motor1.speed_est.param.BaseRpm = 60U*(BASE_FREQ);


    // Initialize the PI module for position
	motor1.pi_pos.Kp = _IQ(1.0);            //_IQ(10.0);
	motor1.pi_pos.Ki = _IQ(0.001);          //_IQ(motor1.T*SpeedLoopPrescaler/0.3);
	motor1.pi_pos.Umax = _IQ(1.0);
	motor1.pi_pos.Umin = _IQ(-1.0);

//    // Initialize the PID module for position (alternative option for eval)
//    motor1.pid_pos.Ref = 0;
//    motor1.pid_pos.Fdb = 0;
//    motor1.pid_pos.OutMin = _IQ(-0.5);
//    motor1.pid_pos.OutMax = _IQ(0.5);
//    motor1.pid_pos.Out = 0;
//
//    motor1.pid_pos.Kp = 1.0;
//    motor1.pid_pos.Ki = 0;
//    motor1.pid_pos.Kd = 0;
//    motor1.pid_pos.Kc = 0.9;
//
//    motor1.pid_pos.Up1 = 0;
//    motor1.pid_pos.Up  = 0;
//    motor1.pid_pos.Ui  = 0;
//    motor1.pid_pos.Ud  = 0;
//    motor1.pid_pos.SatErr    = 0;
//    motor1.pid_pos.OutPreSat = 0;

	// Initialize the PID module for speed
#if (BUILDLEVEL==LEVEL5)
//	motor1.pid_spd.param.Kp=_IQ(2.5);
//	motor1.pid_spd.param.Ki=_IQ(0.0001);
//	motor1.pid_spd.param.Kd=_IQ(0.0);
//	motor1.pid_spd.param.Kr=_IQ(1.0);
//	motor1.pid_spd.param.Umax=_IQ(0.9);
//	motor1.pid_spd.param.Umin=_IQ(-0.9);
	motor1.pid_spd.param.Kp=_IQ(1.0);
	motor1.pid_spd.param.Ki=_IQ(0.001);
	motor1.pid_spd.param.Kd=_IQ(0.0);
	motor1.pid_spd.param.Kr=_IQ(1.0);
	motor1.pid_spd.param.Umax=_IQ(0.95);
	motor1.pid_spd.param.Umin=_IQ(-0.95);

#else
//	motor1.pid_spd.param.Kp   = _IQ(2.0);   //_IQ(0.0464)
	motor1.pid_spd.param.Kp   = _IQ(0.05);
	motor1.pid_spd.param.Ki   = _IQ(0.01);
	motor1.pid_spd.param.Kd   = _IQ(0.0);
	motor1.pid_spd.param.Kr   = _IQ(1.0);
	motor1.pid_spd.param.Umax = _IQ(0.95);
	motor1.pid_spd.param.Umin = _IQ(-0.95);
#endif

//	//Initialize the PI Speed Controller
    motor1.pi_spd.param.Kp       = _IQ(3.0);
	motor1.pi_spd.param.Ki       = _IQ(1.0);
//	motor1.pi_spd.param.Kp       = _IQ(J*5*2*PI*BASE_FREQ/BASE_CURRENT*2*PI);
//	motor1.pi_spd.param.Ki       = _IQ(BM*5*2*PI*BASE_FREQ/BASE_CURRENT*2*PI);
//    motor1.pi_spd.param.Kp       = _IQ((2*5*2*PI*J-BM)*BASE_FREQ/BASE_CURRENT*2*PI);
//    motor1.pi_spd.param.Ki       = _IQ((5*2*PI*5*2*PI*J)*BASE_FREQ/BASE_CURRENT*2*PI);
	motor1.pi_spd.param.Kr       = _IQ(1.0);
	motor1.pi_spd.param.Umax     = _IQ(0.95);
    motor1.pi_spd.param.Umin     = _IQ(-0.95);
    motor1.pi_spd.param.T        = _IQ(0.001);
    motor1.pi_spd.param.divT     = _IQ(1000);
    motor1.pi_spd.param.Kt       = _IQ(0.169);




	// Init PI module for ID loop
	motor1.pi_id.Kp   = _IQ(2);
	motor1.pi_id.Ki   = _IQ(motor1.T/0.04);
	motor1.pi_id.Umax = _IQ(0.5);
	motor1.pi_id.Umin = _IQ(-0.5);

	// Init PI module for IQ loop
	motor1.pi_iq.Kp   = _IQ(5/2);
	motor1.pi_iq.Ki   = _IQ(motor1.T/0.04);
	motor1.pi_iq.Umax = _IQ(0.7);
	motor1.pi_iq.Umin = _IQ(-0.7);

	// Set mock REFERENCES for Speed and Iq loops
	motor1.SpeedRef = 0.007;

	motor1.IqRef = _IQ(0.1);

	// Init FLAGS
	motor1.RunMotor = 1;

//  Note that the vectorial sum of d-q PI outputs should be less than 1.0 which
//  refers to maximum duty cycle for SVGEN. Another duty cycle limiting factor
//	is current sense through shunt resistors which depends on hardware/software
//  implementation. Depending on the application requirements 3,2 or a single
//	shunt resistor can be used for current waveform reconstruction. The higher
//  number of shunt resistors allow the higher duty cycle operation and better
//	dc bus utilization. The users should adjust the PI saturation levels
//  carefully during open loop tests (i.e pi_id.Umax, pi_iq.Umax and Umins) as
//	in project manuals. Violation of this procedure yields distorted  current
// waveforms and unstable closed loop operations which may damage the inverter.

// ****************************************************
// Initialize Matrix for Kalman Filter and RLS
// ****************************************************

	Kalman_Ini_3X3(&Kalman3X3_Handler);
	Kalman_Ini_2X2(&Kalman2X2_Handler);
	RLS_Ini(&RLS_Handler);
	//mpy_SP_RMxRM(tt3, tt1, tt2, 3, 3, 3);
//	Matrix_Dot_Product(tt2, 1.5, tt3 ,9);
//	Matrix_Add(tt2, Kalman3X3_Handler.Zero, tt1, 9);
	//memcpy_fast(fp1, fp2, 9);
//	Matrix_Generate(&test1,2,2);
//	Matrix_Generate(&test2,2,2);
//	Matrix_Generate(&test3,2,2);
//	int i=0,j=0;
//	for(i=0;i<2;i++)
//	{
//	    for(j=0;j<2;j++)
//	        test1.data[i][j]=1;
//	}
//    for(i=0;i<2;i++)
//    {
//        for(j=0;j<2;j++)
//            test2.data[i][j]=2;
//    }
//    Matrix_Product(&test1,&test2,&test3);
//
//    for(i=0;i<2;i++)
//    {
//        for(j=0;j<2;j++)
//            result[2*i+j]=test3.data[i][j];
//    }


// ****************************************************
// Initialize DATALOG module
// ****************************************************
	DLOG_4CH_F_init(&dlog_4ch1);
	dlog_4ch1.input_ptr1 = &DlogCh1;	//data value
	dlog_4ch1.input_ptr2 = &DlogCh2;
	dlog_4ch1.input_ptr3 = &DlogCh3;
	dlog_4ch1.input_ptr4 = &DlogCh4;
	dlog_4ch1.output_ptr1 = &DBUFF_4CH1[0];
	dlog_4ch1.output_ptr2 = &DBUFF_4CH2[0];
	dlog_4ch1.output_ptr3 = &DBUFF_4CH3[0];
	dlog_4ch1.output_ptr4 = &DBUFF_4CH4[0];
	dlog_4ch1.size = 200;
	dlog_4ch1.pre_scalar = 5;
	dlog_4ch1.trig_value = 0.01;
	dlog_4ch1.status = 2;



// ****************************************************************************
// ****************************************************************************
// Call DMC Protection function
// ****************************************************************************
// ****************************************************************************
	DMC1_Protection();

// TODO
// ****************************************************************************
// ****************************************************************************
// Feedbacks OFFSET Calibration Routine
// ****************************************************************************
// ****************************************************************************
#if (MOTOR1_DRV == DRV8301)
	GPIO_WritePin(MOTOR1_DC_CAL_GPIO,  0);  // Set DC-CAL to 0 to enable current amplifiers
#endif

	DELAY_US(5);		                    // delay to allow DRV830x amplifiers to settle

	EALLOW;
	  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;

	motor1.offset_shntA = 0;
	motor1.offset_shntB = 0;
	motor1.offset_shntC = 0;

	for (OffsetCalCounter=0; OffsetCalCounter<20000; )
	{
		if(EPwm1Regs.ETFLG.bit.SOCA==1)
		{
			if(OffsetCalCounter>1000)
			{
				motor1.offset_shntA = K1*motor1.offset_shntA + K2*(IFB_A1)*ADC_PU_SCALE_FACTOR; 	//Mtr1 : Phase A offset
				motor1.offset_shntB = K1*motor1.offset_shntB + K2*(IFB_B1)*ADC_PU_SCALE_FACTOR; 	//Mtr1 : Phase B offset
				motor1.offset_shntC = K1*motor1.offset_shntC + K2*(IFB_C1)*ADC_PU_SCALE_FACTOR; 	//Mtr1 : Phase C offset
			}
			EPwm1Regs.ETCLR.bit.SOCA=1;
			OffsetCalCounter++;
		}
	}

	// ********************************************
	// Init OFFSET regs with identified values
	// ********************************************
	EALLOW;

	AdccRegs.ADCPPB1OFFREF = motor1.offset_shntA*4096.0;      // set shunt Iu1 offset
	AdcbRegs.ADCPPB1OFFREF = motor1.offset_shntB*4096.0;      // set shunt Iv1 offset
	AdcaRegs.ADCPPB3OFFREF = motor1.offset_shntC*4096.0;      // set shunt Iw1 offset

	EDIS;

// ****************************************************************************
// ****************************************************************************
//TODO Enable Interrupts
// ****************************************************************************
// ****************************************************************************
	EALLOW;
	EINT;          // Enable Global interrupt INTM
	ERTM;          // Enable Global realtime interrupt DBGM
	EDIS;

// ***************************************************************************
//  Initialisations COMPLETE
//  - IDLE loop. Just loop forever
// ***************************************************************************
	for(;;)  //infinite loop
	{
		// State machine entry & exit point
		//===========================================================
		(*Alpha_State_Ptr)();	// jump to an Alpha state (A0,B0,...)
		//===========================================================
	}
} //END MAIN CODE

/******************************************************************************
 * ****************************************************************************
 * ****************************************************************************
 * ****************************************************************************
 */

//=================================================================================
//	STATE-MACHINE SEQUENCING AND SYNCRONIZATION FOR SLOW BACKGROUND TASKS
//=================================================================================

//--------------------------------- FRAMEWORK -------------------------------------
void A0(void)
{
	// loop rate synchronizer for A-tasks
	if(CpuTimer0Regs.TCR.bit.TIF == 1)
	{
		CpuTimer0Regs.TCR.bit.TIF = 1;	// clear flag

		//-----------------------------------------------------------
		(*A_Task_Ptr)();		// jump to an A Task (A1,A2,A3,...)
		//-----------------------------------------------------------

		VTimer0[0]++;			// virtual timer 0, instance 0 (spare)
		SerialCommsTimer++;
	}

	Alpha_State_Ptr = &B0;		// Comment out to allow only A tasks
}

void B0(void)
{
	// loop rate synchronizer for B-tasks
	if(CpuTimer1Regs.TCR.bit.TIF == 1)
	{
		CpuTimer1Regs.TCR.bit.TIF = 1;				// clear flag

		//-----------------------------------------------------------
		(*B_Task_Ptr)();		// jump to a B Task (B1,B2,B3,...)
		//-----------------------------------------------------------
		VTimer1[0]++;			// virtual timer 1, instance 0 (spare)
	}

	Alpha_State_Ptr = &C0;		// Allow C state tasks
}

void C0(void)
{
	// loop rate synchronizer for C-tasks
	if(CpuTimer2Regs.TCR.bit.TIF == 1)
	{
		CpuTimer2Regs.TCR.bit.TIF = 1;				// clear flag

		//-----------------------------------------------------------
		(*C_Task_Ptr)();		// jump to a C Task (C1,C2,C3,...)
		//-----------------------------------------------------------
		VTimer2[0]++;			//virtual timer 2, instance 0 (spare)
	}

	Alpha_State_Ptr = &A0;	// Back to State A0
}


//=================================================================================
//	A - TASKS (executed in every 50 usec)
//=================================================================================
//--------------------------------------------------------
void A1(void) // SPARE (not used)
//--------------------------------------------------------
{

	// *******************************************************
	// Motor 1 -- DRV830x protections
	// *******************************************************
	// Check for PWM trip due to over current

	if((motor1.PwmARegs)->TZFLG.bit.OST == 0x1)
	{
	    motor1.TripFlagDMC = 1;                  // Trip on DMC (fault trip )
	    GPIO_WritePin(MOTOR1_EN_GATE_GPIO, 0);   // de-assert the DRV830x EN_GATE pin
	}

	// If clear cmd received, reset PWM trip
	if (motor1.clearTripFlagDMC)
	{
		GPIO_WritePin(MOTOR1_EN_GATE_GPIO, 1);  // assert the DRV830x EN_GATE pin
		DELAY_US(50000);		                // DRV830x settling time

		motor1.TripFlagDMC = 0;
		motor1.clearTripFlagDMC = 0;

		// clear EPWM trip flags
		EALLOW;
		  (motor1.PwmARegs)->TZCLR.bit.OST = 1;
		  (motor1.PwmBRegs)->TZCLR.bit.OST = 1;
		  (motor1.PwmCRegs)->TZCLR.bit.OST = 1;
		EDIS;
	}

	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A2
	A_Task_Ptr = &A2;
	//-------------------
}

//-----------------------------------------------------------------
void A2(void) // SPARE (not used)
//-----------------------------------------------------------------
{

	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A3
	A_Task_Ptr = &A3;
	//-------------------
}

//-----------------------------------------
void A3(void) // SPARE (not used)
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A1;
	//-----------------
}



//=================================================================================
//	B - TASKS (executed in every 100 usec)
//=================================================================================

//----------------------------------- USER ----------------------------------------

//----------------------------------------
void B1(void) // SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B2
	B_Task_Ptr = &B2;
	//-----------------
}

//----------------------------------------
void B2(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B3
	B_Task_Ptr = &B3;
	//-----------------
}

//----------------------------------------
void B3(void) //  SPARE
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B1
	B_Task_Ptr = &B1;
	//-----------------
}


//=================================================================================
//	C - TASKS (executed in every 150 usec)
//=================================================================================

//--------------------------------- USER ------------------------------------------

//----------------------------------------
void C1(void)
//----------------------------------------
{
#if MOTOR1_DRV == DRV8305
Uint16 tmp1, tmp2;
#endif

    GPIO_TogglePin(TEMP_GPIO);    // general purpose flag

	if (motor1.newCmdDRV)
	{
#if (MOTOR1_DRV == DRV8301)
		//write to DRV8301 control register 1, returns status register 1
		motor1.drv8301.stat_reg1.all = DRV8301_SPI_Write(&motor1, CNTRL_REG_1_ADDR);

		//write to DRV8301 control register 2, returns status register 1
		motor1.drv8301.stat_reg1.all = DRV8301_SPI_Write(&motor1, CNTRL_REG_2_ADDR);
#else
		for (tmp1=5; tmp1<= 0xc; tmp1++)
		{
			if (tmp1 != 8)
				tmp2 = DRV8305_SPI_Write(&motor1, tmp1);                //write to DRV8305 control reg @ address 'tmp1';
		}
#endif
		motor1.newCmdDRV = 0;
	}

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C2
	C_Task_Ptr = &C2;
	//-----------------

}

//----------------------------------------
void C2(void)
//----------------------------------------
{
#if (MOTOR1_DRV == DRV8301)
	DRV8301_diagnostics(&motor1);
#else
	DRV8305_diagnostics(&motor1);
#endif

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C3
	C_Task_Ptr = &C3;
	//-----------------
}


//-----------------------------------------
void C3(void) //  SPARE
//-----------------------------------------
{
	static Uint16 i;

	// LED blinking code
	if (++i >= LedCnt)
	{
		i = 0;
		GPIO_TogglePin(BLUE_LED_GPIO);
	}

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C1
	C_Task_Ptr = &C1;
	//-----------------
}

#if BUILDLEVEL == LEVEL1
// ****************************************************************************
// ****************************************************************************
//TODO Motor Control ISR - Build level 1
//	  Checks target independent modules, duty cycle waveforms and PWM update
//	  Keep the motors disconnected at this level
// ****************************************************************************
// ****************************************************************************
inline void BuildLevel1(MOTOR_VARS * motor)
{
// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
	motor->rc.TargetValue = motor->SpeedRef;
	RC_MACRO(motor->rc)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
	motor->rg.Freq = motor->rc.SetpointValue;
	RG_MACRO(motor->rg)

// ------------------------------------------------------------------------------
//  Connect inputs of the INV_PARK module and call the inverse park trans. macro
//	There are two option for trigonometric functions:
//  IQ sin/cos look-up table provides 512 discrete sin and cos points in Q30 format
//  IQsin/cos PU functions interpolate the data in the lookup table yielding higher resolution.
// ------------------------------------------------------------------------------
	motor->park.Angle   = motor->rg.Out;
	motor->park.Sine    = __sinpuf32(motor->park.Angle);
	motor->park.Cosine  = __cospuf32(motor->park.Angle);

	motor->ipark.Ds     = motor->VdTesting;
	motor->ipark.Qs     = motor->VqTesting;
	motor->ipark.Sine   = motor->park.Sine;
	motor->ipark.Cosine = motor->park.Cosine;
	IPARK_MACRO(motor->ipark)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
	motor->svgen.Ualpha = motor->ipark.Alpha;
	motor->svgen.Ubeta  = motor->ipark.Beta;
	SVGENDQ_MACRO(motor->svgen)

// ------------------------------------------------------------------------------
//  Computed Duty and Write to CMPA register
// ------------------------------------------------------------------------------
	(motor->PwmARegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Ta)+INV_PWM_HALF_TBPRD;
	(motor->PwmBRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tb)+INV_PWM_HALF_TBPRD;
	(motor->PwmCRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tc)+INV_PWM_HALF_TBPRD;

// ------------------------------------------------------------------------------
//  Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
	DlogCh1 = motor->rg.Out;
	DlogCh2 = motor->svgen.Ta;
	DlogCh3 = motor->svgen.Tb;
	DlogCh4 = motor->svgen.Tc;

//------------------------------------------------------------------------------
// Variable display on PWMDAC - available
//------------------------------------------------------------------------------
    PwmDacCh1 = _IQtoQ15(motor->rg.Out);   // Launchpad pin DAC1
    PwmDacCh2 = _IQtoQ15(motor->svgen.Ta); // Launchpad pin DAC2
	PwmDacCh3 = _IQtoQ15(motor->svgen.Tb); // Launchpad pin DAC3
    PwmDacCh4 = _IQtoQ15(motor->svgen.Tc); // Launchpad pin DAC4

//------------------------------------------------------------------------------
// Variable display on DAC - DAC-C not available
//------------------------------------------------------------------------------
//    dacAval = (Uint16) _IQtoQ12(motor->rg.Out);
//    dacBval = (Uint16) _IQtoQ12(motor->svgen.Ta);
    dacAval = (Uint16) _IQtoQ11(motor->currentAs + _IQ(1));
    dacBval = (Uint16) _IQtoQ11(motor->currentBs + _IQ(1));

	return;
}
#endif


#if BUILDLEVEL == LEVEL2
// ****************************************************************************
// ****************************************************************************
//TODO Motor Control ISR - - Build level 2
//	  Level 2 verifies
//	     - current sense schems
//         - analog-to-digital conversion - shunt current
//       - clarke/park transformations (CLARKE/PARK)
//       - Position sensor interface
//         - speed estimation
// ****************************************************************************
// ****************************************************************************
inline void BuildLevel2(MOTOR_VARS * motor)
{

	// ------------------------------------------------------------------------------
	// Alignment Routine: this routine aligns the motor to zero electrical angle
	// and in case of QEP also finds the index location and initializes the angle
	// w.r.t. the index location
	// ------------------------------------------------------------------------------
	if(!motor->RunMotor)
		motor->lsw = 0;
	else if (motor->lsw == 0)
	{
		// for restarting from (motor->RunMotor = 0)
		motor->rc.TargetValue =  motor->rc.SetpointValue = 0;

		motor->lsw = 1;   // for QEP, spin the motor to find the index pulse
	} // end else if (lsw=0)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
	if(motor->lsw==0)motor->rc.TargetValue = 0;
	else motor->rc.TargetValue = motor->SpeedRef;
	RC_MACRO(motor->rc)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    motor->rg.Freq = motor->rc.SetpointValue;
	RG_MACRO(motor->rg)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
	motor->clarke.As = motor->currentAs; // Phase A curr.
	motor->clarke.Bs = motor->currentBs; // Phase B curr.
	CLARKE_MACRO(motor->clarke)

// ------------------------------------------------------------------------------
//  Connect inputs of the SPEED_FR module and call the speed calculation macro
// ------------------------------------------------------------------------------
    motor->speed.ElecTheta = motor->ElecTheta;
	SPEED_FR_MACRO(motor->speed)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
	motor->park.Alpha  = motor->clarke.Alpha;
	motor->park.Beta   = motor->clarke.Beta;
	motor->park.Angle  = motor->rg.Out;
	motor->park.Sine   = __sinpuf32(motor->park.Angle);
	motor->park.Cosine = __cospuf32(motor->park.Angle);
	PARK_MACRO(motor->park)

// ------------------------------------------------------------------------------
//	Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
	motor->ipark.Ds = motor->VdTesting;
	motor->ipark.Qs = motor->VqTesting;

	motor->ipark.Sine   = motor->park.Sine;
	motor->ipark.Cosine = motor->park.Cosine;
	IPARK_MACRO(motor->ipark)

// ------------------------------------------------------------------------------
//  Connect inputs of the VOLT_CALC module and call the phase voltage calc. macro
// ------------------------------------------------------------------------------
	motor->volt.DcBusVolt = motor->voltageDC;
	motor->volt.MfuncV1 = motor->svgen.Ta;
	motor->volt.MfuncV2 = motor->svgen.Tb;
	motor->volt.MfuncV3 = motor->svgen.Tc;
	PHASEVOLT_MACRO(motor->volt)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
  	motor->svgen.Ualpha = motor->ipark.Alpha;
 	motor->svgen.Ubeta  = motor->ipark.Beta;
	SVGENDQ_MACRO(motor->svgen)

// ------------------------------------------------------------------------------
//  Computed Duty and Write to CMPA register
// ------------------------------------------------------------------------------
	(motor->PwmARegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Ta)+INV_PWM_HALF_TBPRD;
	(motor->PwmBRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tb)+INV_PWM_HALF_TBPRD;
	(motor->PwmCRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tc)+INV_PWM_HALF_TBPRD;


// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
	DlogCh1 = motor->rg.Out;
	DlogCh2 = motor->speed.ElecTheta;   //  motor->svgen.Ta;      //
	DlogCh3 = motor->clarke.As;
	DlogCh4 = motor->clarke.Bs;

//------------------------------------------------------------------------------
// Variable display on PWMDAC - available
//------------------------------------------------------------------------------

	if(DAC_Switch == 1){
	    PwmDacCh1 = _IQtoQ15(motor->rg.Out);            // Launchpad pin DAC1
        PwmDacCh2 = _IQtoQ15(motor->speed.ElecTheta);   // Launchpad pin DAC2
        PwmDacCh3 = _IQtoQ15(motor->volt.VphaseA);      // Launchpad pin DAC3
        PwmDacCh4 = _IQtoQ15(motor->clarke.As);         // Launchpad pin DAC4
	}
	else if(DAC_Switch == 2){
	    PwmDacCh1 = _IQtoQ15(motor->rg.Out);                   // Launchpad pin DAC1
        PwmDacCh2 = _IQtoQ15(motor->speed.ElecTheta);          // Launchpad pin DAC2
        PwmDacCh3 = _IQtoQ15(motor->speed.Speed);              // Launchpad pin DAC3
        PwmDacCh4 = _IQtoQ15(motor->speed1.EstimatedSpeed);    // Launchpad pin DAC4
	}


//------------------------------------------------------------------------------
// Variable display on DAC - DAC-C not available
//------------------------------------------------------------------------------
//    dacAval = (Uint16) _IQtoQ12(motor->rg.Out);
//    dacBval = (Uint16) _IQtoQ12(motor->speed.ElecTheta);
    dacAval = (Uint16) _IQtoQ11(motor->currentAs + _IQ(1));
    dacBval = (Uint16) _IQtoQ11(motor->currentBs + _IQ(1));

	return;
}
#endif


#if BUILDLEVEL == LEVEL3
// ****************************************************************************
// ****************************************************************************
//TODO Motor Control ISR - - Build level 3
//	Level 3 verifies the dq-axis current regulation performed by PID and speed
//	measurement modules
//  lsw=0: lock the rotor of the motor
//  lsw=1: close the current loop
//  NOTE:- Iq loop is closed using internal ramp angle as position feedback.
//	       Therefore, motor speed does not race high with lighter load. User's
//         wanting to use actual rotor angle should ensure that the test value
//         for Iq reference will not race the motor to high speeds. In other
//         words, to use the actual angle, a loaded motor is needed.
// ****************************************************************************
// ****************************************************************************
inline void BuildLevel3(MOTOR_VARS * motor)
{
	// ------------------------------------------------------------------------------
	// Alignment Routine: this routine aligns the motor to zero electrical angle
	// and in case of QEP also finds the index location and initializes the angle
	// w.r.t. the index location
	// ------------------------------------------------------------------------------
	if(!motor->RunMotor)
		motor->lsw = 0;
	else if (motor->lsw == 0)
	{
		// alignment current
		motor->IdRef = IdRef_start;  //IQ(0.1);
		motor->IqRef = 0;
//
//		// for restarting from (motor->RunMotor = 0)
//		motor->rc.TargetValue =  motor->rc.SetpointValue = 0;
//
//		// set up an alignment and hold time for shaft to settle down
//		if (motor->pi_id.Ref >= motor->IdRef)
//		{
//			if (++motor->alignCntr > motor->alignCnt)
//			{
//				motor->alignCntr  = 0;
//				motor->IdRef = IdRef_run;
//				motor->lsw = 1;      // for QEP, spin the motor to find the index pulse
////				motor->IqRef = _IQ(0.05);
//			}
//		}
	    motor->lsw = 1;
	} // end else if (lsw=0)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
    if(motor->lsw==0)motor->rc.TargetValue = 0;
    else motor->rc.TargetValue = motor->SpeedRef;
	RC_MACRO(motor->rc)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    motor->rg.Freq = motor->rc.SetpointValue;
	RG_MACRO(motor->rg)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
    motor->clarke.As = motor->currentAs; // Phase A curr.
    motor->clarke.Bs = motor->currentBs; // Phase B curr.
	CLARKE_MACRO(motor->clarke)

// ------------------------------------------------------------------------------
//  Connect inputs of the SPEED_FR module and call the speed calculation macro
// ------------------------------------------------------------------------------
	motor->speed.ElecTheta = motor->ElecTheta;
	SPEED_FR_MACRO(motor->speed)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
	motor->park.Alpha = motor->clarke.Alpha;
	motor->park.Beta  = motor->clarke.Beta;

	if(motor->lsw==0) motor->park.Angle = 0;
	else if (motor->lsw==1)  motor->park.Angle = 0;//motor->rg.Out; // this state exists only for QEP
	else motor->park.Angle = motor->rg.Out; //  motor->ElecTheta;

	motor->park.Sine   = __sinpuf32(motor->park.Angle);
	motor->park.Cosine = __cospuf32(motor->park.Angle);
	PARK_MACRO(motor->park)

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_REG3 module and call the PID IQ controller macro
// ------------------------------------------------------------------------------
//	if(lsw==0) 	motor->pi_iq.Ref = 0;
//	else		motor->pi_iq.Ref= motor->IqRef;

//    rc_CurrentCmd_Control_Variation_Rate.TargetValue = CurrentCmd_Sin_Frequency_pu;
//    RC_MACRO(rc_CurrentCmd_Control_Variation_Rate);
//
//    rg_CurrentCmd_Generate_Sin.Freq = rc_CurrentCmd_Control_Variation_Rate.SetpointValue;
//    RG_MACRO(rg_CurrentCmd_Generate_Sin);
//
//	motor->pi_iq.Ref =  motor->IqRef * (motor->lsw==0 ? 0 : 1) * __sinpuf32(rg_CurrentCmd_Generate_Sin.Out);
	motor->pi_iq.Ref =  motor->IqRef * (motor->lsw==0 ? 0 : 1) ;
	motor->pi_iq.Fbk = motor->park.Qs;
	PI_MACRO(motor->pi_iq)

// ------------------------------------------------------------------------------
//  Connect inputs of the PI module and call the PID ID controller macro
// ------------------------------------------------------------------------------
//	if(lsw==0)	motor->pi_id.Ref = motor->IdRef;
//	else		motor->pi_id.Ref = motor->IdRef;
	motor->pi_id.Ref = ramper(motor->IdRef, motor->pi_id.Ref, _IQ(0.0001));
	motor->pi_id.Fbk = motor->park.Ds;
	PI_MACRO(motor->pi_id)

// ------------------------------------------------------------------------------
//	Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
    motor->ipark.Ds = motor->pi_id.Out;   // motor->VdTesting
    motor->ipark.Qs = motor->pi_iq.Out ;  // motor->VqTesting
	motor->ipark.Sine   = motor->park.Sine;
    motor->ipark.Cosine = motor->park.Cosine;
	IPARK_MACRO(motor->ipark)

// ------------------------------------------------------------------------------
//  Connect inputs of the VOLT_CALC module and call the phase voltage calc. macro
// ------------------------------------------------------------------------------
    motor->volt.DcBusVolt = motor->voltageDC;
    motor->volt.MfuncV1 = motor->svgen.Ta;
    motor->volt.MfuncV2 = motor->svgen.Tb;
    motor->volt.MfuncV3 = motor->svgen.Tc;
    PHASEVOLT_MACRO(motor->volt)
// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
  	motor->svgen.Ualpha = motor->ipark.Alpha;
 	motor->svgen.Ubeta  = motor->ipark.Beta;
	SVGENDQ_MACRO(motor->svgen)

// ------------------------------------------------------------------------------
//  Computed Duty and Write to CMPA register
// ------------------------------------------------------------------------------
	(motor->PwmARegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Ta)+INV_PWM_HALF_TBPRD;
	(motor->PwmBRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tb)+INV_PWM_HALF_TBPRD;
	(motor->PwmCRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tc)+INV_PWM_HALF_TBPRD;


//------------------------------------------------------------------------------
// Variable display on SPIDAC
//------------------------------------------------------------------------------


	if(DAC_Switch == 1){
        SPIDAC_write_dac_channel(0, (motor->rg.Out)*2047 * DAC_Gain_A + 2048);             //VoutA on SPIDAC Chip
        SPIDAC_write_dac_channel(1, (motor->speed.ElecTheta)*2047 * DAC_Gain_B + 2048);    //VoutB on SPIDAC Chip
        SPIDAC_write_dac_channel(2, (motor->clarke.Bs)*2047 * DAC_Gain_C + 2048);          //VoutC on SPIDAC Chip
        SPIDAC_write_dac_channel(3, (motor->clarke.As)*2047 * DAC_Gain_D + 2048);          //VoutD on SPIDAC Chip
    }
    else if(DAC_Switch == 2){
        SPIDAC_write_dac_channel(0, (motor->pi_iq.Ref)*2047 * DAC_Gain_A + 2048);
        SPIDAC_write_dac_channel(1, (motor->pi_iq.Fbk)*2047 * DAC_Gain_B + 2048);
        SPIDAC_write_dac_channel(2, (motor->pi_id.Ref)*2047 * DAC_Gain_C + 2048);
        SPIDAC_write_dac_channel(3, (motor->pi_id.Fbk)*2047 * DAC_Gain_D + 2048);
    }
    else if(DAC_Switch == 3){
        SPIDAC_write_dac_channel(0, (motor->SpeedRef)*2047 * DAC_Gain_A +2048);
        SPIDAC_write_dac_channel(1, (motor->speed.Speed)*2047 * DAC_Gain_B +2048);
        SPIDAC_write_dac_channel(2, (motor->pi_id.Ref)*2047 * DAC_Gain_C +2048);
        SPIDAC_write_dac_channel(3, (motor->pi_id.Fbk)*2047 * DAC_Gain_D +2048);
    }

    SPIDAC_update_all();//motor1.clarke.As,phase_volt



//------------------------------------------------------------------------------
// Variable display on DAC - DAC-C not available
//------------------------------------------------------------------------------
//    dacAval = (Uint16) _IQtoQ12(motor->ElecTheta);
//    dacBval = (Uint16) _IQtoQ12(motor->rg.Out);
    dacAval = (Uint16) _IQtoQ11(motor->currentAs + _IQ(1));
    dacBval = (Uint16) _IQtoQ11(motor->currentBs + _IQ(1));

	return;
}
#endif


#if BUILDLEVEL == LEVEL4
// ****************************************************************************
// ****************************************************************************
//TODO Motor Control ISR - - Build level 4
//	  Level 4 verifies the speed regulator performed by PID module.
//	  The system speed loop is closed by using the measured speed as feedback
//  lsw=0: lock the rotor of the motor
//  lsw=1: - needed only with QEP encoders until first index pulse
//         - Loops shown for lsw=2 are closed in this stage
//  lsw=2: close speed loop and current loops Id, Iq
// ****************************************************************************
// ****************************************************************************
inline void BuildLevel4(MOTOR_VARS * motor)
{

// ------------------------------------------------------------------------------
// Alignment Routine: this routine aligns the motor to zero electrical angle
// and in case of QEP also finds the index location and initializes the angle
// w.r.t. the index location
// ------------------------------------------------------------------------------

	if(!motor->RunMotor)
		motor->lsw = 0;
	else if (motor->lsw == 0)
	{
		// alignment current
//		motor->IdRef = IdRef_start;  //IQ(0.1);

		// for restarting from (motor->RunMotor 1 -> 0)
		// Reset all parameter for restarting

//		motor->rc.TargetValue =  motor->rc.SetpointValue = 0;
//		if(++Initial_Cnt > 10000)
//		{
//		    Initial_Cnt = 0;
//		    motor->IdRef = IdRef_run;
//		    motor->lsw = 2;
//		}
		// set up an alignment and hold time for shaft to settle down
//		if (motor->pi_id.Ref >= motor->IdRef)
//		{
//			if (++motor->alignCntr > motor->alignCnt)
//			{
//				motor->alignCntr  = 0;
//				motor->IdRef = IdRef_run;
//				motor->lsw = 1;       // for QEP, spin the motor to find the index pulse
////				motor->IqRef = _IQ(0.05);
//			}
//		}
	} // end else if (lsw=0)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
	if(motor->lsw==0)motor->rc.TargetValue = 0;
	else motor->rc.TargetValue = motor->SpeedRef;
	RC_MACRO(motor->rc)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
	motor->rg.Freq = motor->rc.SetpointValue;
	RG_MACRO(motor->rg)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
	motor->clarke.As = motor->currentAs; // Phase A curr.
	motor->clarke.Bs = motor->currentBs; // Phase B curr.
	CLARKE_MACRO(motor->clarke)

// ------------------------------------------------------------------------------
//  Connect inputs of the SPEED_EST module and call the speed calculation macro
// ------------------------------------------------------------------------------
	motor->speed_est.term.MechTheta = motor->MechTheta;
	motor->speed_est.term.CurrentCmd = motor->pi_iq.Ref * BASE_CURRENT;
	SPEED_EST_MACRO(motor->speed_est)

// -----------------------------------------------------------------------------------
//  Connect inputs of the Low Pass Filter module and let estimated acc pass the filter
// -----------------------------------------------------------------------------------
	Estimated_Acc.Input = motor->speed_est.term.AccEst;
	LPF_MARCRO(Estimated_Acc)

//	if(fabsf(Estimated_Acc.Out) > Acc_Threshold )
//	    GPIO_WritePin(GPIO25,TRUE);
//	else
//	    GPIO_WritePin(GPIO25,FALSE);

// ------------------------------------------------------------------------------
//  Connect inputs of the SPEED_FR module and call the speed calculation macro
// ------------------------------------------------------------------------------
	motor->speed.ElecTheta = motor->ElecTheta;
	SPEED_FR_MACRO(motor->speed)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
	motor->park.Alpha = motor->clarke.Alpha;
	motor->park.Beta  = motor->clarke.Beta;

	if(motor->lsw==0) motor->park.Angle = 0;
	else if (motor->lsw==1)  motor->park.Angle = motor->rg.Out; // this state exists only for QEP
	else motor->park.Angle = motor->ElecTheta;

	motor->park.Sine   = __sinpuf32(motor->park.Angle);
	motor->park.Cosine = __cospuf32(motor->park.Angle);

	PARK_MACRO(motor->park)


// ------------------------------------------------------------------------------
//    Speed CMD Calculation
// ------------------------------------------------------------------------------
	//Sin Speed CMD Calculation
    rc_SpeedCmd_SinFrequency_Variation_Rate.TargetValue = SpeedCmd_Sin_Frequency_pu;
    RC_MACRO(rc_SpeedCmd_SinFrequency_Variation_Rate);

    rg_SpeedCmd_Generate_Sin.Freq = rc_SpeedCmd_SinFrequency_Variation_Rate.SetpointValue;
    RG_MACRO(rg_SpeedCmd_Generate_Sin);

    //Trapezoidal Speed CMD Calculation
    if(!rc_SpeedCmd_Trapezoidal.EqualFlag)
    {
        //Speed_CMD_Cnt = 0;
    }
    else
    {
        if(++Speed_CMD_Cnt >= Trapezoidal_Width)   //Trapezoidal_Width(Time) =  Seconds * PWM Frequency
        {
            Speed_CMD_Cnt = 0;
            Speed_CMD_Index = (Speed_CMD_Index + 1) % 2;
            rc_SpeedCmd_Trapezoidal.TargetValue = Speed_CMD_Data[Speed_CMD_Index];
        }
    }

#if RLS_TEST
    if(SpeedFBK_Cnt >= 2000 && Speed_CMD_Switch != 3)
    {
        if(SpeedFBK_Cnt <= 16500)
        {
            SpeedFBK_Cnt++;
            Speed_CMD_Switch = 1;
            motor->SpeedRef = 0;
            RLS_Start_Flag = 1;
        }
        else
        {
            Speed_CMD_Switch = 3;
            rc_SpeedCmd_Trapezoidal.TargetValue = 0;
            rc_SpeedCmd_Trapezoidal.SetpointValue = 0;
            Speed_CMD_Index = 0;
            RLS_Flag = 1;

        }
    }

#endif

    RAMP_SPEED_MACRO(rc_SpeedCmd_Trapezoidal);

    //Update Speed_CMD
    if(Speed_CMD_Switch == 1)        // Step Speed CMD
        Speed_CMD = motor->rc.SetpointValue;  //motor->SpeedRef;
    else if(Speed_CMD_Switch == 2)   // Sin Speed CMD + Offset
        Speed_CMD = motor->rc.SetpointValue + SpeedCmd_Sin_Magnitude_pu * __sinpuf32(rg_SpeedCmd_Generate_Sin.Out);  //motor->SpeedRef;
    else if(Speed_CMD_Switch == 3)   // Trapezoidal Speed CMD
        Speed_CMD = rc_SpeedCmd_Trapezoidal.SetpointValue;

    //Update Last Step of Speed_CMD
    SpeedCmd[1] = SpeedCmd[0];
    SpeedCmd[0] = Speed_CMD;


// -----------------------------------------------------------------------------------
//  Kalman Filter + RLS
// -----------------------------------------------------------------------------------
    if(RLS_Flag)
    {
        if(++RLS_cnt >= RLS_prescaler)
        {
            RLS_cnt = 0;
            RLS_To_Kalman_J = fminf(fmaxf(RLS_Inertia.Out,0.5*J),1.5*J);
        }
        Kalman3X3_Calculate(&Kalman3X3_Handler , motor->MechTheta * TWO_PI ,  motor->pi_iq.Ref * BASE_CURRENT * KT, RLS_To_Kalman_J );
        Kalman2X2_Calculate(&Kalman2X2_Handler , motor->speed.Speed / (POLES/2) * BASE_FREQ * TWO_PI,  motor->pi_iq.Ref * BASE_CURRENT * KT, RLS_To_Kalman_J);
//        Kalman3X3_Calculate(&Kalman3X3_Handler , motor->MechTheta * TWO_PI ,  motor->pi_iq.Ref * BASE_CURRENT * KT, J);
//        Kalman2X2_Calculate(&Kalman2X2_Handler , motor->speed.Speed / (POLES/2) * BASE_FREQ * TWO_PI,  motor->pi_iq.Ref * BASE_CURRENT * KT, J);
    }
    else
    {
        Kalman3X3_Calculate(&Kalman3X3_Handler , motor->MechTheta * TWO_PI ,  motor->pi_iq.Ref * BASE_CURRENT * KT, J);
        Kalman2X2_Calculate(&Kalman2X2_Handler , motor->speed.Speed / (POLES/2) * BASE_FREQ * TWO_PI,  motor->pi_iq.Ref * BASE_CURRENT * KT, J);
    }

    /*   Need be revised with different Kalman Filter for RLS Test*/

    Kalman_e.Input = Kalman3X3_Handler.e;
    LPF_MARCRO(Kalman_e)

    Kalman3X3_TL[1] = Kalman3X3_TL[0];
//    Kalman3X3_TL[0] = Kalman3X3_Handler.Terminal.TL;
    Kalman3X3_TL[0] = Kalman3X3_Handler.KalmanToRls_TL;
    Kalman2X2_TL[1] = Kalman2X2_TL[0];
    Kalman2X2_TL[0] = Kalman2X2_Handler.Terminal.TL;



    SpeedCmd0_1 = fabsf(SpeedCmd[0] - SpeedCmd[1]);
//if(fabsf(Speed_CMD - Kalman3X3_Handler.Terminal.speed / TWO_PI / BASE_FREQ) < Speed_err_threshold)
    if(fabsf(SpeedCmd[0] - SpeedCmd[1]) < 0.000001)
    {

//        GPIO_WritePin(GPIO25,TRUE);
        Kalman3X3_Handler.KalmanToRls_TL = Kalman3X3_Handler.Terminal.TL;
        Kalman2X2_Handler.KalmanToRls_TL = Kalman2X2_Handler.Terminal.TL;
    }
    else
    {
//        GPIO_WritePin(GPIO25,FALSE);
//        Kalman3X3_Handler.KalmanToRls_TL = Kalman3X3_TL[1];
//        Kalman2X2_Handler.KalmanToRls_TL = Kalman2X2_TL[1];
        Kalman3X3_Handler.KalmanToRls_TL = Kalman3X3_Handler.Terminal.TL;
        Kalman2X2_Handler.KalmanToRls_TL = Kalman2X2_Handler.Terminal.TL;

    }

    Te = motor->pi_iq.Ref * BASE_CURRENT * KT;
#if KALMAN3X3_OR_2X2
    Te_TL_Fbk = Iq_FBK.Out * BASE_CURRENT * KT - Kalman3X3_Handler.KalmanToRls_TL;
//    Te_TL_Cmd = motor->pi_iq.Ref * BASE_CURRENT * KT - Kalman3X3_Handler.KalmanToRls_TL;
    Te_TL_Cmd = motor->pi_iq.Ref * BASE_CURRENT * KT * RLS_Gain - Kalman3X3_Handler.KalmanToRls_TL;
#else
    Te_TL_Fbk = Iq_FBK.Out * BASE_CURRENT * KT - Kalman2X2_Handler.KalmanToRls_TL;
    Te_TL_Cmd = motor->pi_iq.Ref * BASE_CURRENT * KT - Kalman2X2_Handler.KalmanToRls_TL;
#endif
//    if(RLS_Flag)
//        RLS_Calculate(&RLS_Handler, Kalman2X2_Handler.Terminal.speed, Te_TL_Cmd, Estimated_Acc.Out);
//    GPIO_WritePin(GPIO25,FALSE);

    /*   Need be revised with different Kalman Filter for RLS Test*/
#if KALMAN3X3_OR_2X2

    RLS_Calculate(&RLS_Handler, &Kalman3X3_Handler, Kalman3X3_Handler.Terminal.speed, Te_TL_Cmd, Estimated_Acc.Out, RLS_Start_Flag);
//    RLS_Calculate(&RLS_Handler, &Kalman3X3_Handler, motor->speed.Speed / (POLES/2) * TWO_PI * BASE_FREQ, Te_TL_Cmd, Estimated_Acc.Out, RLS_Start_Flag);

//    RLS_Calculate(&RLS_Handler, &Kalman3X3_Handler, motor->speed_est.term.Enhanced_SpeedEst_pu *BASE_FREQ * TWO_PI, Te_TL_Cmd, Estimated_Acc.Out,RLS_Start_Flag);
//    RLS_Calculate(&RLS_Handler, &Kalman3X3_Handler, motor->speed.Speed / (POLES/2) *BASE_FREQ * TWO_PI, Te_TL_Cmd, Estimated_Acc.Out, RLS_Start_Flag);
#else

    RLS_Calculate(&RLS_Handler, &Kalman3X3_Handler,Kalman2X2_Handler.Terminal.speed, Te_TL_Cmd, Estimated_Acc.Out, RLS_Start_Flag);
#endif
//    GPIO_WritePin(GPIO25,TRUE);

    RLS_Inertia.Input = RLS_Handler.Terminal.Inertia;
    LPF_MARCRO(RLS_Inertia)

#if WI_GEARBOX
    if(Adaptive_On)
    {
        Speed_Kp_Gain = 4 * RLS_Inertia.Out / J;
        Speed_Kp_Gain = fminf(fmaxf(Speed_Kp_Gain ,0.5) , 5.5);
    }
#else
    if(Adaptive_On)
    {
        Speed_Kp_Gain = RLS_Inertia.Out / J;
        Speed_Kp_Gain = fminf(fmaxf(Speed_Kp_Gain ,0.1) , 1.2);
    }
#endif
// ------------------------------------------------------------------------------
//    Connect inputs of the PI module and call the PID speed controller macro
// ------------------------------------------------------------------------------
   if (++motor->SpeedLoopCount >= motor->SpeedLoopPrescaler)
     {
        motor->SpeedLoopCount = 0;
        motor->pi_spd.term.Ref = Speed_CMD;


        if(SpeedFBK_Cnt >= 2000 && motor->lsw==2) {
//            motor->pi_spd.term.Fbk = motor->speed_est.term.Enhanced_SpeedEst_pu;
//            motor->pi_spd.term.Fbk = Kalman3X3_Handler.Terminal.speed / TWO_PI / BASE_FREQ;
            motor->pi_spd.term.Fbk = motor->speed.Speed / (POLES/2);
            motor1.pi_spd.param.Kp = _IQ(1.2 * Speed_Kp_Gain);   //1.2 * Speed_Kp_Gain(1.0)  for speed bw = 30 HZ
            motor1.pi_spd.param.Ki = _IQ(0.5 * Speed_Ki_Gain);   //0.5 * Speed_Ki_Gain(1.0)  for speed bw = 30 HZ
        }
        else if(motor->lsw==2){
            motor->pi_spd.term.Fbk = motor->speed.Speed / (POLES/2);
            SpeedFBK_Cnt++;
            motor1.pi_spd.param.Kp = _IQ(J*5*2*PI*BASE_FREQ/BASE_CURRENT*2*PI);
            motor1.pi_spd.param.Ki = _IQ(BM*5*2*PI*BASE_FREQ/BASE_CURRENT*2*PI);
        }
        PI_SPEED(motor->pi_spd);
     }

    if(motor->lsw==0 || motor->lsw==1)
    {
        motor->pi_spd.data.i1 = 0; motor->pi_spd.data.ui = 0; motor->pi_spd.data.up = 0;
    }

// ------------------------------------------------------------------------------
//    Connect inputs of the PI module and call the PID IQ controller macro
// ------------------------------------------------------------------------------
	if(motor->lsw==0)
	{
		motor->pi_iq.Ref = 0;
		motor->pi_iq.ui  = 0;
	}
	else if(motor->lsw==1) motor->pi_iq.Ref = motor->IqRef;
//	else motor->pi_iq.Ref = motor->IqRef ;
	else motor->pi_iq.Ref = motor->pi_spd.term.Out / 0.169 ;

	Iq_FBK.Input = motor->park.Qs;
	LPF_MARCRO(Iq_FBK)
	motor->pi_iq.Fbk = Iq_FBK.Out;
	PI_MACRO(motor->pi_iq)

    Iq_test_Kt.Input = motor->park.Qs;
	LPF_MARCRO(Iq_test_Kt)

// ------------------------------------------------------------------------------
//    Connect inputs of the PI module and call the PID ID controller macro
// ------------------------------------------------------------------------------
	motor->pi_id.Ref=ramper(motor->IdRef, motor->pi_id.Ref, _IQ(0.0001));

    Id_FBK.Input = motor->park.Ds;
    LPF_MARCRO(Id_FBK)
	motor->pi_id.Fbk = Id_FBK.Out;
	PI_MACRO(motor->pi_id)

// ------------------------------------------------------------------------------
//	Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------

//    Vq_Decoupling = motor->pi_spd.term.Ref * BASE_FREQ * TWO_PI * (POLES/2) * (LS * motor->pi_id.Ref * BASE_CURRENT + 0.0225) / BASE_VOLTAGE;
//	Vd_Decoupling = -motor->pi_spd.term.Ref * BASE_FREQ * TWO_PI * (POLES/2) * LS * motor->pi_iq.Ref * BASE_CURRENT / BASE_VOLTAGE;

	motor->ipark.Ds = motor->pi_id.Out + Vd_Decoupling;
	motor->ipark.Qs = motor->pi_iq.Out + Vq_Decoupling;
//    motor->ipark.Ds = motor->pi_id.Out;
//    motor->ipark.Qs = motor->pi_iq.Out;
	motor->ipark.Sine   = motor->park.Sine;
	motor->ipark.Cosine = motor->park.Cosine;
	IPARK_MACRO(motor->ipark)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
	motor->svgen.Ualpha = motor->ipark.Alpha;
	motor->svgen.Ubeta  = motor->ipark.Beta;
	SVGENDQ_MACRO(motor->svgen)

// ------------------------------------------------------------------------------
//  Computed Duty and Write to CMPA register
// ------------------------------------------------------------------------------
	(motor->PwmARegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Ta)+INV_PWM_HALF_TBPRD;
	(motor->PwmBRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tb)+INV_PWM_HALF_TBPRD;
	(motor->PwmCRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tc)+INV_PWM_HALF_TBPRD;

//------------------------------------------------------------------------------
// Variable display on SPIDAC
//------------------------------------------------------------------------------


    if(DAC_Switch == 1){
        DAC_Gain_A = 100; DAC_Gain_B = 2; DAC_Gain_C = 2; DAC_Gain_D = 2;
        SPIDAC_write_dac_channel(0, (Kalman_e.Out)*2047 * DAC_Gain_A + 2048);             //VoutA on SPIDAC Chip
        SPIDAC_write_dac_channel(1, (Kalman3X3_Handler.KalmanToRls_TL *0.1)*2047 * DAC_Gain_B + 2048);    //VoutB on SPIDAC Chip
        SPIDAC_write_dac_channel(2, (Kalman3X3_Handler.Terminal.TL *0.1)*2047 * DAC_Gain_C + 2048);          //VoutC on SPIDAC Chip
        SPIDAC_write_dac_channel(3, (Kalman2X2_Handler.Terminal.TL *0.1)*2047 * DAC_Gain_D + 2048);          //VoutD on SPIDAC Chip
    }
    else if(DAC_Switch == 2){
        SPIDAC_write_dac_channel(0, (motor->pi_iq.Ref)*2047 * DAC_Gain_A + 2048);
        SPIDAC_write_dac_channel(1, (motor->pi_iq.Fbk)*2047 * DAC_Gain_B + 2048);
        SPIDAC_write_dac_channel(2, (Vq_Decoupling)*2047 * DAC_Gain_C + 2048);
        SPIDAC_write_dac_channel(3, (motor->pi_iq.Out)*2047 * DAC_Gain_D + 2048);
    }
//    else if(DAC_Switch == 3){
//        DAC_Gain_A = 60; DAC_Gain_B = 60;
//        SPIDAC_write_dac_channel(0, (motor->pi_spd.term.Ref)*2047 * DAC_Gain_A + 2048);
//        SPIDAC_write_dac_channel(1, (motor->speed_est.term.Enhanced_SpeedEst_pu)*2047 * DAC_Gain_B + 2048);
//        SPIDAC_write_dac_channel(2, (Estimated_Acc.Out/(2*PI*BASE_FREQ))*2047 * DAC_Gain_C + 2048);
//        SPIDAC_write_dac_channel(3, (motor->speed_est.term.AccEst/(2*PI)/(2*PI*BASE_FREQ))*2047 * DAC_Gain_D + 2048);
//    }
    else if(DAC_Switch == 4){
        DAC_Gain_A = 50; DAC_Gain_B = 50; DAC_Gain_C = 50; DAC_Gain_D = 50;
        SPIDAC_write_dac_channel(0, (motor->pi_spd.term.Ref)*2047 * DAC_Gain_A + 2048);
        SPIDAC_write_dac_channel(1, (motor->speed_est.term.Enhanced_SpeedEst_pu)*2047 * DAC_Gain_B + 2048);
        SPIDAC_write_dac_channel(2, (Kalman3X3_Handler.Terminal.speed/(2*PI*BASE_FREQ))*2047 * DAC_Gain_C + 2048);
        SPIDAC_write_dac_channel(3, (Kalman2X2_Handler.Terminal.speed/(2*PI*BASE_FREQ))*2047 * DAC_Gain_D + 2048);
    }
//    else if(DAC_Switch == 5){
//        DAC_Gain_A = 60; DAC_Gain_B = 60;// DAC_Gain_C = 20; DAC_Gain_D = 20;
//        SPIDAC_write_dac_channel(0, (motor->pi_spd.term.Ref)*2047 * DAC_Gain_A + 2048);
//        SPIDAC_write_dac_channel(1, (motor->speed_est.term.Enhanced_SpeedEst_pu)*2047 * DAC_Gain_B + 2048);
//        SPIDAC_write_dac_channel(2, (Te_TL_Fbk)*2047 * DAC_Gain_C + 2048);
//        SPIDAC_write_dac_channel(3, (Te_TL_Cmd)*2047 * DAC_Gain_D + 2048);
//    }
    else if(DAC_Switch == 6){
#if WI_GEARBOX
        DAC_Gain_A = 50; DAC_Gain_B = 50; DAC_Gain_C = 670; DAC_Gain_D = 670;
        SPIDAC_write_dac_channel(0, (motor->pi_spd.term.Ref)*2047 * DAC_Gain_A + 2048);
        SPIDAC_write_dac_channel(1, (motor->speed_est.term.Enhanced_SpeedEst_pu)*2047 * DAC_Gain_B + 2048);
        SPIDAC_write_dac_channel(2, (0.00065)*2047 * DAC_Gain_C + 2048);
        SPIDAC_write_dac_channel(3, (RLS_Inertia.Out)*2047 * DAC_Gain_D + 2048);
#else
//        DAC_Gain_A = 50; DAC_Gain_B = 50; DAC_Gain_C = 5000; DAC_Gain_D = 5000;   //No Brake
        DAC_Gain_A = 50; DAC_Gain_B = 50; DAC_Gain_C = 570; DAC_Gain_D = 570;   // Brake
        SPIDAC_write_dac_channel(0, (motor->pi_spd.term.Ref)*2047 * DAC_Gain_A + 2048);
        SPIDAC_write_dac_channel(1, (motor->speed_est.term.Enhanced_SpeedEst_pu)*2047 * DAC_Gain_B + 2048);
        SPIDAC_write_dac_channel(2, (J)*2047 * DAC_Gain_C + 2048);
        SPIDAC_write_dac_channel(3, (RLS_Inertia.Out)*2047 * DAC_Gain_D + 2048);
#endif
    }
//    else if(DAC_Switch == 7){
//        DAC_Gain_A = 50; DAC_Gain_B = 2; DAC_Gain_C = 100; DAC_Gain_D = 570;
//        SPIDAC_write_dac_channel(0, (motor->speed_est.term.Enhanced_SpeedEst_pu)*2047 * DAC_Gain_A + 2048);             //VoutA on SPIDAC Chip
//        SPIDAC_write_dac_channel(1, (Kalman3X3_Handler.KalmanToRls_TL *0.1)*2047 * DAC_Gain_B + 2048);    //VoutB on SPIDAC Chip
//        SPIDAC_write_dac_channel(2, (Kalman_e.Out)*2047 * DAC_Gain_C + 2048);
//        SPIDAC_write_dac_channel(3, (RLS_Inertia.Out)*2047 * DAC_Gain_D + 2048);
//    }
    else if(DAC_Switch == 8){
        DAC_Gain_A = 50; DAC_Gain_B = 2; DAC_Gain_C = 2; DAC_Gain_D = 570;
        SPIDAC_write_dac_channel(0, (motor->speed_est.term.Enhanced_SpeedEst_pu)*2047 * DAC_Gain_A + 2048);
        SPIDAC_write_dac_channel(1, (Kalman3X3_Handler.Terminal.TL *0.1)*2047 * DAC_Gain_B + 2048);
        SPIDAC_write_dac_channel(2, (Kalman3X3_Handler.KalmanToRls_TL *0.1)*2047 * DAC_Gain_C + 2048);
        SPIDAC_write_dac_channel(3, (RLS_Inertia.Out)*2047 * DAC_Gain_D + 2048);
    }



    SPIDAC_update_all();//motor1.clarke.As,phase_volt


	return;

}
#endif


#if BUILDLEVEL == LEVEL5
// ****************************************************************************
// ****************************************************************************
//TODO Motor Control ISR - - Build level 5
//  Level 5 verifies the position control
//  Position references generated locally
//  lsw=0: lock the rotor of the motor
//  lsw=1: - needed only with QEP encoders until first index pulse
//         - Loops shown for lsw=2 are closed in this stage
//  lsw=2: close all loops, position, speed and currents Id, Iq
// ****************************************************************************
// ****************************************************************************
inline void BuildLevel5(MOTOR_VARS * motor)
{

	// ------------------------------------------------------------------------------
	//  Connect inputs of the RMP module and call the ramp control macro
	// ------------------------------------------------------------------------------
	if(!motor->RunMotor)
		motor->lsw = 0;
	else if (motor->lsw == 0)
	{
		// alignment curretnt
		motor->IdRef = IdRef_start;  //IQ(0.1);

		// for restarting from (motor->RunMotor = 0)
		motor->rc.TargetValue = motor->rc.SetpointValue = 0;

		// set up an alignment and hold time for shaft to settle down
		if (motor->pi_id.Ref >= motor->IdRef)
		{
			if (++motor->alignCntr >= motor->alignCnt)
			{
				motor->alignCntr  = 0;
				motor->IdRef = IdRef_run;
				motor->lsw = 1;      // for QEP, spin the motor to find the index pulse
//				motor->IqRef = _IQ(0.05);
			}
		}
	} // end else if (lsw=0)

// ------------------------------------------------------------------------------
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
	motor->clarke.As = motor->currentAs; // Phase A curr.
	motor->clarke.Bs = motor->currentBs; // Phase B curr.
	CLARKE_MACRO(motor->clarke)

// ------------------------------------------------------------------------------
//  Connect inputs of the SPEED_FR module and call the speed calculation macro
// ------------------------------------------------------------------------------
	motor->speed.ElecTheta = motor->ElecTheta;
	SPEED_FR_MACRO(motor->speed)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
	motor->park.Alpha = motor->clarke.Alpha;
	motor->park.Beta  = motor->clarke.Beta;

	if(motor->lsw==0) motor->park.Angle = 0;
	else if (motor->lsw==1)  motor->park.Angle = motor->rg.Out; // this state exists only for QEP
	else motor->park.Angle = motor->ElecTheta;

	motor->park.Sine   = __sinpuf32(motor->park.Angle);
	motor->park.Cosine = __cospuf32(motor->park.Angle);
	PARK_MACRO(motor->park)

// ------------------------------------------------------------------------------
//    Connect inputs of the PID module and call the PID speed controller macro
// ------------------------------------------------------------------------------
	if (++motor->SpeedLoopCount >= motor->SpeedLoopPrescaler)
	{
		motor->SpeedLoopCount=0;
		if (motor->lsw == 0)
		{
			motor->rc.SetpointValue = 0;  // position = 0 deg
			motor->pid_spd.data.d1 = 0; motor->pid_spd.data.d2 = 0; motor->pid_spd.data.i1 = 0;
			motor->pid_spd.data.ud = 0; motor->pid_spd.data.ui = 0; motor->pid_spd.data.up = 0;
			motor->pi_pos.ui = 0;
		}
		else
		{

		// ========== reference position setting =========
		// --------------------------------------------------------------------
		//  Connect inputs of RAMP GEN module and call ramp generator macro
		// --------------------------------------------------------------------
		motor->rg.Freq = motor->SpeedRef * motor->SpeedLoopPrescaler/(POLES/2);
		RG_MACRO(motor->rg)

		// choose between one of  two position commands - watch Ref and Fbk
		// Position command read from a table
		   motor->rc.TargetValue = refPosGen(motor->rc.TargetValue);
		// Position command generated as integral of SpeedRef
//		   motor->rc.TargetValue = motor->rg.Out;

		motor->rc.SetpointValue = _IQfrac(motor->rc.TargetValue);
		// Rolling in angle within 0 to 1pu
		if (motor->rc.SetpointValue < 0)
			motor->rc.SetpointValue += _IQ(1.0);

		motor->pi_pos.Ref = motor->rc.SetpointValue;
		motor->pi_pos.Fbk = motor->MechTheta;
		PI_POS_MACRO(motor->pi_pos);

		// speed PI regulator
		motor->pid_spd.term.Ref = motor->pi_pos.Out;     //	motor->pid_spd.term.Ref = motor->rc.SetpointValue;
		motor->pid_spd.term.Fbk = motor->speed.Speed;
		PID_MACRO(motor->pid_spd);                //	motor->pi_spd.Out = motor->pi_pos.Out;
		}
	}

// ------------------------------------------------------------------------------
//    Connect inputs of the PID module and call the PID IQ controller macro
// ------------------------------------------------------------------------------
	if(motor->lsw==0)
	{
		motor->pi_iq.Ref = 0;
		motor->pi_iq.ui  = 0;
	}
	else if(motor->lsw==1) motor->pi_iq.Ref = motor->IqRef;
	else motor->pi_iq.Ref =  motor->pid_spd.term.Out;
	motor->pi_iq.Fbk = motor->park.Qs;
	PI_MACRO(motor->pi_iq);

// ------------------------------------------------------------------------------
//    Connect inputs of the PID module and call the PID ID controller macro
// ------------------------------------------------------------------------------
	motor->pi_id.Ref = ramper(motor->IdRef, motor->pi_id.Ref, _IQ(0.0001));  //ramprate = 1pu/s
	motor->pi_id.Fbk = motor->park.Ds;
	PI_MACRO(motor->pi_id);

// ------------------------------------------------------------------------------
//  Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
	motor->ipark.Ds = motor->pi_id.Out;
	motor->ipark.Qs = motor->pi_iq.Out;
	motor->ipark.Sine   = motor->park.Sine;
	motor->ipark.Cosine = motor->park.Cosine;
	IPARK_MACRO(motor->ipark);

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
	motor->svgen.Ualpha = motor->ipark.Alpha;
	motor->svgen.Ubeta  = motor->ipark.Beta;
	SVGENDQ_MACRO(motor->svgen)

// ------------------------------------------------------------------------------
//  Computed Duty and Write to CMPA register
// ------------------------------------------------------------------------------
	(motor->PwmARegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Ta)+INV_PWM_HALF_TBPRD;
	(motor->PwmBRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tb)+INV_PWM_HALF_TBPRD;
	(motor->PwmCRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tc)+INV_PWM_HALF_TBPRD;

// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
	DlogCh1 = motor->ElecTheta;     // motor->rg.Out;
	DlogCh2 = motor->MechTheta;     // motor->park.Ds;
	DlogCh3 = motor->park.Qs;
	DlogCh4 = motor->park.Beta;

//------------------------------------------------------------------------------
// Variable display on PWMDAC - available
//------------------------------------------------------------------------------
    PwmDacCh1 = _IQtoQ15(motor->ElecTheta);     // Launchpad pin DAC1
    PwmDacCh2 = _IQtoQ15(motor->MechTheta);     // Launchpad pin DAC2
    PwmDacCh3 = _IQtoQ15(motor->park.Qs);       // Launchpad pin DAC3
    PwmDacCh4 = _IQtoQ15(motor->park.Beta);     // Launchpad pin DAC4

//------------------------------------------------------------------------------
// Variable display on DAC - DAC-C not available
//------------------------------------------------------------------------------
//    dacAval = (Uint16) _IQtoQ12(motor->ElecTheta);
//    dacBval = (Uint16) _IQtoQ12(motor->MechTheta);
    dacAval = (Uint16) _IQtoQ11(motor->currentAs + _IQ(1));
    dacBval = (Uint16) _IQtoQ11(motor->currentBs + _IQ(1));

	return;
}
#endif

#if BUILDLEVEL == LEVEL6
// ****************************************************************************
// ****************************************************************************
//TODO Motor Control ISR - - Build level 6
//  Level 6 speed estimation and rotor position estmation modules
//
//  lsw=0: lock the rotor of the motor
//  lsw=1: close the current loop
//  NOTE:- Iq loop is closed using internal ramp angle as position feedback.
//         Therefore, motor speed does not race high with lighter load. User's
//         wanting to use actual rotor angle should ensure that the test value
//         for Iq reference will not race the motor to high speeds. In other
//         words, to use the actual angle, a loaded motor is needed.
// ****************************************************************************
// ****************************************************************************
inline void BuildLevel6(MOTOR_VARS * motor)
{
    // ------------------------------------------------------------------------------
    // Alignment Routine: this routine aligns the motor to zero electrical angle
    // and in case of QEP also finds the index location and initializes the angle
    // w.r.t. the index location
    // ------------------------------------------------------------------------------
    if(!motor->RunMotor)
        motor->lsw = 0;
    else if (motor->lsw == 0)
    {
        // alignment current
        motor->IdRef = IdRef_start;  //IQ(0.1);

        // for restarting from (motor->RunMotor = 0)
        motor->rc.TargetValue =  motor->rc.SetpointValue = 0;

        // set up an alignment and hold time for shaft to settle down
        if (motor->pi_id.Ref >= motor->IdRef)
        {
            if (++motor->alignCntr > motor->alignCnt)
            {
                motor->alignCntr  = 0;
                motor->IdRef = IdRef_run;
                motor->lsw = 1;      // for QEP, spin the motor to find the index pulse
//              motor->IqRef = _IQ(0.05);
            }
        }
    } // end else if (lsw=0)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
    if(motor->lsw==0)motor->rc.TargetValue = 0;
    else motor->rc.TargetValue = motor->SpeedRef;
    RC_MACRO(motor->rc)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    motor->rg.Freq = motor->rc.SetpointValue;
    RG_MACRO(motor->rg)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
//  Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
    motor->clarke.As = motor->currentAs; // Phase A curr.
    motor->clarke.Bs = motor->currentBs; // Phase B curr.
    CLARKE_MACRO(motor->clarke)

// ------------------------------------------------------------------------------
//  Connect inputs of the SPEED_FR module and call the speed calculation macro
// ------------------------------------------------------------------------------
    motor->speed.ElecTheta = motor->ElecTheta;
    SPEED_FR_MACRO(motor->speed)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
    motor->park.Alpha = motor->clarke.Alpha;
    motor->park.Beta  = motor->clarke.Beta;

    if(motor->lsw==0) motor->park.Angle = 0;
    else if (motor->lsw==1)  motor->park.Angle = motor->rg.Out; // this state exists only for QEP
    else motor->park.Angle = motor->smo.Theta; //  motor->ElecTheta;

    motor->park.Sine   = __sinpuf32(motor->park.Angle);
    motor->park.Cosine = __cospuf32(motor->park.Angle);
    PARK_MACRO(motor->park)

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_REG3 module and call the PID IQ controller macro
// ------------------------------------------------------------------------------
//  if(lsw==0)  motor->pi_iq.Ref = 0;
//  else        motor->pi_iq.Ref= motor->IqRef;
    motor->pi_iq.Ref =  motor->IqRef * (motor->lsw==0 ? 0 : 1);
    motor->pi_iq.Fbk = motor->park.Qs;
    PI_MACRO(motor->pi_iq)

// ------------------------------------------------------------------------------
//  Connect inputs of the PI module and call the PID ID controller macro
// ------------------------------------------------------------------------------
//  if(lsw==0)  motor->pi_id.Ref = motor->IdRef;
//  else        motor->pi_id.Ref = motor->IdRef;
    motor->pi_id.Ref = ramper(motor->IdRef, motor->pi_id.Ref, _IQ(0.0001));
    motor->pi_id.Fbk = motor->park.Ds;
    PI_MACRO(motor->pi_id)

// ------------------------------------------------------------------------------
//  Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
    motor->ipark.Ds = motor->pi_id.Out;   // motor->VdTesting
    motor->ipark.Qs = motor->pi_iq.Out ;  // motor->VqTesting
    motor->ipark.Sine   = motor->park.Sine;
    motor->ipark.Cosine = motor->park.Cosine;
    IPARK_MACRO(motor->ipark)

// ------------------------------------------------------------------------------
//  Connect inputs of the VOLT_CALC module and call the phase voltage calc. macro
// ------------------------------------------------------------------------------
    motor->volt.DcBusVolt = motor->voltageDC;
    motor->volt.MfuncV1 = motor->svgen.Ta;
    motor->volt.MfuncV2 = motor->svgen.Tb;
    motor->volt.MfuncV3 = motor->svgen.Tc;
    PHASEVOLT_MACRO(motor->volt)

// ------------------------------------------------------------------------------
//    Connect inputs of the SMO_POS module and call the sliding-mode observer macro
// ------------------------------------------------------------------------------
    motor->smo.Ialpha = motor->clarke.Alpha;
    motor->smo.Ibeta  = motor->clarke.Beta;
    motor->smo.Valpha = motor->volt.Valpha;
    motor->smo.Vbeta  = motor->volt.Vbeta;
    SMO_MACRO(motor->smo)

// ------------------------------------------------------------------------------
//    Connect inputs of the SPEED_EST module and call the estimated speed macro
// ------------------------------------------------------------------------------
    motor->speed1.EstimatedTheta = motor->smo.Theta;
    SE_MACRO(motor->speed1)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
    motor->svgen.Ualpha = motor->ipark.Alpha;
    motor->svgen.Ubeta  = motor->ipark.Beta;
    SVGENDQ_MACRO(motor->svgen)

// ------------------------------------------------------------------------------
//  Computed Duty and Write to CMPA register
// ------------------------------------------------------------------------------
    (motor->PwmARegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Ta)+INV_PWM_HALF_TBPRD;
    (motor->PwmBRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tb)+INV_PWM_HALF_TBPRD;
    (motor->PwmCRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tc)+INV_PWM_HALF_TBPRD;

// ------------------------------------------------------------------------------
//  Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
    DlogCh1 = motor->rg.Out;
    DlogCh2 = motor->smo.Theta;     // motor->currentAs;
    DlogCh3 = motor->clarke.As;  // motor->current.Bs;
    DlogCh4 = motor->clarke.Bs;  // motor->current.Cs;

//------------------------------------------------------------------------------
// Variable display on PWMDAC - available
//------------------------------------------------------------------------------
    PwmDacCh1 = _IQtoQ15(motor->rg.Out);            // Launchpad pin DAC1
    PwmDacCh2 = _IQtoQ15(motor->smo.Theta);         // Launchpad pin DAC2
    PwmDacCh3 = _IQtoQ15(motor->clarke.As);         // Launchpad pin DAC3
    PwmDacCh4 = _IQtoQ15(motor->volt.Valpha);       // Launchpad pin DAC4

//------------------------------------------------------------------------------
// Variable display on DAC - DAC-C not available
//------------------------------------------------------------------------------
//    dacAval = (Uint16) _IQtoQ12(motor->rg.Out);
//    dacBval = (Uint16) _IQtoQ12(motor->smo.Theta);
    dacAval = (Uint16) _IQtoQ11(motor->currentAs + _IQ(1));
    dacBval = (Uint16) _IQtoQ11(motor->currentBs + _IQ(1));

    return;
}
#endif

#if BUILDLEVEL == LEVEL7
// ****************************************************************************
// ****************************************************************************
//TODO Motor Control ISR - - Build level 7
//  Level 7 verifies the speed regulator performed by PID_GRANDO_CONTROLLER module.
//  The system speed loop is closed by using the estimated speed as a feedback.
//
//  lsw=0: lock the rotor of the motor
//  lsw=1: close the current loop
//  lsw=2: close the speed loop
//
//  NOTE:- Iq loop is closed using internal ramp angle as position feedback.
//         Therefore, motor speed does not race high with lighter load. User's
//         wanting to use actual rotor angle should ensure that the test value
//         for Iq reference will not race the motor to high speeds. In other
//         words, to use the actual angle, a loaded motor is needed.
// ****************************************************************************
// ****************************************************************************
inline void BuildLevel7(MOTOR_VARS * motor)
{
    // ------------------------------------------------------------------------------
    // Alignment Routine: this routine aligns the motor to zero electrical angle
    // and in case of QEP also finds the index location and initializes the angle
    // w.r.t. the index location
    // ------------------------------------------------------------------------------
    if(!motor->RunMotor)
        motor->lsw = 0;
    else if (motor->lsw == 0)
    {
        // alignment current
        motor->IdRef = IdRef_start;  //IQ(0.1);

        // for restarting from (motor->RunMotor = 0)
        motor->rc.TargetValue =  motor->rc.SetpointValue = 0;

        // back to the current loop
        motor->lsw = 1;

    } // end else if (lsw=0)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
    if(motor->lsw==0) motor->rc.TargetValue = 0;
    else motor->rc.TargetValue = motor->SpeedRef;
    RC_MACRO(motor->rc)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    motor->rg.Freq = motor->rc.SetpointValue;
    RG_MACRO(motor->rg)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
//  Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
    motor->clarke.As = motor->currentAs; // Phase A curr.
    motor->clarke.Bs = motor->currentBs; // Phase B curr.
    CLARKE_MACRO(motor->clarke)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
    motor->park.Alpha = motor->clarke.Alpha;
    motor->park.Beta  = motor->clarke.Beta;

    if(motor->lsw==0) motor->park.Angle = 0;
    else if (motor->lsw==1)  motor->park.Angle = motor->rg.Out; // this state exists only for QEP
    else if (motor->lsw==2)  motor->park.Angle = motor->smo.Theta; //  motor->ElecTheta;
    else motor->park.Angle = theta; // motor->smo.Theta + offset

    motor->park.Sine   = __sinpuf32(motor->park.Angle);
    motor->park.Cosine = __cospuf32(motor->park.Angle);
    PARK_MACRO(motor->park)

// ------------------------------------------------------------------------------
//    Connect inputs of the PI module and call the PID speed controller macro
// ------------------------------------------------------------------------------
   if (++motor->SpeedLoopCount >= motor->SpeedLoopPrescaler)
     {
        motor->SpeedLoopCount = 0;

        motor->pid_spd.term.Ref = motor->rc.SetpointValue;  //motor->SpeedRef;
        motor->pid_spd.term.Fbk = motor->speed1.EstimatedSpeed;
        PID_MACRO(motor->pid_spd);
     }

    if(motor->lsw==0 || motor->lsw==1)
    {
        motor->pid_spd.data.d1 = 0; motor->pid_spd.data.d2 = 0; motor->pid_spd.data.i1 = 0;
        motor->pid_spd.data.ud = 0; motor->pid_spd.data.ui = 0; motor->pid_spd.data.up = 0;
    }

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_REG3 module and call the PID IQ controller macro
// ------------------------------------------------------------------------------
//  if(lsw==0)  motor->pi_iq.Ref = 0;
//  else if(lsw==1)  motor->pi_iq.Ref = motor->IqRef;
//  else        motor->pi_iq.Ref = motor->pid_spd.term.Out;
    motor->pi_iq.Ref = (motor->lsw==0) ? 0 :
                       (motor->lsw==1) ? motor->IqRef : motor->pid_spd.term.Out;
    motor->pi_iq.Fbk = motor->park.Qs;
    PI_MACRO(motor->pi_iq)

// ------------------------------------------------------------------------------
//  Connect inputs of the PI module and call the PID ID controller macro
// ------------------------------------------------------------------------------
//  if(lsw==0)  motor->pi_id.Ref = motor->IdRef;
//  else        motor->pi_id.Ref = motor->IdRef;
    motor->pi_id.Ref = ramper(motor->IdRef, motor->pi_id.Ref, _IQ(0.0001));
    motor->pi_id.Fbk = motor->park.Ds;
    PI_MACRO(motor->pi_id)

// ------------------------------------------------------------------------------
//  Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
    motor->ipark.Ds = motor->pi_id.Out;   // motor->VdTesting
    motor->ipark.Qs = motor->pi_iq.Out ;  // motor->VqTesting
    motor->ipark.Sine   = motor->park.Sine;
    motor->ipark.Cosine = motor->park.Cosine;
    IPARK_MACRO(motor->ipark)

// ------------------------------------------------------------------------------
//  Connect inputs of the VOLT_CALC module and call the phase voltage calc. macro
// ------------------------------------------------------------------------------
    motor->volt.DcBusVolt = motor->voltageDC;
    motor->volt.MfuncV1 = motor->svgen.Ta;
    motor->volt.MfuncV2 = motor->svgen.Tb;
    motor->volt.MfuncV3 = motor->svgen.Tc;
    PHASEVOLT_MACRO(motor->volt)

// ------------------------------------------------------------------------------
//    Connect inputs of the SMO_POS module and call the sliding-mode observer macro
// ------------------------------------------------------------------------------
    motor->smo.Ialpha = motor->clarke.Alpha;
    motor->smo.Ibeta  = motor->clarke.Beta;
    motor->smo.Valpha = motor->volt.Valpha;
    motor->smo.Vbeta  = motor->volt.Vbeta;
    SMO_MACRO(motor->smo)

// ------------------------------------------------------------------------------
//    Connect inputs of the SPEED_EST module and call the estimated speed macro
// ------------------------------------------------------------------------------
    motor->speed1.EstimatedTheta = motor->smo.Theta;
    SE_MACRO(motor->speed1)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
    motor->svgen.Ualpha = motor->ipark.Alpha;
    motor->svgen.Ubeta  = motor->ipark.Beta;
    SVGENDQ_MACRO(motor->svgen)

// ------------------------------------------------------------------------------
//  Computed Duty and Write to CMPA register
// ------------------------------------------------------------------------------
    (motor->PwmARegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Ta)+INV_PWM_HALF_TBPRD;
    (motor->PwmBRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tb)+INV_PWM_HALF_TBPRD;
    (motor->PwmCRegs)->CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*motor->svgen.Tc)+INV_PWM_HALF_TBPRD;

// ------------------------------------------------------------------------------
//  Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
    DlogCh1 = motor->rg.Out;
    DlogCh2 = motor->smo.Theta;     // motor->currentAs;
    DlogCh3 = motor->clarke.As;  // motor->current.Bs;
    DlogCh4 = motor->clarke.Bs;  // motor->current.Cs;

//------------------------------------------------------------------------------
// Variable display on PWMDAC - available
//------------------------------------------------------------------------------
    PwmDacCh1 = _IQtoQ15(theta);            // Launchpad pin DAC1
    PwmDacCh2 = _IQtoQ15(motor->smo.Theta);         // Launchpad pin DAC2
    PwmDacCh3 = _IQtoQ15(motor->currentAs);         // Launchpad pin DAC3
    PwmDacCh4 = _IQtoQ15(motor->currentBs);         // Launchpad pin DAC4

//------------------------------------------------------------------------------
// Variable display on DAC - DAC-C not available
//------------------------------------------------------------------------------
//    dacAval = (Uint16) _IQtoQ12(motor->rg.Out);
//    dacBval = (Uint16) _IQtoQ12(motor->smo.Theta);
    dacAval = (Uint16) _IQtoQ11(motor->currentAs + _IQ(1));
    dacBval = (Uint16) _IQtoQ11(motor->currentBs + _IQ(1));

    return;
}
#endif

// ****************************************************************************
// ****************************************************************************
//TODO Motor Control ISR
// ****************************************************************************
// ****************************************************************************
interrupt void MotorControlISR(void)
{

	// Verifying the ISR
    IsrTicker++;


//    GPIO_TogglePin(TEMP_GPIO, IsrTicker%2);

#if (BUILDLEVEL == LEVEL1)

    BuildLevel1(&motor1);

#else
// ------------------------------------------------------------------------------
//  Measure phase currents and obtain position encoder (QEP) feedback
// ------------------------------------------------------------------------------
//    GPIO_WritePin(GPIO25,TRUE);
//    GPIO_WritePin(GPIO25,FALSE);
    motorCurrentSense();    //  Measure normalised phase currents (-1,+1)
    motorVoltageSense();    //  Measure normalised phase voltages (-1,+1)
    posEncoder(&motor1);    //  Motor 1 Position encoder

#if (BUILDLEVEL==LEVEL2)

	BuildLevel2(&motor1);

#elif (BUILDLEVEL==LEVEL3)

	BuildLevel3(&motor1);

#elif (BUILDLEVEL==LEVEL4)

	BuildLevel4(&motor1);

#elif (BUILDLEVEL==LEVEL5)

	BuildLevel5(&motor1);

#elif (BUILDLEVEL==LEVEL6)

    BuildLevel6(&motor1);

#elif (BUILDLEVEL==LEVEL7)

    BuildLevel7(&motor1);

#endif

#endif
//    GPIO_WritePin(GPIO25,FALSE);
    //clear ADCINT1 INT and ack PIE INT
	AdcbRegs.ADCINTFLGCLR.bit.ADCINT1=1;
	PieCtrlRegs.PIEACK.all=PIEACK_GROUP1;

}// MainISR Ends Here


/****************************************************************************
 * End of Code *
 * ***************************************************************************
 */
