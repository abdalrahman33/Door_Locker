/*
 * buzzer.c
 *
 *  Created on: Mar 11, 2024
 *      Author: Abdelrahman Salem
 */

#include "buzzer.h"
#include "gpio.h"


/*
 * Description :
 * Initialize the Buzzer:
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN2_ID,PIN_OUTPUT);

	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN1_ID,LOGIC_LOW);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN2_ID,LOGIC_LOW);

}


/*
 * Description :
 * Turn ON Buzzer
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN1_ID,LOGIC_HIGH);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN2_ID,LOGIC_LOW);

}

/*
 * Description :
 * Turn OFF Buzzer
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN1_ID,LOGIC_LOW);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN2_ID,LOGIC_LOW);

}
