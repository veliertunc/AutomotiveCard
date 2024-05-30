/*
 * api.h
 *
 *  Created on: 30 May 2024
 *      Author:
 */

#ifndef INCLUDE_API_API_H_
#define INCLUDE_API_API_H_

void API_OnEmergency(void); // Emergency
void API_IncreaseSpeed(void); // Set +
void API_DecreaseSpeed(void); // Set -
void API_StartMotor(void); // Motor Start
void API_StopMotor(void); // Motor Stop

// Activates PTOx
// Options: None, PTO1, PTO2 or NMV (Depends on the vehicle)
void API_ActivatePTO(void);

// Selects one of the predefined motor rotation limits
// Options: None, Limit1, Limit2, Limit3 (May vary for each vehicle)
void API_SelectRPMLimit(void);

// Selects one of the predefined vehicle speed limits
// Options: None, Limit1, Limit2, Limit3 (May vary for each vehicle)
void API_SelectSpeedLimit(void);

#endif /* INCLUDE_API_API_H_ */
