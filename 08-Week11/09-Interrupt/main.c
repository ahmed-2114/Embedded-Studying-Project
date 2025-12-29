/******************************************************************************
 * File: main.c
 * Description: 32-bit GPTM Timer in periodic mode with LED toggle (Interrupt)
 * Date: December 6, 2025
 ******************************************************************************/

#include "tm4c123gh6pm.h"
#include "dio.h"
#include <stdint.h>

/* LED Configuration */
#define LED_PORT        PORTF
#define LED_PIN         PIN1

/* Function Prototypes */
void Timer0A_Init(void);
void Timer0A_Handler(void);

int main(void)
{
    /* Initialize LED as output */
    DIO_Init(LED_PORT, LED_PIN, OUTPUT);
    DIO_WritePin(LED_PORT, LED_PIN, LOW);
    
    /* Initialize Timer0A for 0.5 second periodic interrupts */
    Timer0A_Init();
    
    /* Main loop - interrupt mode (no polling needed) */
    while(1)
    {
        /* CPU can be put to sleep or perform other tasks */
        /* LED toggling is handled in interrupt service routine */
    }
}

/******************************************************************************
 * Function: Timer0A_Init
 * Description: Initialize Timer0A in 32-bit periodic mode with interrupts
 * Parameters: None
 * Returns: None
 ******************************************************************************/
void Timer0A_Init(void)
{
    volatile uint32_t delay;
    
    /* Enable Timer0 clock */
    SYSCTL_RCGCTIMER_R |= 0x01;
    delay = SYSCTL_RCGCTIMER_R;
    
    /* Disable Timer0A during setup */
    TIMER0_CTL_R &= ~0x01;
    
    /* Configure as 32-bit timer */
    TIMER0_CFG_R = 0x00;
    
    /* Set periodic mode, count down */
    TIMER0_TAMR_R = 0x02;
    
    /* Load interval value for 1 second delay */
    /* System clock = 16 MHz, 1 sec = 16,000,000 cycles */
    TIMER0_TAILR_R = 16000000 - 1;
    
    /* Clear timeout flag */
    TIMER0_ICR_R = 0x01;
    
    /* Enable timeout interrupt for Timer0A */
    TIMER0_IMR_R |= 0x01;
    
    /* Enable Timer0A interrupt in NVIC (IRQ 19) */
    /* Timer0A is interrupt number 19, so use bit 19 in NVIC_EN0_R */
    NVIC_EN0_R |= (1 << 19);
    
    /* Enable Timer0A */
    TIMER0_CTL_R |= 0x01;
}

/******************************************************************************
 * Function: Timer0A_Handler
 * Description: Timer0A interrupt service routine - toggles LED
 * Parameters: None
 * Returns: None
 ******************************************************************************/
void Timer0A_Handler(void)
{
    /* Clear the timeout flag */
    TIMER0_ICR_R = 0x01;
    
    /* Toggle LED */
    DIO_TogglePin(LED_PORT, LED_PIN);
}
