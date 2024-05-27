/*
 * main.h
 *
 *  Created on: 27 May 2024
 *      Author:
 */

#ifndef INCLUDE_MAIN_H_
#define INCLUDE_MAIN_H_

// Included Files
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "f2803x_pinmux.h"
#include <stdint.h>
#include <stdbool.h>
// Defines
#define DELAY (CPU_RATE/1000*6*510)  //Qual period at 6 samples

// Function Prototype
__interrupt void set_plus_isr(void);
__interrupt void set_minus_isr(void);

__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

void _initExtInterrupts(void);
void _initTimerInterrupts(void);
void InitInterrupts(void);

void HandleGPIOs(void);

#endif /* INCLUDE_MAIN_H_ */
