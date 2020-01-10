/*
 * ADC.h
 *
 * Created: 1/9/2020 9:13:33 PM
 *  Author: ahmed
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "COMMON_MACROS.h"
#include "STD_TYPES.h"
#include "ADC_REG.h"


/*****ADC Configuration Struct****/
typedef struct
{
	uint8_t u8_ADC_Channel;		  /* select ADC channel */
	uint8_t u8_V_REF;			  /* select V_ref source */
	uint8_t u8_ADC_Mode;		  /* INTERRUPT or POLLING */
	uint8_t u8_DataAdjust;        /* Right adjust or Left adjust */
	uint8_t u8_AutoTrigger;		  /* Auto trigger or not */
	uint8_t u8_AutoTriggerSource; /* Auto trigger source */
	uint8_t u8_Prescaller;		  /* select prescaler */
}Str_ADCConfiguration_t;


/******ADC Channel Selection****/
#define ADC_CHANNEL0 0U
#define ADC_CHANNEL1 1U
#define ADC_CHANNEL2 2U
#define ADC_CHANNEL3 3U
#define ADC_CHANNEL4 4U
#define ADC_CHANNEL5 5U
#define ADC_CHANNEL6 6U
#define ADC_CHANNEL7 7U

/******Vref Selection*********/
#define OUTPUT_VREF           			     0U
#define EXTERNAL_CAPACITOR_AT_VREF 			 1U
#define INTERNAL_2_56_VREF                   2U

/****ADC Mode Interrut or Polling ***/
#define ADC_INTRRUPT_MODE					 0U
#define ADC_POLLING_MODE					 1U

/****Data Adjustment*****/
#define RIGHT_ADJUST						 0U
#define LEFT_ADJUST							 1U

/********Auto Trigger or not*******/
#define AUTO_TRIGGER_MODE					 1U
#define NORMAL_MODE							 0U

/********Trigger Source*******/
#define FREE_RUNNING_MODE					 0U
#define ANALOGE_COMPARETOR					 1U
#define EXTERNAL_INTERRUPT0_REQUEST			 2U
#define TIMER0_COMPARE_MATCH				 3U
#define TIMER0_OVER_FLOW					 4U
#define TIMER1_COMPARE_MATCH				 5U
#define TIMER1_OVER_FLOW					 6U
#define TIMER1_CAPTURE_EVENT				 7U

/*******ADC Prescaller Selection********/
#define PRESCALLER_2						 1U
#define PRESCALLER_4						 2U
#define PRESCALLER_8						 3U
#define PRESCALLER_16						 4U
#define PRESCALLER_32						 5U
#define PRESCALLER_64						 6U
#define PRESCALLER_128						 7U

#define NA									 0U


/********* ERRORS **********/
#define ERROR_OK 0
#define ERROR_ADC_CHANNEL -1
#define ERROR_ADC_V_REF -2
#define ERROR_INTERRUPT_POLLING -3
#define E_PTR_IS_NULL -4
#define ERROR_ADC_MODE -5
#define ERROR_TRIGGER_MODE -6
#define ERROR_PRESCALER -7


/* INIT function for ADC module */
uint8_t ADC_Init(Str_ADCConfiguration_t * pstr_ADCconfig);

/* ADC function to start converstion */
void  ADC_Read(void);

/* Call back function for user to use it in application */
uint8_t Set_Call_Back_ADC(void (*function)(void));

#endif /* ADC_H_ */