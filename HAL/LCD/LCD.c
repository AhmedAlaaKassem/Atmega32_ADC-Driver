// implemented by A.A.KASSEM
#include"LCD.h"



void LCD_Init (void){
	LCD_DATA_DIR= 0XF0;                            // PORT A  HIGH 4 BITS for LCD 
	LCD_CTR_DIR |= (1<<RS) | (1<<RW) | (1<<E)  ;    // configure 3 pins for control LCD output
	_delay_ms(20);		                           /* LCD Power ON delay always >15ms */
	LCD_sendcmd(0x33);
	LCD_sendcmd(0x32);	                           // Send for 4 bit initialization of LCD  
	LCD_sendcmd(0x28);	                           // 2 line, 5*7 matrix in 4-bit mode 
	LCD_sendcmd(0x0c);                             // Display on cursor off 
	LCD_sendcmd(0x06);                             // Increment cursor (shift cursor to right) 
	LCD_sendcmd(0x01);	                           //	 Clear display screen 
}

void LCD_sendcmd       (unsigned char cmd){
	LCD_DATA = (cmd & 0xF0); // out the required command to the data bus D4 --> D7          // delay for processing
	CLEARBIT(LCD_CTR,RS);    // Instruction Mode RS=0
	CLEARBIT(LCD_CTR,RW);    // write command to LCD so RW=0
	SETBIT(LCD_CTR,E);       // Enable LCD E=1
	_delay_ms(1);            //delay for processing
	CLEARBIT(LCD_CTR,E);     //disable LCD E=0
	_delay_ms(1);	

	LCD_DATA = ((cmd<<4) & 0xF0); // shift data command D0 --> D3            //delay for processing
	CLEARBIT(LCD_CTR,RS);    // Instruction Mode RS=0
	CLEARBIT(LCD_CTR,RW);    // write command to LCD so RW=0
	SETBIT(LCD_CTR,E);       // Enable LCD E=1
	_delay_ms(1);            //delay for processing
	CLEARBIT(LCD_CTR,E);     //disable LCD E=0
	_delay_ms(1);
}

void LCD_sendchar      (unsigned char data){
	LCD_DATA = (data & 0xF0); // out the required command to the data bus D4 --> D7
	_delay_ms(1);            // delay for processing
	SETBIT(LCD_CTR,RS);      // Instruction Mode RS=0
	CLEARBIT(LCD_CTR,RW);    // write command to LCD so RW=0
	SETBIT(LCD_CTR,E);       // Enable LCD E=1
	_delay_ms(1);            //delay for processing
	CLEARBIT(LCD_CTR,E);     //disable LCD E=0
	_delay_ms(1);

	LCD_DATA = ((data<<4) & 0xF0); // shift data  D0 --> D3
	_delay_ms(1);            //delay for processing
	SETBIT(LCD_CTR,RS);      // Instruction Mode RS=0
	CLEARBIT(LCD_CTR,RW);    // write command to LCD so RW=0
	SETBIT(LCD_CTR,E);       // Enable LCD E=1
	_delay_ms(1);            //delay for processing
	CLEARBIT(LCD_CTR,E);     //disable LCD E=0
	_delay_ms(1);
}

void LCD_sendstring    (const char *str){
unsigned char i=0;
while(str[i] != '\0')
	{
		LCD_sendchar(str[i]);
		i++;
	}
}

void LCD_goto_xy       (unsigned char row, unsigned char col){

	unsigned char add=1;
	switch(row)
	{
		case 0:
				add=col;
				break;
		case 1:
				add=col+0x40;
				break;

	}					
	
	LCD_sendcmd(add | 0x80);     // we need to apply the corresponding command 0b10000000+Address 

}

void LCD_sendstring_xy (unsigned char row, unsigned char col , const char *str){
LCD_goto_xy(row,col);
LCD_sendstring(str);
}

void LCD_clear         (void){
LCD_sendcmd(0X01);           // 0X01  command for clear screen
}

void LCD_inttostring   (int data){
char str[16];
sprintf(str, "%d", data);
LCD_sendstring(str);
}


