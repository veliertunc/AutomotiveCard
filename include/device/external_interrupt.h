/*
 * external_interrupt.h
 *
 *  Created on: 28 May 2024
 *      Author:
 */

#ifndef INCLUDE_DEVICE_EXTERNAL_INTERRUPT_H_
#define INCLUDE_DEVICE_EXTERNAL_INTERRUPT_H_

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

__interrupt void set_plus_isr(void);
__interrupt void set_minus_isr(void);

void _initExtInterrupts(void);

#endif /* INCLUDE_DEVICE_EXTERNAL_INTERRUPT_H_ */
