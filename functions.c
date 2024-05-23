/*
 * functions.c
 *
 *  Created on: Apr 26, 2024
 *      Author: Abdo Essa
 */

#include <util/delay.h>
#include <avr/interrupt.h>
#include "functions.h"
#include "lcd.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include "adc.h"
#include "keypad.h"

uint8 MyFlag = FALSE;

void MainMenu(void)
{
	LCD_clearScreen();
	_delay_ms(5);
	LCD_displayString("Choose the type:");
	LCD_displayStringRowColumn(1,0,"1)V 2)A 3)R 4)AC");
	TypeDetect();
}

void TypeDetect(void)
{
	uint8 key = KEYPAD_getPressedKey();
	_delay_ms(100);
	LCD_clearScreen();
	_delay_ms(5);
	switch(key)
	{
	case 1:
		VoltRange();
		break;
	case 2:
		AmeterSet();
		MyAmeter();
		break;
	case 3:
		MyOhmeter();
		break;
	case 4:
		ACType();
		break;
	default:
		Invalid();
		MainMenu();
		break;
	}
}


void MyVoltmeter(uint8 range)
{
	float voltage = 0;
	uint8 dummyTransformValue;

	switch(range)
	{
	case 1:
		dummyTransformValue = 2;
		break;
	case 2:
		dummyTransformValue = 4;
		break;
	default:
		Invalid();
		VoltRange();
		break;
	}

	LCD_moveCursor(0,0);
	LCD_displayString("V = ");
	LCD_moveCursor(0,4);

	while(1)
	{
		voltage = ADC_readChannel(VoltPin);
		_delay_ms(500);

		voltage = (voltage*5.0*dummyTransformValue)/(1023.0);

		LCD_floatToString(voltage);
		LCD_displayStringRowColumn(0,8,"  V");
		LCD_moveCursor(0,4);

		if(MyFlag)
		{
			MyFlag = FALSE;
			_delay_ms(5);
			MainMenu();
		}
	}
}


void VoltRange()
{
	LCD_clearScreen();
	_delay_ms(5);
	LCD_displayString("Volt Range?");
	LCD_displayStringRowColumn(1,0,"1)0-10V 2)10-20V");
	uint8 key = KEYPAD_getPressedKey();
	_delay_ms(100);
	switch(key)
	{
	case 1:
		Voltmeter10Set();
		break;
	case 2:
		Voltmeter20Set();
		break;
	}
	LCD_clearScreen();
	_delay_ms(5);
	MyVoltmeter(key);
}


void MyAmeter()
{
	float current = 0;

	LCD_moveCursor(0,0);
	LCD_displayString("A = ");
	LCD_moveCursor(0,4);

	while(1)
	{
		current = ADC_readChannel(AmpPin);
		_delay_ms(500);

		current = ((current*5.0*9.09)/(1023.0 * 3.0));

		LCD_floatToString(current);
		LCD_displayStringRowColumn(0,8,"   mA");
		LCD_moveCursor(0,4);

		if(MyFlag)
		{
			MyFlag = FALSE;
			_delay_ms(5);
			MainMenu();
		}
	}
}


void MyOhmeter()
{
	OhmeterSet();

	float resistance = 0;

	LCD_moveCursor(0,0);
	LCD_displayString("R = ");
	LCD_moveCursor(0,4);

	while(1)
	{
		resistance = ADC_readChannel(ResPin);
		_delay_ms(500);
		//resistance = (5.0 * 1500.0 * resistance) / (1023.0 * 12.0 - 5.0 * resistance);

		resistance = resistance * 5.0 / 1023.0;

		LCD_floatToString(resistance);
		LCD_displayStringRowColumn(0,8,"    KOhm");

		LCD_moveCursor(0,4);

		if(MyFlag)
		{
			MyFlag = FALSE;
			_delay_ms(5);
			MainMenu();
		}
	}
}


void MyACmeter(uint8 type)
{
	float voltage = 0;
	while(1)
	{
		voltage = ADC_readChannel(ACPin);
		_delay_ms(500);

		voltage = (voltage*5.0)/(1023.0);

		switch(type)
		{
		case 1:
			LCD_displayStringRowColumn(0,0,"Vac = ");
			LCD_floatToString(voltage);
			LCD_displayStringRowColumn(0,7,"     V");
			break;
		case 2:
			voltage *= 100.0;
			LCD_displayStringRowColumn(0,0,"Iac = ");
			LCD_floatToString(voltage);
			LCD_displayStringRowColumn(0,7,"     mA");
			break;
		}

		if(MyFlag)
		{
			MyFlag = FALSE;
			_delay_ms(5);
			MainMenu();
		}
	}
}


void ACType()
{
	LCD_clearScreen();
	_delay_ms(5);
	LCD_displayString("AC Type?");
	LCD_displayStringRowColumn(1,0,"1)Volt   2)Amps");
	uint8 key = KEYPAD_getPressedKey();
	_delay_ms(100);
	LCD_clearScreen();

	MyACmeter(key);
}


void Invalid()
{
	LCD_clearScreen();
	_delay_ms(5);
	LCD_displayStringRowColumn(0,1,"Invalid input!");
	_delay_ms(2000);
}


void Welcome(void)
{
	LCD_displayStringRowColumn(0,3,"Welcome to");
	LCD_displayStringRowColumn(1,4,"our DMM!");
	_delay_ms(2000);
	LCD_clearScreen();
	_delay_ms(5);
}


void ISR_Toggle()
{
	MyFlag = TRUE;
	_delay_ms(5);
}


void Voltmeter10Set()
{
	GPIO_setupPinDirection(SEL1Port,SEL1Pin,PIN_OUTPUT);
	GPIO_setupPinDirection(SEL2Port,SEL2Pin,PIN_OUTPUT);
	GPIO_setupPinDirection(VselPort,VselPin,PIN_OUTPUT);
	_delay_ms(5);

	GPIO_writePin(SEL1Port,SEL1Pin,LOGIC_LOW);
	GPIO_writePin(SEL2Port,SEL2Pin,LOGIC_LOW);
	GPIO_writePin(VselPort,VselPin,LOGIC_LOW);
	_delay_ms(5);
}


void Voltmeter20Set()
{
	GPIO_setupPinDirection(SEL1Port,SEL1Pin,PIN_OUTPUT);
	GPIO_setupPinDirection(SEL2Port,SEL2Pin,PIN_OUTPUT);
	GPIO_setupPinDirection(VselPort,VselPin,PIN_OUTPUT);
	_delay_ms(5);

	GPIO_writePin(SEL1Port,SEL1Pin,LOGIC_LOW);
	GPIO_writePin(SEL2Port,SEL2Pin,LOGIC_LOW);
	GPIO_writePin(VselPort,VselPin,LOGIC_HIGH);
	_delay_ms(5);
}

void AmeterSet()
{
	GPIO_setupPinDirection(SEL1Port,SEL1Pin,PIN_OUTPUT);
	GPIO_setupPinDirection(SEL2Port,SEL2Pin,PIN_OUTPUT);
	_delay_ms(5);

	GPIO_writePin(SEL1Port,SEL1Pin,LOGIC_LOW);
	GPIO_writePin(SEL2Port,SEL2Pin,LOGIC_HIGH);
	_delay_ms(5);
}


void OhmeterSet()
{
	GPIO_setupPinDirection(SEL1Port,SEL1Pin,PIN_OUTPUT);
	GPIO_setupPinDirection(SEL2Port,SEL2Pin,PIN_OUTPUT);
	_delay_ms(5);


	GPIO_writePin(SEL1Port,SEL1Pin,LOGIC_HIGH);
	GPIO_writePin(SEL2Port,SEL2Pin,LOGIC_HIGH);
	_delay_ms(5);
}

void SetReset()
{
	GPIO_setupPinDirection(ResetPort, ResetPin, PIN_INPUT);
	GPIO_writePin(ResetPort, ResetPin, LOGIC_HIGH);
	_delay_ms(5);
}

void SetPullUp()
{
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 1, LOGIC_HIGH);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 2, LOGIC_HIGH);
	GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 3, LOGIC_HIGH);
	_delay_ms(5);
}
