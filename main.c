/*
 * DIO_PROJECT_TESTED.c
 *
 * Created: 12/17/2019 4:33:13 AM
 * Author : Ahmed Alaa
 */ 

 #include "LCD.h"
 #include "ADC_Pb.h"
 #include "DIO.h"
 #include "Timer_Pb.h"
 #include <avr/interrupt.h>

 #define CONVERSION_COMPLETE 1				/* to indicate that conversion is complete */
 #define CONVERSION_NOT_COMPLETE 0			/* to indicate that conversion not complete yet */

 uint16_t volatile Global_reading;			/* Global variable for getting ADC reading */
 uint8_t  volatile ADC_flag = CONVERSION_NOT_COMPLETE;  /* Flag use to ensure conversion status */


 void ACD_callback_function(void);		/* call back function of ADC conversion complete will run every time ADC triggered */

  int main ()
  {

		LCD_Init();						/* Init LCD */
		ADC_Init(&ADC_obj);				/* Init ADC */
		Timer_Init(&Timer1);			/* Init Timer 1 with Timer1 object configuration in timer post build file */
		
		LCD_sendstring("Temp = ");		/* Display */
		LCD_goto_xy(0,10);
		LCD_sendchar('C');				/* Display */
		
		Set_Call_Back_ADC(ACD_callback_function);  /* set call back function for every conversion of ADC will run */
		
		ADC_Read();					 /* Start ADC conversion */

		Timer_Start(TIMER1,7800);    /* using 1024 prescaler with 8 mega freq 7800 tic = 1 sec */
									 /* every over flow will catch new value for ADC converter */
		while (1)
		{
			if( ADC_flag == CONVERSION_COMPLETE )	/* Check if conversion complete or not */
			{
				ADC_flag = CONVERSION_NOT_COMPLETE;	/* clear flag indicating that ADC process not complete yet */
				LCD_goto_xy(0,7);					/* to display the number */
				/* Max volt for LM35 is 1.5 v */
				/*  5 volt -> 1024 res   ***  1.5 volt -> 307 reslution */
				/* 307 max resolution at 150 C  *** 307/150 = 2 for every 1 degeree C*/
				Global_reading /= 2;
				LCD_inttostring(Global_reading);	/*display the temp on LCD screen*/
			}
		}
  }


  void ACD_callback_function(void)
  {
	Global_reading  = ADCL;					/* get Least 8 bit reg value -- store it in g variable */
	Global_reading |= (uint16_t)(ADCH << 8);	/* shift the Most 8 bit to left and masking with the g variable to get the value */
	ADC_flag = CONVERSION_COMPLETE ;		/* set flage indicating conversion complete */
  }

  

  

  




