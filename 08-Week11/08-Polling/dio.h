/******************************************************************************
 * Module: DIO (Digital Input/Output)
 * File Name: dio.h
 * Description: Simple header file for TM4C123GH6PM GPIO Driver
 * Author: Embedded Systems Team
 * Date: November 22, 2025
 ******************************************************************************/

#ifndef DIO_H_
#define DIO_H_

#include <stdint.h>

/******************************************************************************
 *                              Definitions                                    *
 ******************************************************************************/

/* Port Definitions */
#define PORTA       0
#define PORTB       1
#define PORTC       2
#define PORTD       3
#define PORTE       4
#define PORTF       5

/* Pin Definitions */
#define PIN0        0
#define PIN1        1
#define PIN2        2
#define PIN3        3
#define PIN4        4
#define PIN5        5
#define PIN6        6
#define PIN7        7

/* Direction Definitions */
#define INPUT       0
#define OUTPUT      1

/* Pin Level Definitions */
#define LOW         0
#define HIGH        1

/* Enable/Disable Options */
#define ENABLE      1
#define DISABLE     0

/******************************************************************************
 *                              Function Prototypes                            *
 ******************************************************************************/

/* Initialize a GPIO pin */
void DIO_Init(uint8_t port, uint8_t pin, uint8_t direction);

/* Write a value to a GPIO pin (1 = HIGH, 0 = LOW) */
void DIO_WritePin(uint8_t port, uint8_t pin, uint8_t value);

/* Read the value of a GPIO pin */
uint8_t DIO_ReadPin(uint8_t port, uint8_t pin);

/* Toggle a GPIO pin */
void DIO_TogglePin(uint8_t port, uint8_t pin);

/* Enable Pull-Up Resistor on a pin */
void DIO_SetPUR(uint8_t port, uint8_t pin, uint8_t enable);

/* Enable Pull-Down Resistor on a pin */
void DIO_SetPDR(uint8_t port, uint8_t pin, uint8_t enable);

#endif /* DIO_H_ */
