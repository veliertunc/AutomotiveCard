//###########################################################################
//
// FILE:	DSP2803x_I2C.c
//
// TITLE:	DSP2803x I2C Initialization & Support Functions.
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
#include "i2c.h"
#include "global_vars.h"
//
// InitI2C - This function initializes the I2C to a known state.
//
void InitI2C(void)
{
    //
    // Initialize I2C-A:
    //
    I2CA_Init();
}

//
// InitI2CGpio - This function initializes GPIO pins to function as I2C pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for SDAA operation.
// Only one GPIO pin shoudl be enabled for SCLA operation.
// Comment out other unwanted lines.
//
void InitI2CGpio()
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SDAA)
    //GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCLA)
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up for GPIO32 (SDAA)
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;	// Enable pull-up for GPIO33 (SCLA)

    //
    // Set qualification for selected pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SDAA)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (SCLA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // Asynch input GPIO32 (SDAA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // Asynch input GPIO33 (SCLA)

    //
    // Configure I2C pins using GPIO regs
    // This specifies which of the possible GPIO pins will be I2C functional 
    // pins. Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 2;   //Configure GPIO28 for SDAA
    //GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 2;   //Configure GPIO29 for SCLA
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1; //Configure GPIO32 for SDAA
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1; //Configure GPIO33 for SCLA

    EDIS;
}


__interrupt void i2c_int1a_isr(void)
{
    Uint16 IntSource, i;

    // Read interrupt source
    IntSource = I2caRegs.I2CISRC.all;
    // Interrupt source = stop condition detected
    if (IntSource == I2C_SCD_ISRC) {
       if (I2cCurrentMsgPtr->MsgStatus == I2C_MSGSTAT_WRITE_BUSY) {
           I2cCurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
       } else {
           // If a message receives a NACK during the address setup portion
           // of the EEPROM read, the code further below included in the
           // register access ready interrupt source code will generate a stop
           // condition. After the stop condition is received (here), set the
           // message status to try again. User may want to limit the number
           // of retries before generating an error.
           if (I2cCurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY) {
              I2cCurrentMsgPtr->MsgStatus = I2C_MSGSTAT_SEND_NOSTOP;
           } else if (I2cCurrentMsgPtr->MsgStatus == I2C_MSGSTAT_READ_BUSY){
               // If completed message was reading EEPROM data, reset msg to
               // inactive state and read data from FIFO.
               I2cCurrentMsgPtr->MsgStatus == I2C_MSGSTAT_INACTIVE;
               for (i = 0; i < I2C_NUMBYTES; ++i) {
                   I2cCurrentMsgPtr->MsgBuffer[i] = I2caRegs.I2CDRR;

                   if(I2cMsgIn1.MsgBuffer[i] == I2cMsgOut1.MsgBuffer[i])
                   { I2C_PassCount++; }
                   else { I2C_FailCount++; }
               }

               if (I2C_PassCount==I2C_NUMBYTES)
               { I2C_Pass(); }
               else { I2C_Fail(); }

           }
       }
    }
    else if(IntSource == I2C_ARDY_ISRC)
    {
        // Interrupt source = Register Access Ready
        // This interrupt is used to determine when the EEPROM address setup
        // portion of the read data communication is complete. Since no stop bit is
        // commanded, this flag tells us when the message has been sent instead of
        // the SCD flag. If a NACK is received, clear the NACK bit and command a
        // stop. Otherwise, move on to the read data portion of the communication.
        if (I2caRegs.I2CSTR.bit.NACK) {
            I2caRegs.I2CMDR.bit.STP = 1;
            I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
        } else if (I2cCurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY) {
            I2cCurrentMsgPtr->MsgStatus = I2C_MSGSTAT_RESTART;
        }
    }
    else {
        // Generate some error due to interrupt source
        ;
    }
    //Enable future I2C (PIE Group 8) interrupts
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}


void _initI2CInterrupts(void)
{
    EALLOW;
    PieVectTable.I2CINT1A = &i2c_int1a_isr;
    EDIS;
    // Enable I2C interrupt 1 in the PIE: Group 8 interupt 1
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
    // Enable CPU INT8 which is connected to PIE group 8
    IER |= M_INT8;
    EINT;
}

void I2CA_Init(void)
{
    I2caRegs.I2CSAR = SLAVE_ADDRESS;   // Slave address - EEPROM cont

    I2caRegs.I2CPSC.all = 6;        // Prescaler - need 7-12 Mhz on module clk
    I2caRegs.I2CCLKL = 10;          // NOTE: must be non zero
    I2caRegs.I2CCLKH = 5;           // NOTE: must be non zero
    I2caRegs.I2CIER.all = 0x24;	    // Enable SCD & ARDY interrupts

    I2caRegs.I2CMDR.all = 0x0020;   // Take I2C out of reset
                                    // Stop I2C when suspended

    I2caRegs.I2CFFTX.all = 0x6000;  // Enable FIFO mode and TXFIFO
    I2caRegs.I2CFFRX.all = 0x2040;  // Enable RXFIFO, clear RXFFINT,
}

Uint16 I2CA_WriteData(struct I2CMSG *msg)
{
    Uint16 i;

    // Wait until STP bit is cleared from any previous master communication. Clearing of this bit by the module is delayed until after the SCD bit is
    // set. If this bit is not checked prior to initiating a new message, the
    // I2C could get confused.

    if(I2caRegs.I2CMDR.bit.STP){
        return I2C_STP_NOT_READY_ERROR;
    }

    // Setup slave address
    I2caRegs.I2CSAR = msg->SlaveAddress;
    // Check if bus busy
    if (I2caRegs.I2CSTR.bit.BB) {
        return I2C_BUS_BUSY_ERROR;
    }
    // Setup num of bytes to send
    // MsgBuffer + Address
    I2caRegs.I2CCNT = msg->NumOfBytes;
    // Setup data to send
    I2caRegs.I2CDXR = msg->MemoryHighAddr;
    I2caRegs.I2CDXR = msg->MemoryLowAddr;
    for (i = 0; i < msg->NumOfBytes; ++i) {
        I2caRegs.I2CDXR = *(msg->MsgBuffer+i);
    }
    // Send start as master
    I2caRegs.I2CMDR.all = 0x6E20;

    return I2C_SUCCESS;

}

Uint16 I2CA_ReadData(struct I2CMSG *msg)
{

    // Wait until STP bit is cleared from any previous master communication.
    // Clearing of this bit by the module is delayed until after the SCD bit is
    // set. If this bit is not checked prior to initiating a new message, the
    // I2C could get confused.
    if (I2caRegs.I2CMDR.bit.STP) {
        return I2C_STP_NOT_READY_ERROR;
    }
    I2caRegs.I2CSAR = msg->SlaveAddress;

    if (msg->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP) {
        // Check if bus heavy
        I2caRegs.I2CCNT = 2;
        I2caRegs.I2CDXR = msg->MemoryHighAddr;
        I2caRegs.I2CDXR = msg->MemoryLowAddr;
        I2caRegs.I2CMDR.all = 0x2620; // Send data to setup EEPROM address

    } else if(msg->MsgStatus == I2C_MSGSTAT_RESTART){
       I2caRegs.I2CCNT = msg->NumOfBytes; // Setup up how many bytes to expect
       I2caRegs.I2CMDR.all = 0x2C20; // Send restart as master receiver
    }

    return I2C_SUCCESS;
}

void I2C_Pass()
{
}

void I2C_Fail()
{
}




//
// End of file
//
