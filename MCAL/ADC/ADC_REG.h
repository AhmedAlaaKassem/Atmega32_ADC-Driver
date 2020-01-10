/*
 * ADC_REGISTERS.h
 *
 * Created: 1/9/2020 1:26:57 PM
 *  Author: Zeyad
 */ 


#ifndef ADC_REG_H_
#define ADC_REG_H_

#define ADMUX	 *((volatile uint8_t*) 0x27)
#define ADCSRA	 *((volatile uint8_t*) 0x26)
#define ADCH	 *((volatile uint8_t*) 0x25)
#define ADCL	 *((volatile uint8_t*) 0x24)
#define SFIOR	 *((volatile uint8_t*) 0x50)

#define SREG     *((volatile uint8_t*) 0x5FU)

#define GI 		7U

#define SFIOR_ADTS0 5
#define SFIOR_ADTS1 6
#define SFIOR_ADTS2 7


#define ADMUX_REF1  7U
#define ADMUX_REF0  6U
#define ADMUX_ADLAR 5U
#define ADMUX_MUX4  4U
#define ADMUX_MUX3  3U
#define ADMUX_MUX2  2U
#define ADMUX_MUX1  1U
#define ADMUX_MUX0  0U

#define ADCSRA_ADEN  7U
#define ADCSRA_ADSC  6U
#define ADCSRA_ADATE 5U
#define ADCSRA_ADIF  4U
#define ADCSRA_ADIE  3U
#define ADCSRA_ADPS2 2U
#define ADCSRA_ADPS1 1U
#define ADCSRA_ADPS0 0U


#endif /* ADC_REG_H_ */