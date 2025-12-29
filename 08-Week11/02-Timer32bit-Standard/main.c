/******************************************************************************
 * File: main.c
 * Description: 32-bit GPTM Timer in periodic mode with LED toggle (Polling)
 * Date: November 29, 2025
 ******************************************************************************/

#include "tm4c123gh6pm.h"
#include "dio.h"
#include <stdint.h>

/* LED Configuration */
#define LED_PORT        PORTF
#define LED_PIN         PIN1

/* Function Prototypes */
void Timer0A_Init(void);

int main(void)
{
    /* Initialize LED as output */
    DIO_Init(LED_PORT, LED_PIN, OUTPUT);
    DIO_WritePin(LED_PORT, LED_PIN, LOW);
    
    /* Initialize Timer0A for 1 second periodic interrupts */
    Timer0A_Init();
    
    /* Main loop - polling mode */
    while(1)
    {
        /* Check if timer timeout flag is set */
        if(TIMER0_RIS_R & 0x01)
        {
            /* Clear the timeout flag */
            TIMER0_ICR_R = 0x01;
            
            /* Toggle LED */
            DIO_TogglePin(LED_PORT, LED_PIN);
        }
    }
}

/******************************************************************************
 * Function: Timer0A_Init
 * Description: Initialize Timer0A in 32-bit periodic mode
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
    
    /* Set periodic mode, count up */
    TIMER0_TAMR_R = 0x12;
    
    /* Load interval value for 1 second delay */
    /* System clock = 16 MHz, 1 sec = 16,000,000 cycles */
    TIMER0_TAILR_R = 100;
    TIMER0_TAV_R = 0;
    
    /* Clear timeout flag */
    TIMER0_ICR_R = 0x01;
    
    /* Enable Timer0A */
    TIMER0_CTL_R |= 0x03;
}
