#include <stdint.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    //-------------------------------------------
    // Enable Port F Clock
    //-------------------------------------------
    SYSCTL_RCGCGPIO_R |= 0x20;

    //-------------------------------------------
    // Configure PF1 (Red LED)
    //-------------------------------------------
    GPIO_PORTF_DIR_R |= (1 << 1);
    GPIO_PORTF_DEN_R |= (1 << 1);

    //-------------------------------------------
    // SysTick Initialization (NO INTERRUPTS)
    //-------------------------------------------
    NVIC_ST_CTRL_R = 0;                 // Disable SysTick
    NVIC_ST_RELOAD_R = 16000 - 1;       // Reload for 1 ms (16 MHz)
    NVIC_ST_CURRENT_R = 0;              // Clear current
    NVIC_ST_CTRL_R = 0x05;              // ENABLE + CLK_SRC, no interrupt

    //-------------------------------------------
    // Main Loop
    //-------------------------------------------
    while (1)
    {
        // Toggle Red LED
        GPIO_PORTF_DATA_R ^= (1 << 1);

        // Delay 500ms
        for (uint32_t ms = 0; ms < 500; ms++)
        {
            // Wait for COUNTFLAG
            while ((NVIC_ST_CTRL_R & (1 << 16)) == 0);
        }
    }
}
