/*
 * can.h
 *
 *  Created on: 28 May 2024
 *      Author:
 */

#ifndef INCLUDE_DEVICE_CAN_H_
#define INCLUDE_DEVICE_CAN_H_

#include "DSP2803x_Device.h"     // DSP28 Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP28 Examples Include File
#include "typedefs.h"

void ECana_Transmit(Uint16 mbox_no, struct CANFrame msg);
void ECana_Receive(Uint16 mbox_no);


#endif /* INCLUDE_DEVICE_CAN_H_ */
