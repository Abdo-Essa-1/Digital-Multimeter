/*
 * INT1.c
 *
 *  Created on: Apr 27, 2024
 *      Author: Abdo Essa
 */

#include "INT1.h"
#include "common_macros.h"
#include <avr/interrupt.h>

void (*Global_PF_Vector_2)(void) = NULL ;

void INT1_INIT()
{
	SET_BIT(MCUCR,ISC11);
	CLEAR_BIT(MCUCR,ISC10);
	SET_BIT(GICR,INT1);
	sei();
}


void INT1_SetCallBack(void (*Local_PointerToFunction) (void))
{
	Global_PF_Vector_2 = Local_PointerToFunction;
}


void __vector_2 (void)   __attribute__((signal));
void __vector_2 (void)
{
	if ( Global_PF_Vector_2 != NULL )
	{
		Global_PF_Vector_2 ();  // calling Global pointer to function that contain address of Application Function with INT1.
	}
}
