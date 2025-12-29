#include "tm4c123gh6pm.h"

// we have 2 buttons , on PORTF, PF0, PF4
int main()
{
  // 1. enable and provide a clock for portf
  SYSCTL_RCGCGPIO_R |= (1<<5);
  // 2. set direction of the bits of desired pins to output
  GPIO_PORTF_DIR_R  |= ((1<<1) | (1<<2) | (1<<3));
  // 3. what kind of signal do you need?
  GPIO_PORTF_DEN_R  |= ((1<<1) | (1<<2) | (1<<3) | (1<<4));
  // 4. configure PULL up
  GPIO_PORTF_PUR_R  |= (1<<4);
  
  while(1){
    if( ((GPIO_PORTF_DATA_R >> 4) & 0x1) == 0 ){
      for (int i =0 ;i<20*1600; i++){}
      GPIO_PORTF_DATA_R ^= (1<<1);
      while( ((GPIO_PORTF_DATA_R >> 4) & 0x1) == 0 ){}
      for (int i =0 ;i<20*1600; i++){}
    }
  }
}