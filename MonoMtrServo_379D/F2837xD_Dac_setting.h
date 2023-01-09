/*
 *  F2837xD_Dac_setting.h
 *
 *  Created on: 2019¦~11¤ë15¤é
 *      Author: Jen
 */

#ifndef F2837XD_DAC_SETTING_H_
#define F2837XD_DAC_SETTING_H_


#include "F28x_Project.h"

//
// Globals
//
extern volatile struct DAC_REGS* DAC_PTR[4];
extern Uint16 dacAval;
extern Uint16 dacBval;
extern Uint16 dacCval;

//
// Defines
//
#define REFERENCE_VDAC      0
#define REFERENCE_VREF      1
#define DACA         1
#define DACB         2
#define DACC         3
#define REFERENCE            REFERENCE_VREF
#define DAC_NUM                DACA



//
// Function Prototypes
//
extern void configureDAC(Uint16 dac_num);


#endif /* F2837XD_DAC_H_ */
