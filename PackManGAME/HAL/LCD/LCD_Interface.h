/*
 * LCD_Interface.h
 *
 *  Created on: Aug 25, 2021
 *      Author: Start1
 */

#ifndef HAL_LCD_INTERFACE_H_
#define HAL_LCD_INTERFACE_H_
#define LCD_CLEAR LCD_SendCom(0x01)
#define FIREST_ROW_IDX 0
#define SECOND_ROW_IDX 1
#define FIREST_ROW_START 0x00
#define SECOND_ROW_START 0x40
#define SET_AC_MASK 0x80
#include "../../LIB/STD_TYPES.h"
//P0=D0
//RS=P0   RW=P1 EN=P2
void LCD_Init(void);
void LCD_SendCom(u8 u8_Adata);
void LCD_SendChar(u8 Char);
void LCD_SendString(char Arr[]);
void LCD_SendIntNumb(int Numb);
void LCD_Calculator(int ,  char, int);
void LCD_voidGoto (u8 A_u8ROW,u8 A_u8COL);
void LCD_WriteToCGRAM (u8 A_u8PatternIdx , u8 *A_PatternVlaue );
void LCD_voidGoto (u8 A_u8ROW,u8 A_u8COL);

#endif /* HAL_LCD_INTERFACE_H_ */
