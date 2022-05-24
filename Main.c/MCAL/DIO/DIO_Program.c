/*
 * DIO_Program.c
 *
 *  Created on: Aug 23, 2021
 *      Author: Start1
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Privet.h"
#include "DIO_Config.h"
#include "DIO_Interface.h"
void DIO_SetPin(u8 Port,u8 Pin,u8 Value){
	if (Value ==1){
	switch (Port){
	case 0:Set_Bit(PORTA , Pin);break;
	case 1:Set_Bit(PORTB , Pin);break;
	case 2:Set_Bit(PORTC , Pin);break;
	case 3:Set_Bit(PORTD , Pin);break;
	}
	}
	else{
		switch (Port){
case 0:Clr_Bit(PORTA , Pin);break;
	case 1:Clr_Bit(PORTB , Pin);break;
	case 2:Clr_Bit(PORTC , Pin);break;
	case 3:Clr_Bit(PORTD , Pin);break;	}
	}}
void DIO_SetPort(u8 Port, u8 Value){

	switch (Port){
		case 0:PORTA = Value;break;
		case 1:PORTB = Value;break;
		case 2:PORTC = Value;break;
		case 3:PORTD = Value;break;
}}
void DIO_TogPin(u8 Port, u8 Pin){
		switch (Port){
				case 0:Tog_Bit(PORTA,Pin);break;
				case 1:Tog_Bit(PORTB,Pin);break;
				case 2:Tog_Bit(PORTC,Pin);break;
				case 3:Tog_Bit(PORTD,Pin);break;


		}
}
u8 DIO_GetPin(u8 Port, u8 Pin){
			u8 x=0;
			switch (Port){
		case 0:x=Get_Bit(PORTA,Pin);break;
						case 1:x= Get_Bit(PORTB,Pin);break;
						case 2:x=Get_Bit(PORTC,Pin);break;
						case 3:x=Get_Bit(PORTD,Pin);break;

	}return x;
		}
u8 DIO_GetPort(u8 Port){
			u8 x=0;
			switch (Port){
		case 0:x=PORTA;break;
						case 1:x=PORTB;break;
						case 2:x=PORTC;break;
						case 3:x=PORTD;break;

	}return x;
}

void DIO_PinDirection(u8 Port,u8 Pin ,u8 Dir){
	if (Dir ==1){
		switch (Port){
		case 0:Set_Bit(DDRA , Pin);break;
		case 1:Set_Bit(DDRB , Pin);break;
		case 2:Set_Bit(DDRC , Pin);break;
		case 3:Set_Bit(DDRD , Pin);break;
		}
	}
	else {
			switch (Port){
			case 0: Set_Bit(DDRA , Pin);break;
			case 1:Set_Bit(DDRB , Pin);break;
			case 2:Set_Bit(DDRC , Pin);break;
			case 3:Set_Bit(DDRD , Pin);break;
			}

}}
	void DIO_PortDirection(u8 Port ,u8 Dir){
		if(Dir==1){
		switch (Port){
				case 0:DDRA=0xff;break;
				case 1:DDRB=0xff;break;
				case 2:DDRC=0xff;break;
				case 3:DDRD=0xff;break;
				}
		}

		else{

			switch (Port){
            case 0: DDRA=0x00;break;
			case 1: DDRB=0x00;break;
			case 2: DDRC=0x00;break;
			case 3: DDRD=0x00;break;
			}
		}
	}










