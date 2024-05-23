/*
 * functions.h
 *
 *  Created on: Apr 26, 2024
 *      Author: Abdo Essa
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


#define VoltPin					0
#define AmpPin					1
#define ResPin					2
#define ACPin					3

#define SEL1Port				PORTD_ID
#define SEL1Pin					PIN0_ID

#define SEL2Port				PORTD_ID
#define SEL2Pin					PIN1_ID

#define VselPort				PORTD_ID
#define VselPin					PIN2_ID

#define Rsel0Port				PORTD_ID
#define Rsel0Pin				PIN6_ID

#define Rsel1Port				PORTD_ID
#define Rsel1Pin				PIN7_ID

#define ResetPort				PORTD_ID
#define ResetPin				PIN3_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


void Welcome(void);

void MainMenu(void);

void Invalid(void);

void TypeDetect(void);

void VoltRange(void);
void MyVoltameter(uint8 range);

void MyAmeter(void);

void MyOhmeter();

void ACType(void);
void MyACmeter(uint8 type);

void Voltmeter10Set(void);
void Voltmeter20Set(void);

void AmeterSet(void);

void OhmeterSet(void);

void SetReset();

void SetPullUp();

void ISR_Toggle();


#endif /* FUNCTIONS_H_ */
