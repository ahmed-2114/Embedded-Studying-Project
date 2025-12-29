#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

// Heavy CPU workload (simulating a long calculation)
void HeavyTask(void)
{
    volatile uint32_t i;
    for (i = 0; i < 8000000; i++);
}

int main(void)
{
    // Enable Port F clock
    SYSCTL_RCGCGPIO_R 	|= (1U << 5);

    // Configure PF2 as output (Blue LED)
    GPIO_PORTF_DIR_R	|= (1U << 2);
    GPIO_PORTF_DEN_R 	|= (1U << 2);

    // SysTick: 1 ms tick => reload = 16,000 for 16 MHz
    SysTick_Init(16000);

    while (1)
    {
        // Toggle LED
        GPIO_PORTF_DATA_R ^= (1U << 2);
	
	// Should toggle every 500 ms
        DelayMs(500);

        // Add heavy task will cause visible delay
        HeavyTask();
    }
}
