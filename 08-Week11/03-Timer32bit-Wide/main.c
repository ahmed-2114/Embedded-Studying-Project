/******************************************************************************
 * File: main.c
 * Description: 32-bit Wide Timer in periodic mode with LED toggle (Polling)
 * Date: November 29, 2025
 ******************************************************************************/

#include "tm4c123gh6pm.h"
#include "dio.h"
#include <stdint.h>

/* LED Configuration */
#define LED_PORT        PORTF
#define LED_PIN         PIN1

/* Function Prototypes */
void WideTimer2_Init(void);

int main(void)
{
    /* Initialize LED as output */
    DIO_Init(LED_PORT, LED_PIN, OUTPUT);
    DIO_WritePin(LED_PORT, LED_PIN, LOW);
    
    /* Initialize Wide Timer2 for 1 second periodic operation */
    WideTimer2_Init();
    
    /* Main loop - polling mode */
    while(1)
    {
        /* Check if timer timeout flag is set */
        if(WTIMER2_RIS_R & 0x01)
        {
            /* Clear the timeout flag */
            WTIMER2_ICR_R = 0x01;
            
            /* Toggle LED */
            DIO_TogglePin(LED_PORT, LED_PIN);
        }
    }
}

/******************************************************************************
 * Function: WideTimer2_Init
 * Description: Initialize Wide Timer2 in 32-bit wide periodic mode
 * Parameters: None
 * Returns: None
 ******************************************************************************/
void WideTimer2_Init(void)
{
    volatile uint32_t delay;
    
    /* Enable Wide Timer2 clock */
    SYSCTL_RCGCWTIMER_R |= 0x04;  /* Enable Wide Timer2 */
    delay = SYSCTL_RCGCWTIMER_R;
    
    /* Disable Wide Timer2A during setup */
    WTIMER2_CTL_R &= ~0x01;
    
    /* Configure as 32-bit wide timer (not 64-bit) */
    WTIMER2_CFG_R = 0x04;  /* 32-bit RTC/Wide mode */
    
    /* Set periodic mode, count down */
    WTIMER2_TAMR_R = 0x02;
    
    /* Load interval value for 1 second delay */
    /* System clock = 16 MHz, 1 sec = 16,000,000 cycles */
    WTIMER2_TAILR_R = 16000000 - 1;
    
    /* Clear timeout flag */
    WTIMER2_ICR_R = 0x01;
    
    /* Enable Wide Timer2A */
    WTIMER2_CTL_R |= 0x01;
}
