/*
 * gpio.h
 *
 *  Created on: 28 May 2024
 *      Author:
 */

#ifndef INCLUDE_DEVICE_GPIO_H_
#define INCLUDE_DEVICE_GPIO_H_

#include <stdbool.h>
#include <stdint.h>
#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File


void ReadGPIO(void);
void HandleGPIOs(void);

#endif /* INCLUDE_DEVICE_GPIO_H_ */
