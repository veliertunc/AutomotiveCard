/*
 * typedefs.h
 *
 *  Created on: 29 May 2024
 *      Author:
 */

#ifndef INCLUDE_TYPEDEFS_H_
#define INCLUDE_TYPEDEFS_H_

#include <stdbool.h>
#include "DSP2803x_Device.h"     // DSP28 Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP28 Examples Include File

struct CANFrame {
    Uint32 ID; // Message identifier
    bool IsRTR; // Is remote request frame
    Uint16 DLC; // DLC
    Uint32 LowBytes; // byte 0-3
    Uint32 HighBytes; // byte 4-7
};

#endif /* INCLUDE_TYPEDEFS_H_ */
