/*
 * eeprom.h
 *
 *  Created on: 31 May 2024
 *      Author:
 */

#ifndef INCLUDE_BSP_EEPROM_H_
#define INCLUDE_BSP_EEPROM_H_

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

// EEPROM Start Addresses for
#define NODE_ID_ADDR_LOW             (0x0000)
#define NODE_ID_ADDR_HIGH            (0x0000)


void EEPROM_GetAll(void);

void EEPROM_GetNodeId(void);
void EEPROM_SetNodeId(Uint32 value);



#endif /* INCLUDE_BSP_EEPROM_H_ */
