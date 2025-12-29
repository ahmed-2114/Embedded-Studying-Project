#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

void SysTick_Init(uint32_t reload);
void SysTick_Wait(void);
void DelayMs(uint32_t ms);

#endif
