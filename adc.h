#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

#define ADC_MAXIMUM_VALUE   1023
#define ADC_REF_VOLT_VALUE  5

void ADC_init(void);

uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
