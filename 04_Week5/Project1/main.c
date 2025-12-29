#include "tm4c123gh6pm.h"
int main()
{
  SYSCTL_RCGCGPIO_R |= (1<<5);
  GPIO_PORTF_DIR_R |= ((1<<1) | (1<<2) | (1<<3));
  GPIO_PORTF_DEN_R |= ((1<<1) | (1<<2) | (1<<3));
  
  while(1){
//    *((unsigned int *)0x400253FC) |= (1<<1);
//    for(int i = 0; i<1600000; i++){}
//    *((unsigned int *)0x400253FC) &= ~(1<<1);
//    for(int i = 0; i<1600000; i++){}
    GPIO_PORTF_DATA_R ^= (1<<1);
    for(int i = 0; i<1600000; i++){}    
    
  }
}