#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

// External variable from systick.c
extern volatile uint32_t msTicks;

void HeavyTask(void)
{
    volatile uint32_t i;
    for (i = 0; i < 8000000; i++){}
}

int main(void)
{
    SYSCTL_RCGCGPIO_R |= (1U << 5);

    GPIO_PORTF_DIR_R |= (1U << 2);
    GPIO_PORTF_DEN_R |= (1U << 2);

    // ===== CHOOSE MODE =====
    
    // MODE 1: POLLING - LED toggle in main loop (affected by HeavyTask)
    // SysTick_Init(16000, SYSTICK_NOINT);
    
    // MODE 2: INTERRUPT - LED toggle in ISR above (NOT affected by HeavyTask)
    SysTick_Init(16000, SYSTICK_INT);
    
    while (1)
    {
        // Simulate heavy processing
        // In INTERRUPT mode: LED blinks precisely every 500ms despite HeavyTask!
        HeavyTask();
    }
}

// SysTick Interrupt Handler - called automatically every 1ms
void SystickHandler(void)
{
    static volatile uint32_t counter = 0;
    
    msTicks++;  // Update time counter
    
    counter++;
    if (counter >= 500)  // Every 500ms
    {
        GPIO_PORTF_DATA_R ^= (1U << 2);  // Toggle blue LED
        counter = 0;
    }
}