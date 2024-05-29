/*
 * global_vars.h
 *
 *  Created on: 29 May 2024
 *      Author:
 */

#ifndef INCLUDE_GLOBAL_VARS_H_
#define INCLUDE_GLOBAL_VARS_H_
#include "typedefs.h"
// GPIO Global variables

volatile Uint16 TruckSelect = 0, PTOMode = 0, RPMMode = 0, SpeedMode = 0;
volatile bool IsCANBaudSelect = false, IsEmergency = false;
volatile bool IsSetPlus = false, IsSetMinus = false;
volatile bool IsMotorStart = false, IsMotorStop = false;
volatile bool IsOpt1 = false, IsOpt2 = false, IsOpt3 = false;

// External Interrupt Global variables
Uint32 idle_loop_count;
volatile Uint32 set_plus_cnt;
volatile Uint32 set_minus_cnt;

// I2C Global variables
struct I2CMSG *I2cCurrentMsgPtr;		// used in interrupts
Uint16 I2cPassCount;
Uint16 I2cFailCount;
struct I2CMSG I2cMsgIn1;
struct I2CMSG I2cMsgOut1;

// CAN Global variables
struct CANFrame CANLastFrameReceived;

#endif /* INCLUDE_GLOBAL_VARS_H_ */
