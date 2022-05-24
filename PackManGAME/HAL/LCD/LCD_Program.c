#include "../../LIB/STD_TYPES.h"
#include<avr/io.h>
#include<util/delay.h>
#include "LCD_Interface.h"
#include "LCD_Configration.h"

void LCD_SendCom(u8 u8_Adata) {
	ControllPort = 0b00000000;
	DataPort = u8_Adata;
	ControllPort = 0b00000100;
	_delay_ms(1);
	ControllPort = 0b00000000;
	_delay_ms(1);
}

void LCD_Init(void) {
	DDR_DataPort = 0xff;
	DDR_ControllPort = 0xff;
	_delay_ms(50);
	LCD_SendCom(0b00111000);
	_delay_ms(1);
	LCD_SendCom(0b00001100);
	_delay_ms(1);
	LCD_SendCom(0b00000001);
	_delay_ms(3);
	LCD_SendCom(0b00000100);
	_delay_ms(3);
	LCD_SendCom(0b00000001);

}

void LCD_SendChar(u8 Char) {
	ControllPort = 0b00000001; //RS --->B0 //RW --->B1 //EN --->B2
	DataPort = Char;
	ControllPort = 0b00000101;
	_delay_ms(1);
	ControllPort = 0b00000001;
	_delay_ms(1);
}

void LCD_SendString(char Arr[]) {

	for (int i = 0; Arr[i] != '\0'; i++) {
		LCD_SendChar(Arr[i]);

	}
	return;
}

void LCD_SendIntNumb(int Numb) {
	int Numb_Size = 0;
	int Numb_Copy[3];
	for (Numb_Size = 0; Numb > 0; Numb_Size++) {
		Numb_Copy[Numb_Size] = Numb % 10;
		Numb /= 10;

	}
	Numb_Size -= 1;
	for (; Numb_Size >= 0; Numb_Size--) {
		LCD_SendChar('0'+Numb_Copy[Numb_Size] + 48);
	}
	return;
}

void LCD_Calculator(int Numb1, char opp, int Numb2) {
	switch (opp) {
	case '+':
		LCD_SendIntNumb(Numb1 + Numb2);
		break;
	case '-':
		if (Numb1 < Numb2) {
			LCD_SendChar('-');
			LCD_SendIntNumb(Numb2 - Numb1);

		} else {
			LCD_SendIntNumb(Numb1 - Numb2);
		}
		break;

	case '*':
		LCD_SendIntNumb(Numb1 * Numb2);
		break;
	case '/':
		LCD_SendIntNumb(Numb1 / Numb2);
		break;
	default:
		break;
	}

}
void LCD_voidGoto (u8 A_u8ROW,u8 A_u8COL){
	u8 L_u8DDRRAMAddress;
	u8 L_u8Command;

	if ((A_u8ROW <= 1) &&( A_u8COL <= 15))
	{
		if (A_u8ROW  == FIREST_ROW_IDX){
			L_u8DDRRAMAddress = FIREST_ROW_START + A_u8COL;
		}
		else
		{
			L_u8DDRRAMAddress = SECOND_ROW_START + A_u8COL;
		}
		L_u8Command = L_u8DDRRAMAddress | SET_AC_MASK;
		LCD_SendCom(L_u8Command);
	}
	else
	{
		//Do No thing
	}

}
void LCD_WriteToCGRAM (u8 A_u8PatternIdx , u8 *A_PatternVlaue )
{ u8 L_u8LoopIterator;

switch (A_u8PatternIdx)
{

case 0 :LCD_SendCom(0x40);break;
case 1 :LCD_SendCom(0x48);break;
case 2 :LCD_SendCom(0x56);break;
case 3 :LCD_SendCom(0x64);break;
case 4 :LCD_SendCom(0x72);break;
case 5 :LCD_SendCom(0x80);break;
case 6 :LCD_SendCom(0x88);break;
case 7 :LCD_SendCom(0x96);break;
default : break;
}



for(L_u8LoopIterator = 0; L_u8LoopIterator<8;L_u8LoopIterator++){

 		LCD_SendChar(A_PatternVlaue[L_u8LoopIterator]);
 	}

return;}
