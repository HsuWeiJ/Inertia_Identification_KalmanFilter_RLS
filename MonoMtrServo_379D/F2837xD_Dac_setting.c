/*
 *  F2837xD_Dac_setting.c
 *
 *  Created on: 2019¦~11¤ë15¤é
 *      Author: Jen
 */
#include "F2837xD_Dac_setting.h"


//
// Globals
//
volatile struct DAC_REGS* DAC_PTR[4] = {0x0,&DacaRegs,&DacbRegs,&DaccRegs};
Uint16 dacAval = 2048;
Uint16 dacBval = 2048;
Uint16 dacCval = 2048;


//
// configureDAC - Configure specified DAC output
//
void configureDAC(Uint16 dac_num)
{
    EALLOW;
    DAC_PTR[dac_num]->DACCTL.bit.DACREFSEL = REFERENCE;
    DAC_PTR[dac_num]->DACOUTEN.bit.DACOUTEN = 1;
    DAC_PTR[dac_num]->DACVALS.all = 0;
    DELAY_US(10); // Delay for buffered DAC to power up
    EDIS;
}
