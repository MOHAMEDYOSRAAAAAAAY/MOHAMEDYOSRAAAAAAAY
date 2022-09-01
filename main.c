#include "MCAL/LIB/BIT_MATH.h"
#include "MCAL/LIB/STD_TYPES.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/TIMERS/TIMERS_int.h"
#include "MCAL/I2C/I2C_Interface.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/ADC/ADC_int.h"
#include <avr/io.h>
#include "util/delay.h"
#include "MCAL/GIE/GIE_InterFace.h"
void Send_Bright(void);
void FanSpeed(void);
u8	Bright_level;
u8 UART_VAR;
u8 SwitchState[3]={0,0,0};
u8 Empty_stat;
void Smart_Home_Update(void);
u8* String = "Welcome To The System" ;
int main (void){
	DIO_PinDirection(DIO_PORTC,DIO_PIN1,DIO_OUTPUT_PIN);
	DIO_PinDirection(DIO_PORTC,DIO_PIN0,DIO_OUTPUT_PIN);

	DIO_PortDirection(DIO_PORTB,DIO_OUTPUT_PORT);
	DIO_PinDirection(DIO_PORTC,DIO_PIN7,DIO_INPUT_PIN);

MADC_vInit();
MTIMERS_vInit();
MTIMERS_vStartTimer(TIMER0);
UART_Init();


UART_WritString(String);
while (1){
Smart_Home_Update();

}
}
void Send_Temp(void){
 u16 raw_temp=MADC_u16AnalogRead(CHANNEL_00);
	raw_temp = (raw_temp * 5.0 / 1024) * 100;
	UART_SendNumber(raw_temp);
	DIO_SetPin(DIO_PORTC,DIO_PIN0,DIO_HIGH);
	DIO_SetPin(DIO_PORTC,DIO_PIN1,DIO_HIGH);
	_delay_ms(1000);
}
void Send_Bright(void){
	u16 Bright = MADC_u16AnalogRead(CHANNEL_01);
	u8 string ;

	if (Bright <=30 ){
		 string = "the Brightness is LOW ";
		 UART_WritString(string);
		 Bright_level = 0;
		}
	else if (Bright >=30 && Bright <=500 ){
		string = "the Brightness is Medium ";
		UART_WritString(string);
		Bright_level = 1;
	}
	else if (Bright >=500 ){
			string = "the Brightness is HIGH ";
					 UART_WritString(string);
						Bright_level = 2;
		}

	DIO_SetPin(DIO_PORTC,DIO_PIN0,DIO_LOW);
		DIO_SetPin(DIO_PORTC,DIO_PIN1,DIO_HIGH);}
void FanSpeed(void){
	u8 Arr[4] = {0};

UART_ReadString(Arr);
if (Arr[1]=='#'){
	Arr[0] = Arr[0] -48;
UART_SendNumber(Arr[0]);
MTIMERS_vSetCompareValue(TIMER0,Arr[0]);}
else if (Arr[2]=='#'){
	Arr[0] = ((Arr[0]-48)*10) + (Arr[1]-48);
	UART_SendNumber(Arr[0]);
	MTIMERS_vSetCompareValue(TIMER0,Arr[0]);}
else if (Arr[3]=='#'){
	Arr[0] = ((Arr[0]-48)*100) + ((Arr[1]-48)*10) + (Arr[2]-48);
	UART_SendNumber(Arr[0]);
	MTIMERS_vSetCompareValue(TIMER0,Arr[0]);}
}
void Smart_Home_Update(void){
	UART_VAR =UART_Get();
	switch(UART_VAR){
	case 'R' :
		String = "The Temperature is :";
		UART_WritString(String);
				Send_Temp();break;
	case 'Y' :Send_Bright();break;
	case 'G' :if(SwitchState[0] ==1){
	DIO_SetPin(DIO_PORTB,DIO_PIN0,DIO_LOW);
	DIO_SetPin(DIO_PORTC,DIO_PIN0,DIO_HIGH);
			DIO_SetPin(DIO_PORTC,DIO_PIN1,DIO_LOW);

	_delay_ms(300);
	DIO_SetPin(DIO_PORTB,DIO_PIN0,DIO_HIGH);

		}break;
	case 'E' : break;//Auto mode
	case 'A' :DIO_SetPin(DIO_PORTB,DIO_PIN0,DIO_HIGH);SwitchState[0]=1;
	DIO_SetPin(DIO_PORTC,DIO_PIN0,DIO_HIGH);
	DIO_SetPin(DIO_PORTC,DIO_PIN1,DIO_LOW);
	break;
	case 'a' :DIO_SetPin(DIO_PORTB,DIO_PIN0,DIO_LOW);SwitchState[0]=0; break;
	case 'B' :DIO_SetPin(DIO_PORTB,DIO_PIN1,DIO_HIGH);SwitchState[1]=1; break;
	case 'b' :DIO_SetPin(DIO_PORTB,DIO_PIN1,DIO_LOW);SwitchState[1]=0; break;
	case 'C' :DIO_SetPin(DIO_PORTB,DIO_PIN2,DIO_HIGH);SwitchState[2]=1; break;
	case 'c' :DIO_SetPin(DIO_PORTB,DIO_PIN2,DIO_LOW);SwitchState[2]=0; break;
	case 'D' :DIO_SetPin(DIO_PORTB,DIO_PIN2,DIO_HIGH);SwitchState[2]=1; break;
	case 'd' :DIO_SetPin(DIO_PORTB,DIO_PIN2,DIO_LOW);SwitchState[2]=0; break;
	case 'S' :if(SwitchState[2] ==1){FanSpeed();}break;

default :break;
}

if(Get_Bit(PINC,7)==0){

String = "*LR0G0B0*";
if(Empty_stat ==1){

	Empty_stat = 0;
	UART_Send('L');
	UART_WritString(String);}
}

else if (Get_Bit(PINC,7)==1){
	String = "*LR255G255B0*";
	if(Empty_stat ==0){

		Empty_stat = 1;
		UART_Send('L');
		UART_WritString(String);}
}
DIO_SetPin(DIO_PORTC,DIO_PIN0,DIO_LOW);
	DIO_SetPin(DIO_PORTC,DIO_PIN1,DIO_LOW);

}



