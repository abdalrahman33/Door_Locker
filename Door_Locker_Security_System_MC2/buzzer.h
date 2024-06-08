/*
 * buzzer.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Abdelrahman Salem
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* DC Motor Driver HW Ports and Pins Ids */

#define BUZZER_PORT_ID      PORTC_ID
#define BUZZER_PIN1_ID      PIN3_ID
#define BUZZER_PIN2_ID  	PIN4_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Buzzer:
 */
void Buzzer_init(void);

/*
 * Description :
 * Turn ON Buzzer
 */
void Buzzer_on(void);

/*
 * Description :
 * Turn OFF Buzzer
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
