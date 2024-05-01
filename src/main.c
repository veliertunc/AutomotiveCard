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
__interrupt void set_plus_isr(void);
__interrupt void set_minus_isr(void);

__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

void _initExtInterrupts(void);
void _initTimerInterrupts(void);
void InitInterrupts(void);

//
// Globals
//
volatile Uint32 set_plus_cnt;
volatile Uint32 set_minus_cnt;

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

//
// xint1_isr -
//
__interrupt void set_plus_isr(void)
{
    GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
    set_plus_cnt++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// xint2_isr -
//
__interrupt void set_minus_isr(void)
{
    GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
    set_minus_cnt++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

void InitInterrupts(void)
{
    _initExtInterrupts();


}

void _initExtInterrupts(void)
{
    EALLOW;
    // Write ISR functions to PIE Vector table
    PieVectTable.XINT1 = &set_plus_isr;
    PieVectTable.XINT1 = &set_minus_isr;
    EDIS;

    set_plus_cnt = 0; // Count XINT1 interrupts
    set_minus_cnt = 0;
    LoopCount = 0;  // Count times through idle loop

    //Enable groups and interrupts
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Group 1 INT4 (XInt1)
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Group 1 INT5 (XInt2)
    IER |= M_INT1;                              // Enable CPU INT1
    EINT;                                       // Enable Global Interrupts

    //
    // GPIO8(Set-) and GPIO17(Set+) are inputs
    //
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;        // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;         // input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 0;       // XINT1 Sync to SYSCLKOUT only

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;         // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;          // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = 0;        // XINT2 Sync to SYSCLKOUT only
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = 2;        // XINT2 Qual using 6 samples

    //
    // Each sampling window is 510*SYSCLKOUT
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0xFF;
    EDIS;


    EALLOW;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 17;   // XINT1 is GPIO17 -> Set +
    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 8;    // XINT2 is GPIO8 -> Set -
    EDIS;

    //
    // Configure XINT1
    //
    XIntruptRegs.XINT1CR.bit.POLARITY = 1;      // Rising edge interrupt
    XIntruptRegs.XINT2CR.bit.POLARITY = 1;      // Rising edge interrupt
    //
    // Enable XINT1 and XINT2
    //
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable XINT1
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2
    XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // Enable XINT3
}

void _initTimerInterrupts(void)
{
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &cpu_timer0_isr;
    PieVectTable.TINT1 = &cpu_timer1_isr;
    PieVectTable.TINT2 = &cpu_timer2_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize the Device Peripheral. This function can be
    //         found in DSP2803x_CpuTimers.c
    //
    InitCpuTimers();   // For this example, only initialize the Cpu Timers

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 60MHz CPU Freq, 1 second Period (in uSeconds)
    //
    ConfigCpuTimer(&CpuTimer0, 60, 1000000);
    ConfigCpuTimer(&CpuTimer1, 60, 1000000);
    ConfigCpuTimer(&CpuTimer2, 60, 1000000);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigCpuTimer and InitCpuTimers (in DSP2803x_CpuTimers.h), the
    // below settings must also be updated.
    //
    CpuTimer0Regs.TCR.all = 0x4000; //write-only instruction to set TSS bit = 0
    CpuTimer1Regs.TCR.all = 0x4000; //write-only instruction to set TSS bit = 0
    CpuTimer2Regs.TCR.all = 0x4000; //write-only instruction to set TSS bit = 0

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
    // which is connected to CPU-Timer 1, and CPU int 14, which is connected
    // to CPU-Timer 2:
    //
    IER |= M_INT1;
    IER |= M_INT13;
    IER |= M_INT14;

    //
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM
}

//
// cpu_timer0_isr - Timer0 counter
//
__interrupt void
cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;

   //
   // Acknowledge this interrupt to receive more interrupts from group 1
   //
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// cpu_timer1_isr - Timer1 counter
//
__interrupt void
cpu_timer1_isr(void)
{
   //
   // The CPU acknowledges the interrupt.
   //
   CpuTimer1.InterruptCount++;
}

//
// cpu_timer2_isr - Timer2 counter
//
__interrupt void
cpu_timer2_isr(void)
{
   //
   // The CPU acknowledges the interrupt.
   //
   CpuTimer2.InterruptCount++;
}


//
// End of File
//

