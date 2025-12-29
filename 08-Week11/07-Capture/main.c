/******************************************************************************
 * File: main.c
 * Description: 32-bit GPTM Timer in Edge-Time Capture mode
 * Date: November 29, 2025
 ******************************************************************************/

#include "tm4c123gh6pm.h"
#include "dio.h"
#include <stdint.h>

/* LED Configuration */
#define LED_PORT        PORTF
#define LED_PIN         PIN1

/* Capture Pin Configuration - Timer0A CCP0 on PB6 */
#define CAPTURE_PORT    PORTB
#define CAPTURE_PIN     PIN6

/* Global Variables */
volatile uint32_t firstEdge = 0;
volatile uint32_t secondEdge = 0;
volatile uint32_t period = 0;
volatile uint8_t edgeCount = 0;

/* Function Prototypes */
void Timer0A_Capture_Init(void);
void PB6_Init(void);

int main(void)
{
    /* Initialize LED as output */
    DIO_Init(LED_PORT, LED_PIN, OUTPUT);
    DIO_WritePin(LED_PORT, LED_PIN, LOW);
    
    /* Initialize PB6 for Timer0A capture (CCP0) */
    PB6_Init();
    
    /* Initialize Timer0A in capture mode */
    Timer0A_Capture_Init();
    
    /* Main loop - polling mode */
    while(1)
    {
        /* Check if capture event occurred */
        if(TIMER0_RIS_R & 0x04)  /* Check CAERIS bit (Capture Mode Event) */
        {
            /* Clear the capture event flag */
            TIMER0_ICR_R = 0x04;
            
            if(edgeCount == 0)
            {
                /* First edge captured */
                firstEdge = TIMER0_TAR_R;
                edgeCount = 1;
            }
            else
            {
                /* Second edge captured */
                secondEdge = TIMER0_TAR_R;
                
                /* Calculate period (time between edges) */
                if(secondEdge > firstEdge)
                {
                    period = secondEdge - firstEdge;
                }
                else
                {
                    /* Handle timer overflow */
                    period = (0xFFFFFFFF - firstEdge) + secondEdge + 1;
                }
                
                /* Toggle LED to indicate capture */
                DIO_TogglePin(LED_PORT, LED_PIN);
                
                /* Reset for next measurement */
                edgeCount = 0;
            }
        }
    }
}

/******************************************************************************
 * Function: PB6_Init
 * Description: Initialize PB6 as Timer0A CCP0 input for capture mode
 * Parameters: None
 * Returns: None
 ******************************************************************************/
void PB6_Init(void)
{
    volatile uint32_t delay;
    
    /* Enable Port B clock */
    SYSCTL_RCGCGPIO_R |= 0x02;
    delay = SYSCTL_RCGCGPIO_R;
    
    /* Set PB6 direction as input */
    GPIO_PORTB_DIR_R &= ~0x40;
    
    /* Enable alternate function for PB6 */
    GPIO_PORTB_AFSEL_R |= 0x40;
    
    /* Configure PB6 for T0CCP0 (Timer0 Capture) - PMC7 = 7 */
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xF0FFFFFF) | 0x07000000;
    
    /* Enable digital function on PB6 */
    GPIO_PORTB_DEN_R |= 0x40;
}

/******************************************************************************
 * Function: Timer0A_Capture_Init
 * Description: Initialize Timer0A in 32-bit edge-time capture mode
 * Parameters: None
 * Returns: None
 ******************************************************************************/
void Timer0A_Capture_Init(void)
{
    volatile uint32_t delay;
    
    /* Enable Timer0 clock */
    SYSCTL_RCGCTIMER_R |= 0x01;
    delay = SYSCTL_RCGCTIMER_R;
    
    /* Disable Timer0A during setup */
    TIMER0_CTL_R &= ~0x01;
    
    /* Configure as 32-bit timer */
    TIMER0_CFG_R = 0x00;
    
    /* Configure Timer0A for Edge-Time Capture mode */
    TIMER0_TAMR_R = 0x17;  /* Bit 0-1: 11 (Capture mode)
                              Bit 2: 1 (Count up)
                              Bit 3: 0 (Capture mode not edge count)
                              Bit 4: 1 (Wait on Trigger disabled) */
    
    /* Configure for rising edge detection */
    TIMER0_CTL_R &= ~0x0C;  /* Clear TAEVENT bits */
    TIMER0_CTL_R |= 0x00;   /* 00 = positive edge */
    
    /* Set load value to maximum for free-running counter */
    TIMER0_TAILR_R = 0xFFFFFFFF;
    
    /* Clear any pending capture interrupt */
    TIMER0_ICR_R = 0x04;
    
    /* Enable Timer0A */
    TIMER0_CTL_R |= 0x01;
}
