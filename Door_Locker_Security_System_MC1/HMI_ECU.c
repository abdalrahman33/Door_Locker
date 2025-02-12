/*
 * HMI_ECU.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Abdelrahman Salem
 */

#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer.h"
#include "std_types.h"
#include <util/delay.h>
#include <avr/io.h>

#define NO_OF_DIGITS_IN_PASS 5

uint8 g_tick=0;
uint8 g_flag=0;
uint8 counterCheck=0;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void CreatePass(void);
void Error_callback(void);
void Error(void);
void OpenDoor_callback(void);
void OpenDoor(void);
void ChangePass(void);

/*******************************************************************************
 *                     				Main                     		           *
 *******************************************************************************/


int main(void)
{

	SREG   |= (1<<7);
	LCD_init();

	UART_ConfigType uartConfig={BIT_DATA_8,DISABLED,ONE_BIT,9600};
	UART_init(&uartConfig);

	/*
	 * For initiation of pass
	 */
	CreatePass();

	for(;;)
	{
		LCD_clearScreen();
		uint8 option;
		LCD_moveCursor(0,0);
		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1,0);
		LCD_displayString("- : Change Pass");
		option=KEYPAD_getPressedKey();
		if(option=='+')
		{
			UART_sendByte('+');
			OpenDoor();
		}
		else if(option=='-')
		{
			UART_sendByte('-');
			ChangePass();
		}
	}
}

/*******************************************************************************
 *                  		      Functions                                    *
 *******************************************************************************/

void CreatePass(void)
{
	sint8 value=-1;
	LCD_displayString("Plz enter pass: ");
	LCD_moveCursor(1,0);

	uint8 counter=0;
	do
	{
		counter++;
		value=KEYPAD_getPressedKey();
		_delay_ms(250);
		if(counter<=NO_OF_DIGITS_IN_PASS)
		{
			UART_sendByte(value);
			LCD_displayCharacter('*');
		}

	}while(value!='=');
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Plz re-enter the");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass: ");

	counter=0;
	do
	{
		counter++;
		value=KEYPAD_getPressedKey();
		_delay_ms(250);
		if(counter<=NO_OF_DIGITS_IN_PASS)
		{
			UART_sendByte(value);
			LCD_displayCharacter('*');
		}

	}while(value!='=');
	LCD_clearScreen();
	if(UART_recieveByte())
	{
		CreatePass();
	}
	else
	{
		return;
	}
}

void OpenDoor(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Plz enter pass: ");
	LCD_moveCursor(1,0); //ask for password

	sint8 value;
	uint8 counter=0;
	do  //write password & wait until '=' is pressed
	{
		counter++;
		value=KEYPAD_getPressedKey();
		_delay_ms(250);
		if(counter<=NO_OF_DIGITS_IN_PASS) //accept only 5 inputs to send & display
		{
			UART_sendByte(value);
			LCD_displayCharacter('*');
		}

	}while(value!='=');


	LCD_clearScreen();

	if(UART_recieveByte()) //error in password
	{
		counterCheck++;
		if(counterCheck==3) //check 3 times before sending error
		{
			counterCheck=0;
			Error();
		}
		else
		{
			OpenDoor(); //repeat as long as counter less than 3
		}
	}
	else //success & set timer to open door
	{
		LCD_clearScreen();
		counterCheck=0;
		Timer1_setCallBack(OpenDoor_callback);
		Timer1_ConfigType t1Config={0,0,PS_64_T1,NORM_T1,NONE,TOGGLE_T1};
		Timer1_init(&t1Config);
		while(g_flag==0);
		g_flag=0;
	}
}



void OpenDoor_callback(void)
{
	g_tick++;
	if(g_tick==66)
	{
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("Done   ");
		LCD_moveCursor(1,0);
		LCD_displayString("Locking    ");
		Timer1_deInit();
		g_tick=0;
		g_flag=1;
	}
	else if(g_tick<30)
	{
		LCD_moveCursor(0,0);
		LCD_displayString("Door is    ");
		LCD_moveCursor(1,0);
		LCD_displayString("Unlocking    ");
	}
	else if(g_tick<66)
	{
		LCD_moveCursor(0,0);
		LCD_displayString("Door is   ");
		LCD_moveCursor(1,0);
		LCD_displayString("Locking    ");
	}



}


void ChangePass(void)
{
	UART_sendByte('-');
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Plz enter pass: ");
	LCD_moveCursor(1,0);

	sint8 value;
	uint8 counter=0;
	do
	{
		counter++;
		value=KEYPAD_getPressedKey();
		_delay_ms(250);
		if(counter<=5)
		{
			UART_sendByte(value);
			LCD_displayCharacter('*');
		}

	}while(value!='=');
	LCD_clearScreen();
	if(UART_recieveByte())
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
	else
	{
		counterCheck=0;
		CreatePass();
	}
}



void Error(void)
{
	Timer1_setCallBack(Error_callback);
	Timer1_ConfigType t1Config={0,0,PS_64_T1,NONE,TOGGLE_T1};
	Timer1_init(&t1Config);

	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("I Caught u");

	while(g_flag==0);
	g_flag=0;


}

void Error_callback(void)
{
	g_tick++;
	if(g_tick==120)
	{
		g_flag=1;
		Timer1_deInit();
		g_tick=0;
	}
}
