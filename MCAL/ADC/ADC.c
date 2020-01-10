/*
 * ADC.c
 *
 * Created: 1/9/2020 9:13:43 PM
 *  Author: ahmed
 */ 

#include "ADC.h"
#include "DIO.h"
 #include <avr/interrupt.h>

void __vector_16(void)__attribute((signal,used));		/* ISR for ADC */
void (*callBack_ADC)(void)=NULL_PTR;					/* Local function to set cal back function */


uint8_t ADC_Init(Str_ADCConfiguration_t * pstr_ADCconfig)
{
	uint8_t retval = ERROR_OK;
	/* to select channel of ADC */
	switch( pstr_ADCconfig -> u8_ADC_Channel )
	{
		case ADC_CHANNEL0: ADMUX|=0x00;    /* channel 0 */
		break;
		case ADC_CHANNEL1: ADMUX|=0x01;    /* channel 1 */	   
		break;
		case ADC_CHANNEL2: ADMUX|=0x02;    /* channel 2 */
		break;
		case ADC_CHANNEL3: ADMUX|=0x03;    /* channel 3 */
		break;
		case ADC_CHANNEL4: ADMUX|=0x04;    /* channel 4 */
		break;
		case ADC_CHANNEL5: ADMUX|=0x05;    /* channel 5 */
		break;
		case ADC_CHANNEL6: ADMUX|=0x06;    /* channel 6 */
		break;
		case ADC_CHANNEL7: ADMUX|=0x07;    /* channel 7 */
		break;
		default: retval = ERROR_ADC_CHANNEL;          /* for error checking */
		break;
	}

	/* to select V REF source */
	switch( pstr_ADCconfig ->u8_V_REF )
	{
		case OUTPUT_VREF: ADMUX|= 0x00;                /* get V REF from external pin 5v */
		break;
		case EXTERNAL_CAPACITOR_AT_VREF : ADMUX|= 0x40;  /* get V REF from external pin with CAPACITOR */
		break;
		case INTERNAL_2_56_VREF: ADMUX|= 0xC0;		  /* get V REF from internal v 2.56 v */
		break;
		default: retval = ERROR_ADC_V_REF;			/* for error checking */
		break;	
	}

	switch(pstr_ADCconfig ->u8_ADC_Mode)
	{
		case ADC_INTRRUPT_MODE : SET_BIT(SREG, GI);      /* enable global interrupt */
								 ADCSRA |= (1<<ADCSRA_ADIE);   /* enable ADC interrupt */
		break;
		case ADC_POLLING_MODE :	ADCSRA |= (1<<ADCSRA_ADSC);		/* start conversion */
								while((ADCSRA & (1<<ADCSRA_ADIF)) == 0);   /* wait that conversion complete */
		break;
		default: retval = ERROR_INTERRUPT_POLLING;      /* for error checking */
		break;
	}

	/* select right or left adjust for ADLAR reg */
	switch(pstr_ADCconfig -> u8_DataAdjust)
	{
		case RIGHT_ADJUST :		/* not handled */
		break;
		case LEFT_ADJUST : ADMUX |= (1<< ADMUX_ADLAR);		 /* dominnant case */
		break;
		default: 
		break;
	}

	/* to select between normal mode or auto trigger mode */
	switch( pstr_ADCconfig ->u8_AutoTrigger)
	{
		case NORMAL_MODE:			/* normal mode */
		break;
		case AUTO_TRIGGER_MODE: ADCSRA |= (1<< ADCSRA_ADATE );		/* auto trigger mode */
		break;
		default: retval = ERROR_ADC_MODE;
		break;
	}

	/* to chose form source of trigger of ADC */
	switch( pstr_ADCconfig ->u8_AutoTriggerSource)
	{
		case FREE_RUNNING_MODE:							/* free running mode */
		break;
		case ANALOGE_COMPARETOR: SFIOR |= (1<<SFIOR_ADTS0);		/* Analog comparator mode */
		break;
		case EXTERNAL_INTERRUPT0_REQUEST   : SFIOR |= (1<<SFIOR_ADTS1);  /* set external interrupt as trigger */
											 MCUCR = 0x03;				 /* set external interrupt 0 for rising edge */
											 GICR = (1<<6);              /* enable external interrupt */
		break;
		case TIMER0_COMPARE_MATCH: SFIOR |= (1<<SFIOR_ADTS1) | (1<<SFIOR_ADTS0); /* Timer0 compare match */
		break;
		case TIMER0_OVER_FLOW: SFIOR |= (1<<SFIOR_ADTS2);						/* Timer0 Overflow */
		break;
		case TIMER1_COMPARE_MATCH: SFIOR |= (1<<SFIOR_ADTS2) | (1<<SFIOR_ADTS0); /* Timer1 compare match */
		break;
		case TIMER1_OVER_FLOW: SFIOR |= (1<<SFIOR_ADTS2) | (1<<SFIOR_ADTS1);	/* Timer1 over flow */
		break;
		case TIMER1_CAPTURE_EVENT: SFIOR |= (1<<SFIOR_ADTS2) | (1<<SFIOR_ADTS1) | (1<<SFIOR_ADTS0);
		break;
		default:	retval = ERROR_TRIGGER_MODE;
		break; 
	}

	/* to check for prescaler */
	switch(pstr_ADCconfig ->u8_Prescaller)
	{
		case PRESCALLER_2: ADCSRA |= (1<<ADCSRA_ADPS0); /* prescaler /2 */
		break;
		case PRESCALLER_4: ADCSRA |= (1<<ADCSRA_ADPS1); /* prescaler /4 */
		break;
		case PRESCALLER_8: ADCSRA |= (1<<ADCSRA_ADPS0) | (1<<ADCSRA_ADPS1); /* prescaler /8 */
		break;
		case PRESCALLER_16: ADCSRA |= (1<<ADCSRA_ADPS2); /* prescaler /16 */
		break;
		case PRESCALLER_32: ADCSRA |= (1<<ADCSRA_ADPS0) | (1<<ADCSRA_ADPS2); /* prescaler /32 */
		break;
		case PRESCALLER_64: ADCSRA |= (1<<ADCSRA_ADPS1) | (1<<ADCSRA_ADPS2); /* prescaler /64 */
		break;
		case PRESCALLER_128: ADCSRA |= (1<<ADCSRA_ADPS0) | (1<<ADCSRA_ADPS2) | (1<<ADCSRA_ADPS1); /* prescaler /128 */
		break;
		default: retval= ERROR_PRESCALER ;
		break;
	}
	/* Enable ADC module */
	ADCSRA |= (1<<ADCSRA_ADEN);

	return retval;	/* return Error value */
}

void ADC_Read(void)
{	
	/* start conversion */
	ADCSRA |= (1<<ADCSRA_ADSC); 
}


/* Global ADC set callback function */
uint8_t Set_Call_Back_ADC(void (*function)(void))
{
	uint8_t retval = ERROR_OK;
	if( function != NULL_PTR )
	{
		callBack_ADC = function;
	}
	else
	{
		retval = E_PTR_IS_NULL ;
	}
	return retval;
}

/* ISR For ADC conversion complete */
void __vector_16(void)
{
	if(callBack_ADC != NULL_PTR)
	{
		callBack_ADC();
	}
}