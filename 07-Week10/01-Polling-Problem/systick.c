#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

void SysTick_Init(uint32_t reload)
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = reload - 1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x05; // ENABLE | CLK_SRC
}

void SysTick_Wait(void)
{
    while ((NVIC_ST_CTRL_R & 0x00010000) == 0);
}

void DelayMs(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
        SysTick_Wait();
}
