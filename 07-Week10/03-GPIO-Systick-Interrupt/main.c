/******************************************************************************
 * File Name: main.c
 * Description: Interrupt-based GPIO and SysTick example
 * Date: November 22, 2025
 ******************************************************************************/

#include "dio.h"
#include "systick.h"
#include "tm4c123gh6pm.h"

int main(void)
{
    /* Initialize Red LED as output */
    DIO_Init(PORTF, PIN1, OUTPUT);      /* Red LED */
    DIO_Init(PORTF, PIN3, OUTPUT);      /* Green LED */
    
    /* Initialize SW1 (PF4) as input */
    DIO_Init(PORTF, PIN4, INPUT);
    
    /* Enable pull-up resistor for SW1 (active low) */
    DIO_SetPUR(PORTF, PIN4, ENABLE);
    
    /* Configure GPIO Port F Interrupt for SW1 (PF4) */
    GPIO_PORTF_IS_R &= ~(1 << PIN4);     /* Edge-sensitive */
    GPIO_PORTF_IBE_R &= ~(1 << PIN4);    /* Single edge */
    GPIO_PORTF_IEV_R &= ~(1 << PIN4);    /* Falling edge (button press) */
    GPIO_PORTF_ICR_R |= (1 << PIN4);     /* Clear any prior interrupt */
    GPIO_PORTF_IM_R |= (1 << PIN4);      /* Unmask interrupt */
    
    /* Enable GPIO Port F interrupt in NVIC (Interrupt 30) */
    NVIC_EN0_R |= (1 << 30);
    
    /* Set GPIO Port F priority to 2 (higher priority, lower number) */
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | (2 << 21);
    
    /* Initialize SysTick for 1 second interrupt (16MHz / 16000000 = 1 sec) */
    SysTick_Init(16000000, SYSTICK_INT);
    
    /* Set SysTick priority to 3 (lower priority, higher number) */
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | (3 << 29);
    
    /* Enable global interrupts */
    __asm("  CPSIE I");
    
    /* Main loop - all work done in interrupt handlers */
    while(1)
    {
        /* CPU can sleep or do other work here */
    }
}

/* GPIO Port F Interrupt Handler - Toggles Red LED when SW1 is pressed */
void GPIOPortF_Handler(void)
{
    /* Check if PF4 (SW1) caused the interrupt */
    if (GPIO_PORTF_MIS_R & (1 << PIN4))
    {
        /* Toggle Red LED */
        DIO_TogglePin(PORTF, PIN1);
        
        /* Clear the interrupt flag */
        GPIO_PORTF_ICR_R |= (1 << PIN4);
	
	/* Toggle Red LED */
        DIO_TogglePin(PORTF, PIN1);
	
	/* Toggle Red LED */
        DIO_TogglePin(PORTF, PIN1);
    }
}
