/* 
 * 
 *
 * Created: 9/22/2019 4:05:12 PM
 * implemented by A.A.KASSEM
 */
#ifndef LCD_H
#define LCD_H
#define F_CPU 8000000UL 
#include "DIO.h"
#include <stdio.h>
#include <util/delay.h>


#define SETBIT(REG,BIT) ( REG |=  (1<<(BIT)) )
#define CLEARBIT(reg,bit) ( reg &= ~(1<<(bit)) )
#define TOGGLEBIT(reg,bit) ( reg ^=  (1<<(bit)) )


#define LCD_DATA       PORTA
#define LCD_DATA_DIR   DDRA
#define LCD_CTR        PORTA
#define LCD_CTR_DIR    DDRA
#define RS  1
#define RW  2
#define E   3

void LCD_Init          (void);
void LCD_sendcmd       (unsigned char cmd);
void LCD_sendchar      (unsigned char data);
void LCD_sendstring    (const char *str);
void LCD_goto_xy       (unsigned char row, unsigned char col);
void LCD_sendstring_xy (unsigned char row, unsigned char col , const char *str);
void LCD_clear         (void);
void LCD_inttostring   (int data);


#endif