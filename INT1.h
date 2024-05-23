/*
 * INT1.h
 *
 *  Created on: Apr 27, 2024
 *      Author: Abdo Essa
 */

#ifndef INT1_H_
#define INT1_H_

#include "std_types.h"

/* Private Macros */

#define  NULL                     (void*)(0)

void INT1_INIT(void);

void INT1_SetCallBack(void (*Local_PointerToFunction) (void));

#endif /* INT1_H_ */
