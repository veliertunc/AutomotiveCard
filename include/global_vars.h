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

extern Uint16 TruckSelect, PTOMode, RPMMode, SpeedMode;
extern bool IsCANBaudSelect, IsEmergency;
extern bool IsSetPlus, IsSetMinus;
extern bool IsMotorStart, IsMotorStop;
extern bool IsOpt1, IsOpt2, IsOpt3;

// External Interrupt Global variables
extern Uint32 idle_loop_count;
extern Uint32 set_plus_cnt;
extern Uint32 set_minus_cnt;

// Timer globals
extern struct CPUTIMER_VARS CpuTimer0,CpuTimer1,CpuTimer2;

// I2C Global variables
extern struct I2CMSG *I2cCurrentMsgPtr;		// used in interrupts
extern Uint16 I2cPassCount;
extern Uint16 I2cFailCount;
extern struct I2CMSG I2cMsgIn1;
extern struct I2CMSG I2cMsgOut1;

// CAN Global variables
extern struct CANFrame CANLastFrameReceived;

#endif /* INCLUDE_GLOBAL_VARS_H_ */
