//###########################################################################
//
// FILE:	DSP2803x_Gpio.c
//
// TITLE:	DSP2803x General Purpose I/O Initialization & Support Functions.
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
#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File
#include "gpio.h"
#include <stdbool.h>
#include <stdint.h>

extern volatile Uint8 TruckSelect = 0, PTOMode = 0, RPMMode = 0, SpeedMode = 0;
extern volatile bool IsCANBaudSelect = false, IsEmergency = false;
extern volatile bool IsSetPlus = false, IsSetMinus = false;
extern volatile bool IsMotorStart = false, IsMotorStop = false;
extern volatile bool IsOpt1 = false, IsOpt2 = false, IsOpt3 = false;


//
// InitGpio - This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example.
//
void InitGpio(void)
{
    EALLOW;

    //
    // Each GPIO pin can be:
    // a) a GPIO input/output
    // b) peripheral function 1
    // c) peripheral function 2
    // d) peripheral function 3
    // By default, all are GPIO Inputs
    //
    GpioCtrlRegs.GPAMUX1.all = 0x0000;   // GPIO functionality GPIO0-GPIO15
    GpioCtrlRegs.GPAMUX2.all = 0x0000;   // GPIO functionality GPIO16-GPIO31
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0x01;     // CANTXA
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0x01;     // CANRXA
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0x01;     // SCITXA
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0x01;     // SCIRXA
    GpioCtrlRegs.GPBMUX1.all = 0x0000;   // GPIO functionality GPIO32-GPIO44
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0x01;     //SCLA
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0x01;     //SDAA
    //
    // Dig.IO funct. applies to AIO2,4,6,10,12,14
    //
    GpioCtrlRegs.AIOMUX1.all = 0x0000;     

    GpioCtrlRegs.GPADIR.all = 0x0000;   // GPIO0-GPIO31 are GP inputs
    GpioCtrlRegs.GPBDIR.all = 0x0000;   // GPIO32-GPIO44 are inputs
    GpioCtrlRegs.AIODIR.all = 0x0000;   // AIO2,4,6,19,12,14 are digital inputs

    //
    // Each input can have different qualification
    // a) input synchronized to SYSCLKOUT
    // b) input qualified by a sampling window
    // c) input sent asynchronously (valid for peripheral inputs only)
    //
    GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
    GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO44 Synch to SYSCLKOUT

    //
    // Pull-ups can be enabled or disabled.
    //
    //GpioCtrlRegs.GPAPUD.all = 0x0000;      // Pullup's enabled GPIO0-GPIO31
    //GpioCtrlRegs.GPBPUD.all = 0x0000;      // Pullup's enabled GPIO32-GPIO44
    GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
    GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO44
    EDIS;
}

void ReadGPIO(void)
{
    // Note: GPADAT -> GPIO0-GPIO31, GPBDAT -> GPIO32-GPIO44

    // Set + and Set - are external interrupts
    // Set + button - GPIO17
    // IsSetPlus = (Uint8) GpioDataRegs.GPADAT.bit.GPIO17;
    // Set -  button - GPIO8
    // IsSetMinus = (Uint8) GpioDataRegs.GPADAT.bit.GPIO8;

    // CAN baudrate select - GPIO22
    IsCANBaudSelect = (bool) GpioDataRegs.GPADAT.bit.GPIO22;
   // Emergency button GPIO18
    IsEmergency = (bool) GpioDataRegs.GPADAT.bit.GPIO18;
    // Motor Start button - GPIO16
    IsMotorStart = (bool) GpioDataRegs.GPADAT.bit.GPIO16;
    // Motor Stop button - GPIO12
    IsMotorStop = (bool) GpioDataRegs.GPADAT.bit.GPIO12;
    // Optional input 1 - GPIO1
    IsOpt1 = (bool) GpioDataRegs.GPADAT.bit.GPIO1;
    // Optional input 2 - GPIO0
    IsOpt2 = (bool) GpioDataRegs.GPADAT.bit.GPIO0;
    // Optional input 3 - GPIO23
    IsOpt3 = (bool) GpioDataRegs.GPADAT.bit.GPIO23;

    // Truck select - GPIO20,21,24
    TruckSelect = (Uint8) (GpioDataRegs.GPADAT.bit.GPIO24 |
            GpioDataRegs.GPADAT.bit.GPIO21 | GpioDataRegs.GPADAT.bit.GPIO20);
    // PTO mode - GPIO7,6
    PTOMode = (Uint8) (GpioDataRegs.GPADAT.bit.GPIO7 | GpioDataRegs.GPADAT.bit.GPIO6);
    // RPM mode - GPIO19,11,4
    RPMMode = (Uint8) (GpioDataRegs.GPADAT.bit.GPIO19 |
            GpioDataRegs.GPADAT.bit.GPIO11 | GpioDataRegs.GPADAT.bit.GPIO4);
    // Speed mode - GPIO10,3,2
    SpeedMode = (Uint8) (GpioDataRegs.GPADAT.bit.GPIO10 |
            GpioDataRegs.GPADAT.bit.GPIO3 | GpioDataRegs.GPADAT.bit.GPIO2);

}

void HandleGPIOs(void)
{
    // Note: GPADAT -> GPIO0-GPIO31, GPBDAT -> GPIO32-GPIO44

    if (IsEmergency) {
        // Stop EVERYTHING, EVERYTHING!!!!!!!!!!!
        ;
    } else {
        if (IsMotorStart && !IsMotorStop) {
            ;
        } else {
            // IsMotorStart && IsMotorStop or
            // !IsMotorStart && IsMotorStop or
            // !IsMotorStart && !IsMotorStop

            // Stop the motor
            ;
        }

       if(IsOpt1) {;} else {;}
       if(IsOpt2) {;} else {;}
       if(IsOpt3) {;} else {;}

    }
}



//
// End of file
//

