//----------------------------------------------------------------------------------
//	FILE:			MonoMtrServo.h
//
//	Description:	Header file for Single motor control with 37xS launch pad
//
//	Version: 		1.0
//
//  Target:  		TMS320F28377S
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments � 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// 4 Nov 2015 - Mono motor include file list
//----------------------------------------------------------------------------------


#ifndef MONOMTRSERVO_H_
#define MONOMTRSERVO_H_

#include "F2837xD_IO_assignment.h"
#include "MonoMtrServo-Settings.h"
/*-------------------------------------------------------------------------------
Include project specific include files.
-------------------------------------------------------------------------------*/
// define math type as float(1)
#define   MATH_TYPE      1
#include "IQmathLib.h"
#include "F28x_Project.h"
#include "motorVars.h"
#include "config.h"
#include <math.h>

#include "DRV830x_SPI.h"
#include "drv8301.h"
#include "drv8305.h"

#include "DLOG_4CH_F.h"
#include "f2837xpwmdac_PM.h"
#include "F2837xD_Dac_setting.h"
#include "spi_dac.h"
#include "SpeedLoop.h"
#include "Filter.h"
#include "KalmanFilter_RLS.h"
#include "dsp.h"
#include "fpu32/fpu_vector.h"

#endif /* MONOMTRSERVO_H_ */
