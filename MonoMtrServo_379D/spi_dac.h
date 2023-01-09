

//#define SINE_WAVE_VERTICAL_RESOLUTION 63  // (2^N-1)
//unsigned int DAC_RESOLUTION_in_LSB = 4096;			// (2^N)
//unsigned int SINE_DATA[SINE_WAVE_VERTICAL_RESOLUTION];
//
//float multiper;
//
//void SINE_WAVE_INIT(void)
//{
//	int i;
//
//	for(i=1;i<=SINE_WAVE_VERTICAL_RESOLUTION;i++)
//		SINE_DATA[i-1] = (sin(i/SINE_WAVE_VERTICAL_RESOLUTION)+1)*(DAC_RESOLUTION_in_LSB/2);
//
//}

  #define SPIDAC_SET_LDAC       GpioDataRegs.GPCSET.bit.GPIO66   = 1
  #define SPIDAC_CLEAR_LDAC     GpioDataRegs.GPCCLEAR.bit.GPIO66 = 0


// SPIDAC
void SPIDAC_setup()
{


//   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;	// SPI-A
   //CpuSysRegs.PCLKCR8.all |= 0x01;
    CpuSysRegs.PCLKCR8.bit.SPI_B = 0x01;
/*
   EALLOW;
   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;	// 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
   GpioCtrlRegs.GPADIR.bit.GPIO16  = 1;	// 1=OUTput,  0=INput
   GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;	// 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ3
   GpioCtrlRegs.GPADIR.bit.GPIO17  = 0;	// 1=OUTput,  0=INput
   GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;	// 0=GPIO,  1=SPICLK-A,  2=LINTX-A,  3=XCLKOUT
   GpioCtrlRegs.GPADIR.bit.GPIO18  = 1;	// 1=OUTput,  0=INput
   GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;	// 0=GPIO,  1=SPISTE-A,  2=LINRX-A,  3=ECAP1
   GpioCtrlRegs.GPADIR.bit.GPIO19  = 1;	// 1=OUTput,  0=INput
   EDIS;
*/

  // Setup the SPI CCR register
  SpibRegs.SPICCR.bit.SPISWRESET = 0;
  SpibRegs.SPICCR.bit.CLKPOLARITY = 1;
  SpibRegs.SPICCR.bit.SPILBK = 0;
  SpibRegs.SPICCR.bit.SPICHAR = 0xf;


  // Setup the SPI CTL register
  SpibRegs.SPICTL.bit.OVERRUNINTENA = 0;
  SpibRegs.SPICTL.bit.CLK_PHASE = 1;
  SpibRegs.SPICTL.bit.MASTER_SLAVE = 1;
  SpibRegs.SPICTL.bit.TALK = 1;
  SpibRegs.SPICTL.bit.SPIINTENA = 0;
 // Initialize the SPI BRR (Baud Rate Register) to 1 Mb
  SpibRegs.SPIBRR.all = 3;//5;  //  reduce -> increase clock


  // Setup the SPI FIFO TX path
  SpibRegs.SPIFFTX.bit.SPIRST = 0;
  SpibRegs.SPIFFTX.bit.SPIFFENA = 1;
  SpibRegs.SPIFFTX.bit.TXFIFO = 1;
  SpibRegs.SPIFFTX.bit.TXFFIENA = 0;
  SpibRegs.SPIFFTX.bit.SPIRST = 1;

    // Setup the SPI FIFO RX path
  SpibRegs.SPIFFRX.bit.RXFIFORESET = 0;
  SpibRegs.SPIFFRX.bit.RXFFIENA = 0;
  SpibRegs.SPIFFRX.bit.RXFIFORESET = 1;

    // Setup the SPI FIFO CTL
  SpibRegs.SPIFFCT.bit.TXDLY = 1;  // reduce for more channel

  // Take the SPI port out of reset
  SpibRegs.SPICCR.bit.SPISWRESET = 1;

  // Setup the SPI priority register
  SpibRegs.SPIPRI.bit.FREE = 1;
  //SpiaRegs.SPIPRI.bit.STEINV = 0;
  //SpiaRegs.SPIPRI.bit.TRIWIRE = 0;

  // Set the LDAC pin high

  SPIDAC_SET_LDAC;

}




void SPIDAC_xmit_u16(unsigned int data)
{
	unsigned int volatile v;
//	int volatile i, j;

	do
	  {	v = SpibRegs.SPIFFTX.bit.TXFFST; }	while (v == 4);

	SpibRegs.SPITXBUF = data;

	do	// wait for the transmit FIFO to clear
	  {	v = SpibRegs.SPIFFTX.bit.TXFFST; }	while (v > 0);


	do	// wait for the transmit buffer to clear
	  {	v = SpibRegs.SPISTS.bit.BUFFULL_FLAG; }	while (v);

//	for (i=0; i<10; i++)
//		j+=i;
}




void SPIDAC_write_dac_channel(int ch, unsigned int data)
{
	unsigned int v;

	data &= 0xfff; ch &= 0x3; v=data|(ch<<14)|(1<<12);

	SPIDAC_xmit_u16(v);
}

void SPIDAC_update_all()
{
	SPIDAC_CLEAR_LDAC;
	SPIDAC_SET_LDAC;
}
