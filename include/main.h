/*
 * main.h
 *
 *  Created on: 27 May 2024
 *      Author:
 */

#ifndef INCLUDE_MAIN_H_
#define INCLUDE_MAIN_H_

// Included Files
#include <stdint.h>
#include <stdbool.h>

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "f2803x_pinmux.h"

#include "timer.h"
#include "gpio.h"
#include "external_interrupt.h"
#include "i2c.h"
// Defines
#define DELAY (CPU_RATE/1000*6*510)  //Qual period at 6 samples

// Function Prototype

void InitInterrupts(void);


#endif /* INCLUDE_MAIN_H_ */
