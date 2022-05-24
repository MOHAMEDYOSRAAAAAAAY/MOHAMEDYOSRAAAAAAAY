/*
 * main.c
 *
 *  Created on: May 19, 2022
 *      Author: YOSRY
 */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/DIO/DIO_Interface.h"
#include <util/delay.h>
#include <avr/io.h>
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/LCD/LCD_Configration.h"
u8 Animation = 0;
void packManUpdate(u8 A_u8new_pos);
void EnmiUpdate(void);
u8 Get_Bot(void);
#define SEED 0b10100101
#define BLOCK 0b11111111
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define ELSE 4
#define SEEDNUMBER 10
u8 pacMan_Pos[2]={0,0};
u8 Enmi_Pos[2]={1,5};
u8	static Seed_Arr[SEEDNUMBER][3] = {
		{0,1,1},{0,2,1},{0,3,1},{0,7,1},{0,8,1},{0,9,1},{1,8,1},{1,9,1},{1,10,1},{1,11,1}
};
u8 Points =0;
void Clear_Blok(u8 *POS);
void END_GAME (void);
void Seed(void);
void Block(void);
int main(void) {
	u8 Packman1[] = {0x00, 0x0E, 0x1F, 0x1C, 0x1C, 0x1F, 0x0E, 0x00};
	u8 Packman2[] = {0x00, 0x0E, 0x1F, 0x1D, 0x1F, 0x1F, 0x0E, 0x00};
	u8 Packman3[] = {0x00, 0x0E, 0x1F, 0x07, 0x07, 0x1F, 0x0E, 0x00};
LCD_Init();
DDRD = 0x00;
PORTD=0xff;

LCD_WriteToCGRAM(0,Packman1);
_delay_ms(50);
LCD_WriteToCGRAM(1,Packman2);
_delay_ms(50);
LCD_WriteToCGRAM(3,Packman3);
_delay_ms(50);
LCD_CLEAR;

while (1)
	{
	packManUpdate(Get_Bot());

EnmiUpdate();

_delay_ms(50);
Seed ();
Block();
END_GAME ();
	}

	return 0;
}
void EnmiUpdate(void)
{u8 static direction = 1;
u8 static Speed = 7;
u8  En_animation =0;
	if(Speed <= 7){Speed ++;}
	else{
Clear_Blok(Enmi_Pos);
if(direction ==1){
Enmi_Pos[1]++;
if	(Enmi_Pos[1] ==12){
	direction =0;
	En_animation = 0;
}

}
if(direction == 0){
	Enmi_Pos[1]--;
	if	(Enmi_Pos[1] ==6){
		direction =1;
		En_animation = 3;
	}

}
Speed =0;
}
LCD_voidGoto(Enmi_Pos[0],Enmi_Pos[1]);
LCD_SendChar(En_animation);
}
void packManUpdate(u8 A_u8new_pos)
{u8 static Speed = 0;
if(Speed <= 5){Speed ++;}
else{
	LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);

	switch(A_u8new_pos){
case RIGHT : if((pacMan_Pos[1] >= 15)||((pacMan_Pos[1] == 4)&&pacMan_Pos[0] == 0)){/*do no thing*/}
else{LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
LCD_SendChar(0b11111110);
LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
	LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]+1);pacMan_Pos[1]+=1;break;
}break;
case LEFT : if((pacMan_Pos[1] == 0)||((pacMan_Pos[1] == 6)&&pacMan_Pos[0] == 0)){/*do no thing*/}

else{LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
LCD_SendChar(0b11111110);
LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]-1);pacMan_Pos[1]-=1;break;
}break;
case UP :
	if((pacMan_Pos[0] == 0)||((pacMan_Pos[1] == 5)&&pacMan_Pos[0] == 1)){/*do no thing*/}
	else{LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
	LCD_SendChar(0b11111110);
	LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
	LCD_voidGoto(pacMan_Pos[0]-1,pacMan_Pos[1]);pacMan_Pos[0]-=1;break;
	}break;
case DOWN :if(pacMan_Pos[0] == 1){/*do no thing*/}
else{LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
LCD_SendChar(0b11111110);
LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
	LCD_voidGoto(pacMan_Pos[0]+1,pacMan_Pos[1]);pacMan_Pos[0]+=1;break;
}break;

default :break;
}
if(Animation ==1){	Animation = 0;}
else if(Animation ==0){	Animation = 1;}
LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);
LCD_SendChar(Animation);
LCD_voidGoto(pacMan_Pos[0],pacMan_Pos[1]);}
return;
}
u8 Get_Bot(void)
{
if(Get_Bit(PIND,0)==0){while(Get_Bit(PIND,0)==0){}_delay_ms(10);return RIGHT;}
if(Get_Bit(PIND,1)==0){while(Get_Bit(PIND,1)==0){}_delay_ms(10);return LEFT; }
if(Get_Bit(PIND,2)==0){while(Get_Bit(PIND,2)==0){}_delay_ms(10);return UP; }
if(Get_Bit(PIND,3)==0){while(Get_Bit(PIND,3)==0){}_delay_ms(10);return DOWN; }
else if(1){ return ELSE;}
}
void Clear_Blok(u8 *POS){
LCD_voidGoto(POS[0],POS[1]);
LCD_SendChar(0b11111110);
LCD_voidGoto(POS[0],POS[1]);
}
void END_GAME (void)
{	if ((pacMan_Pos[0] == Enmi_Pos[0]) && (pacMan_Pos[1] == Enmi_Pos[1])){

	LCD_CLEAR;
	LCD_voidGoto(0,3);
	LCD_SendString("GAME OVER");
	LCD_voidGoto(1,0);
	LCD_SendString("PRESS RESET POT");
	pacMan_Pos[0]=0;
	pacMan_Pos[1] =0;
	for(int  i = 0; i<SEEDNUMBER; i++){
				Seed_Arr[i][2]=1;}
	Points =0;
	while(Get_Bit(PIND,4)==1){}
	LCD_CLEAR;

}else {}

if(Points ==SEEDNUMBER){
	LCD_voidGoto(0,3);
		LCD_SendString("YOU WIN");
		LCD_voidGoto(1,0);
		LCD_SendString("PRESS RESET POT");
		Points =0;
		for(int  i = 0; i<SEEDNUMBER; i++){
			Seed_Arr[i][2]=1;}
		while(Get_Bit(PIND,4)==1){}
		LCD_CLEAR;

}


}
void Seed (void){

for(int  i = 0; i<SEEDNUMBER; i++){
	if(Seed_Arr[i][2]==1){
	LCD_voidGoto(Seed_Arr[i][0],Seed_Arr[i][1]);
	LCD_SendChar(SEED);
	if((Seed_Arr[i][0]== pacMan_Pos[0])&&(Seed_Arr[i][1]== pacMan_Pos[1])){
			Seed_Arr[i][2]=0;
			Points ++;

	}
	else{}


	}
}


LCD_voidGoto(0,14);
LCD_SendIntNumb(Points);

}
void Block (void){
	LCD_voidGoto(0,5);
	LCD_SendChar(BLOCK);
}
