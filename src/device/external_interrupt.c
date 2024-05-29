/*
 * external_interrupt.c
 *
 *  Created on: 28 May 2024
 */
#include "external_interrupt.h"
#include "global_vars.h"

void _initExtInterrupts(void)
{
    EALLOW;
    // Write ISR functions to PIE Vector table
    PieVectTable.XINT1 = &set_plus_isr;
    PieVectTable.XINT2 = &set_minus_isr;
    EDIS;

    set_plus_cnt = 0; // Count XINT1 interrupts
    set_minus_cnt = 0;
    idle_loop_count = 0;  // Count times through idle loop

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

__interrupt void set_plus_isr(void)
{
    GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
    set_plus_cnt++;

    // Call the API to send Set + msg from CAN bus

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void set_minus_isr(void)
{
    GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
    set_minus_cnt++;

    // Call the API to send Set - msg from CAN bus

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

