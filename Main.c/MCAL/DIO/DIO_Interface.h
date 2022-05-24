/*
 * DIO_Interface.h
 *
 *  Created on: Aug 23, 2021
 *      Author: Start1
 */
#include "STD_TYPES.h"
#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_
void DIO_SetPin(u8 Port,u8 Pin,u8 Value);
void DIO_SetPort(u8 Port, u8 Value);
void DIO_TogPin(u8 Port, u8 Pin);
u8 DIO_GetPin(u8 Port, u8 Pin);
u8 DIO_GetPort(u8 Port);
void DIO_PortDirection(u8 Port ,u8 Dir);
void DIO_PinDirection(u8 Port,u8 Pin ,u8 Dir);

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_LOW 0
#define DIO_HIGH 1
#define DIO_OUTPUT_PORT 1
#define DIO_INPUT_PORT 0
#define DIO_OUTPUT_PIN 1
#define DIO_INPUT_PIN 0
#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
