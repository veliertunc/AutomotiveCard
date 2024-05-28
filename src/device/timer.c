//###########################################################################
//
// FILE:	DSP2803x_CpuTimers.c
//
// TITLE:	CPU 32-bit Timers Initialization & Support Functions.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "DSP2803x_Device.h"     // Headerfile Include File
#include "DSP2803x_Examples.h"   // Examples Include File
#include "timer.h"

//
// Globals
//
struct CPUTIMER_VARS CpuTimer0,CpuTimer1,CpuTimer2;
//
// InitCpuTimers - This function initializes all three CPU timers
// to a known state.
//
void InitCpuTimers(void)
{
    // CPU Timer 0,1,2
    // Initialize address pointers to respective timer registers
    CpuTimer0.RegsAddr = &CpuTimer0Regs;
    CpuTimer1.RegsAddr = &CpuTimer1Regs;
    CpuTimer2.RegsAddr = &CpuTimer2Regs;

    // Initialize timer period to maximum
    CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
    CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
    CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;

    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all = 0;

    CpuTimer1Regs.TPR.all  = 0;
    CpuTimer1Regs.TPR.all  = 0;

    CpuTimer2Regs.TPRH.all = 0;
    CpuTimer2Regs.TPRH.all = 0;

    // Make sure timer is stopped
    CpuTimer0Regs.TCR.bit.TSS = 1;
    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;

    // Reload all counter register with period value
    CpuTimer0Regs.TCR.bit.TRB = 1;
    CpuTimer1Regs.TCR.bit.TRB = 1;
    CpuTimer2Regs.TCR.bit.TRB = 1;

    // Reset interrupt counters
    CpuTimer0.InterruptCount = 0;
    CpuTimer1.InterruptCount = 0;
    CpuTimer2.InterruptCount = 0;
}

//
// ConfigCpuTimer - This function initializes the selected timer to the period
// specified by the "Freq" and "Period" parameters. The "Freq" is entered
// as "MHz" and the "Period" in "uSeconds". The timer is held in the stopped 
// state after configuration.
//
void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period)
{
    Uint32     PeriodInClocks;
    
    // Initialize timer period
    Timer->CPUFreqInMHz = Freq;
    Timer->PeriodInUSec = Period;
    PeriodInClocks = (long) (Freq * Period);
    
    // Counter decrements PRD+1 times each period
    Timer->RegsAddr->PRD.all = PeriodInClocks - 1;
    
    // Set pre-scale counter to divide by 1 (SYSCLKOUT)
    Timer->RegsAddr->TPR.all  = 0;
    Timer->RegsAddr->TPRH.all  = 0;
    
    // Initialize timer control register

    // 1 = Stop timer, 0 = Start/Restart Timer    
    Timer->RegsAddr->TCR.bit.TSS = 1;
    
    Timer->RegsAddr->TCR.bit.TRB = 1;       // 1 = reload timer
    Timer->RegsAddr->TCR.bit.SOFT = 0;
    Timer->RegsAddr->TCR.bit.FREE = 0;      // Timer Free Run Disabled
    
    // 0 = Disable/ 1 = Enable Timer Interrupt
    Timer->RegsAddr->TCR.bit.TIE = 1;   
    
    // Reset interrupt counter
    Timer->InterruptCount = 0;
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
    // 60MHz CPU Freq, 1 second, 250ms and 100ms respectively Period (in uSeconds)
    //
    ConfigCpuTimer(&CpuTimer0, 60, 1000000);
    ConfigCpuTimer(&CpuTimer1, 60, 250000);
    ConfigCpuTimer(&CpuTimer2, 60, 100000); // Will be used for CAN bus data send

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
// cpu_timer0_isr - Timer0 counter (1s)
//
__interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;

   //
   // Acknowledge this interrupt to receive more interrupts from group 1
   //
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// cpu_timer1_isr - Timer1 counter (250ms)
//
__interrupt void cpu_timer1_isr(void)
{
   //
   // The CPU acknowledges the interrupt.
   //
   CpuTimer1.InterruptCount++;
}

//
// cpu_timer2_isr - Timer2 counter (100ms)
//
__interrupt void cpu_timer2_isr(void)
{
   //
   // The CPU acknowledges the interrupt.
   //
   CpuTimer2.InterruptCount++;
}


//
// End of File
//
