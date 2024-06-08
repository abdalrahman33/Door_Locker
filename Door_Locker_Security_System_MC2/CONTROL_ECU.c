/*
 * CONTROL_ECU.C
 *
 *  Created on: Mar 11, 2024
 *      Author: Abdelrahman Salem
 */
#include <avr/io.h>
#include <util/delay.h>
#include "std_types.h"
#include "external_eeprom.h"
#include "timer.h"
#include "twi.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "uart.h"


#define NO_OF_DIGITS_IN_PASS 5
#define PASSWORD_ADDRESS 0x00FF

uint8 g_tick=0;
uint8 g_flag=0;
uint8 counterCheck=0;

typedef enum{
	SUCCEED,BREAK
}Message_Status;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void SavePass(void);
void OpenDoor(void);
void ChangePass(void);
void MotorDoor(void);
void Error(void);
void buzzer(void);

/*******************************************************************************
 *                     				Main 	                                   *
 *******************************************************************************/


int main(void)
{
	SREG   |= (1<<7);
	DcMotor_Init();

	Buzzer_init();

	TWI_ConfigType twiConfig={0b00000010,400000};
	TWI_init(&twiConfig);

	UART_ConfigType uartConfig={BIT_DATA_8,DISABLED,ONE_BIT,9600};
	UART_init(&uartConfig);

	SavePass();

	for(;;)
	{
		if(UART_recieveByte()=='+')
		{
			OpenDoor();
		}
		else if(UART_recieveByte()=='-')
		{
			ChangePass();
		}
	}



}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void SavePass(void)
{
	uint8 arr[5]={0};
	Message_Status State=SUCCEED;
	for(int i=0;i<NO_OF_DIGITS_IN_PASS;i++)
	{
		arr[i]=UART_recieveByte();
	}
	for(int i=0;i<NO_OF_DIGITS_IN_PASS;i++)
	{
		if(arr[i]!=UART_recieveByte())
		{
			State=BREAK;
		}
	}
	UART_sendByte(State);
	if(State==BREAK)
	{
		SavePass();
	}
	else
	{
		for(int i=0;i<NO_OF_DIGITS_IN_PASS;i++)
		{
			_delay_ms(10);
			EEPROM_writeByte(PASSWORD_ADDRESS+i,arr[i]);
		}
	}
}

void buzzer(void)
{
	g_tick++;
	Buzzer_on();
	if(g_tick==120)
	{
		Buzzer_off();
		g_tick=0;
		Timer1_deInit();
	}

}


void OpenDoor(void)
{
	uint8 read;
	Message_Status State=SUCCEED;
	for(int i=0;i<NO_OF_DIGITS_IN_PASS;i++) //check if password is correct
	{
		_delay_ms(10);
		EEPROM_readByte(PASSWORD_ADDRESS+i, &read);
		if(read!=UART_recieveByte())
		{
			State=BREAK;
		}
	}

	UART_sendByte(State); //send STATE to other MC

	if(State==SUCCEED) //success & open door
	{
		counterCheck=0;

		Timer1_setCallBack(MotorDoor);
		Timer1_ConfigType t1Config={0,0,PS_64_T1,NORM_T1,NONE,TOGGLE_T1};
		Timer1_init(&t1Config);
	}
	else if(State==BREAK) //failure
	{
		counterCheck++;
		if(counterCheck==3) //send error if counter = 3
		{
			counterCheck=0;
			Error();
		}
		else
		{
			OpenDoor(); //repeat as long as counter less than 3
		}
	}
}
void ChangePass(void)
{
	uint8 read;
	Message_Status State=SUCCEED;

	for(int i=0;i<NO_OF_DIGITS_IN_PASS;i++)
	{
		_delay_ms(10);
		EEPROM_readByte(PASSWORD_ADDRESS+i, &read);

		if(read!=UART_recieveByte())
		{
			State=BREAK;
		}
	}
	UART_sendByte(State);
	if(State==SUCCEED)
	{
		counterCheck=0;
		SavePass();
	}
	else
	{
		counterCheck++;
		if(counterCheck==3)
		{
			counterCheck=0;
			Error();
		}
		else
		{
			ChangePass();
		}

	}
}

void MotorDoor(void)
{
	g_tick++;
	if(g_tick==66)
	{
		DcMotor_Rotate(NO_ROTATION,100);
		Timer1_deInit();
		g_tick=0;
	}
	else if(g_tick<30)
	{
		DcMotor_Rotate(CW_ROTATION,100);
	}
	else if(g_tick<36)
	{
		DcMotor_Rotate(NO_ROTATION,100);
	}
	else
	{
		DcMotor_Rotate(CCW_ROTATION,100);
	}

}


void Error(void)
{
	Timer1_setCallBack(buzzer);
	Timer1_ConfigType t1Config={0,0,PS_64_T1,NONE,TOGGLE_T1};
	Timer1_init(&t1Config);
}


