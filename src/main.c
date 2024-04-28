//###########################################################################
//
// FILE:   Example_2803x_Pinmux.c
//
// TITLE:  Empty Pinmux Project
//
//!  \addtogroup f2806x_example_list
//!  <h1>Empty Pinmux</h1>
//		
//#############################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Function Prototype
//
__interrupt void xint1_isr(void);
__interrupt void xint5_isr(void);
__interrupt void xint6_isr(void);
__interrupt void xint8_isr(void);
__interrupt void xint9_isr(void);
__interrupt void xint10_isr(void);
__interrupt void xint12_isr(void);

void InitInterrupts(void);

//
// Globals
//
volatile Uint32 Xint1Count;
volatile Uint32 Xint5Count;
volatile Uint32 Xint8Count;
volatile Uint32 Xint9Count;
volatile Uint32 Xint10Count;
volatile Uint32 Xint12Count;
Uint32 LoopCount;

//
// Defines
//
#define DELAY (CPU_RATE/1000*6*510)  //Qual period at 6 samples

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO: 
    //
    //InitGpio();
    InitECanGpio();
    InitSciGpio();
    InitI2CGpio();
    
    //
    // Step 3. Initalize CAN:
    //
    InitECan();

    //
    // Step 4. Initalize UART:
    //
    InitSci();

    //
    // Step 6. Initalize I2C:
    //
    InitI2C();

    //
    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts 
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.  
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt 
    // Service Routines (ISR).  
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    //
    InitPieVectTable();

    InitInterrupts();

    for(;;)
    {
        
    }
}

__interrupt void xint1_isr(void)
{
    Xint1Count++;
    //Differentiate which external interrupt occured. (XINT1 or XINT2)
    //
    // Acknowledge this interrupt to get more from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void xint5_isr(void)
{
    Xint5Count++;

    //
    // Acknowledge this interrupt to get more from group 5
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

__interrupt void xint8_isr(void)
{
    Xint8Count++;

    //
    // Acknowledge this interrupt to get more from group 8
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

__interrupt void xint9_isr(void)
{
    Xint9Count++;

    //
    // Acknowledge this interrupt to get more from group 9
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

__interrupt void xint10_isr(void)
{
    Xint10Count++;

    //
    // Acknowledge this interrupt to get more from group 10
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}

__interrupt void xint12_isr(void)
{
    Xint12Count++;

    //
    // Acknowledge this interrupt to get more from group 12
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}



void InitInterrupts(void)
{
    EALLOW;
    // Write ISR functions to PIE Vector table
    PieVectTable.XINT1 = &xint1_isr;
    EDIS;
    Xint1Count = 0; // Count XINT1 interrupts
    Xint5Count = 0;
    Xint8Count = 0;
    Xint9Count = 0;
    Xint10Count = 0;
    Xint12Count = 0;
    LoopCount = 0;  // Count times through idle loop

    //Enable groups and interrupts
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Group 1 INT4 (XInt1)
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Group 1 INT5 (XInt2)

    PieCtrlRegs.PIEIER5.bit.INTx1 = 1;          // Enable PIE Group 5 INT1 (QEP)

    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;          // Enable PIE Group 8 INT1 (I2CINT1A)
    PieCtrlRegs.PIEIER8.bit.INTx2 = 1;          // Enable PIE Group 8 INT2 (I2CINT2A)

    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;          // Enable PIE Group 9 INT1 (SCIRXINTA)
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1;          // Enable PIE Group 9 INT2 (SCITXINTA)
    PieCtrlRegs.PIEIER9.bit.INTx5 = 1;          // Enable PIE Group 9 INT5 (ECANA_INT0)
    PieCtrlRegs.PIEIER9.bit.INTx6 = 1;          // Enable PIE Group 9 INT6 (ECANA_INT1)

    PieCtrlRegs.PIEIER10.all = 0xFFFF;          // Enable PIE Group 10 All ADCs

    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;         // Enable PIE Group 12 INT1 (XINT3)

    IER |= M_INT1;                              // Enable CPU INT1
    EINT;                                       // Enable Global Interrupts

    EALLOW;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0;   // XINT1 is GPIO0
    //GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 1;   // XINT2 is GPIO1
    //GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 2;   // XINT3 is GPIO2
    EDIS;

    //
    // Configure XINT1
    //
    XIntruptRegs.XINT1CR.bit.POLARITY = 1;      // Rising edge interrupt

    //
    // Enable XINT1 and XINT2
    //
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable XINT1
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2
    XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // Enable XINT3
}

//
// End of File
//

