/*
 * main.c
 *
 *  Created on: Apr 26, 2024
 *      Author: Abdo Essa
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"
#include "INT1.h"
#include "lcd.h"
#include "keypad.h"
#include "adc.h"
#include "functions.h"

int main()
{
	/******Initializations******/
	ADC_init();
	LCD_init();
	INT1_INIT();
	INT1_SetCallBack(ISR_Toggle);
	SetReset();
	SetPullUp();

	Welcome();

	/******PROGRAM******/
	while(1)
	{
		MainMenu();
	}

	return 0;
}
