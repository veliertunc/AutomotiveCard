/*
 * timer.h
 *
 *  Created on: 28 May 2024
 *      Author: veli.ertunc
 */

#ifndef INCLUDE_DEVICE_TIMER_H_
#define INCLUDE_DEVICE_TIMER_H_

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

void _initTimerInterrupts(void);



#endif /* INCLUDE_DEVICE_TIMER_H_ */
