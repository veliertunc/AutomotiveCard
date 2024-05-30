/*
 * i2c.h
 *
 *  Created on: 28 May 2024
 *      Author:
 */

#ifndef INCLUDE_DEVICE_I2C_H_
#define INCLUDE_DEVICE_I2C_H_

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

// Slave address for CAV24C04 0101_0001 (0x51) (from 1010_A2A1a0)
#define EEPROM_SLAVE_ADDRESS       (0x0051)
#define I2C_NUMBYTES               (2)


__interrupt void i2c_int1a_isr(void);

void I2CA_Init(void);
void _initI2CInterrupts(void);

Uint16 I2CA_WriteData(struct I2CMSG *msg);
Uint16 I2CA_ReadData(struct I2CMSG *msg);

void I2C_Pass(void);
void I2C_Fail(void);

#endif /* INCLUDE_DEVICE_I2C_H_ */
