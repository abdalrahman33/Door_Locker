/*
 * timer1.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Abdelrahman Salem
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

#define TIMER0
#define TIMER1




#ifdef TIMER0
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PWM_T0_ENABLE_PORT_ID  PORTB_ID
#define PWM_T0_ENABLE_PIN_ID   PIN3_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum {
	NO_CLK_T0,PS_1_T0,PS_8_T0,PS_64_T0,PS_256_T0,PS_1024_T0,EXT_CLK_FALLING_T0,EXT_CLK_RISING_T0
}Timer0_Prescaler;

typedef enum {
	NORM_T0,PWM_PH_T0,CTC_T0,FAST_PWM_T0
}Timer0_Mode;


typedef enum {
	NORMAL_T0,TOGGLE_T0,CLEAR_T0,SET_T0
}Timer0_Comp_Match;

typedef struct {
 uint8 initial_value;
 uint8 compare_value; // it will be used in compare mode only.
 Timer0_Prescaler prescaler;
 Timer0_Mode mode;
 Timer0_Comp_Match comp_match; //decide compare match output mode (extra parameter)
} Timer0_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialization of Timer 1 by:
 * 1. Setup Timer Mode
 * 2. Setup Prescaler
 * 3. Setup the initial value
 * 4. Setup compare value if required
 */
void Timer0_init(const Timer0_ConfigType * Config_Ptr);


/*
 * Description :
 * Functional responsible for Deinitialization of Timer 0 by clearing all registers
 */
void Timer0_deInit(void);

/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void));

/*
 * Description: Adjust PWM compare value if input is percentage
 */
void Timer0_pwmAdjust(uint8 duty_cycle);
#endif

#ifdef TIMER1
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PWM_T1A_ENABLE_PORT_ID  PORTD_ID
#define PWM_T1A_ENABLE_PIN_ID   PIN5_ID

#define PWM_T1B_ENABLE_PORT_ID  PORTD_ID
#define PWM_T1B_ENABLE_PIN_ID   PIN4_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum {
	NO_CLK_T1,PS_1_T1,PS_8_T1,PS_64_T1,PS_256_T1,PS_1024_T1,EXT_CLK_FALLING_T1,EXT_CLK_RISING_T1
}Timer1_Prescaler;

typedef enum {
	NORM_T1,PWM_PH_8_T1,PWM_PH_9_T1,PWM_PH_10_T1,CTC_OCR_T1,FAST_PWM_8_T1,FAST_PWM_9_T1,FAST_PWM_10_T1,
	PWM_PH_FR_ICR_T1,PWM_PH_FR_OCR_T1,PWM_PH_ICR_T1,PWM_PH_OCR_T1,CTC_ICR_T1,FAST_PWM_ICR_T1=14,FAST_PWM_OCR_T1
}Timer1_Mode;

typedef enum {
	NONE,TIMER1A,TIMER1B
}Timer1_Index;

typedef enum {
	NORMAL_T1,TOGGLE_T1,CLEAR_T1,SET_T1
}Timer1_Comp_Match;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
 Timer1_Index index; //choose Timer1A or Timer1B (extra parameter)
 Timer1_Comp_Match comp_match; //decide compare match output mode (extra parameter)
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialization of Timer 1 by:
 * 1. Setup Timer Mode
 * 2. Setup Prescaler
 * 3. Setup the initial value
 * 4. Setup compare value if required
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);


/*
 * Description :
 * Functional responsible for Deinitialization of Timer 1 by clearing all registers
 */
void Timer1_deInit(void);

/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));

/*
 * Description: Adjust PWM compare value if input is percentage
 */
void Timer1_pwmAdjust(uint16 duty_cycle);
#endif


#ifdef TIMER2
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PWM_T2_ENABLE_PORT_ID  PORTD_ID
#define PWM_T2_ENABLE_PIN_ID   PIN7_ID


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum {
	NO_CLK_T2,PS_1_T2,PS_8_T2,PS_32_T2,PS_64_T2,PS_128_T2,PS_256_T2,PS_1024_T2
}Timer2_Prescaler;

typedef enum {
	NORM_T2,PWM_PH_T2,CTC_T2,FAST_PWM_T2
}Timer2_Mode;


typedef enum {
	NORMAL_T2,TOGGLE_T2,CLEAR_T2,SET_T2
}Timer2_Comp_Match;

typedef struct {
 uint8 initial_value;
 uint8 compare_value; // it will be used in compare mode only.
 Timer2_Prescaler prescaler;
 Timer2_Mode mode;
 Timer2_Comp_Match comp_match; //decide compare match output mode (extra parameter)
} Timer2_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialization of Timer 1 by:
 * 1. Setup Timer Mode
 * 2. Setup Prescaler
 * 3. Setup the initial value
 * 4. Setup compare value if required
 */
void Timer2_init(const Timer2_ConfigType * Config_Ptr);


/*
 * Description :
 * Functional responsible for Deinitialization of Timer 0 by clearing all registers
 */
void Timer2_deInit(void);

/*
 * Description: Function to set the Call Back function address.
 */
void Timer2_setCallBack(void(*a_ptr)(void));

/*
 * Description: Adjust PWM compare value if input is percentage
 */
void Timer2_pwmAdjust(uint8 duty_cycle);
#endif

#endif /* TIMER_H_ */
