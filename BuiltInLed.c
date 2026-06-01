
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
/*
    // INITIALIZE LD2 ON STM32F446RE
    uint32_t * pClckCntrlRgstr = (uint32_t*) 0x40023830;
    uint32_t * pPortAModeRegstr = (uint32_t*) 0x40020000;
    uint32_t * pPortAOutRegstr = (uint32_t*) 0x40020014;

    //1. ENABLE CLOCK GPIO A PERIPHERAL IN AHB1ENR
    *pClckCntrlRgstr |= 0x01;

    //2. CONFIGURE MODE OF IO PIN AS OUTPUT
    //a. CLEAR THE REGISTER
    *pPortAModeRegstr &= 0xFFFFF3FF;

    //b. SET REGISTER AS GENERAL PURPOSE OUT
    *pPortAModeRegstr |= 0x0400;

    //3. SET 5TH BIT OF GPIO OUTPUT DATA REGISTER AS HIGH TO SET PIN 5 AS HIGH
    * pPortAOutRegstr |= 0X0020;
*/

     // INITIALIZE LD2 ON STM32F446RE USING BIT MANIPULATION
    uint32_t * pClckCntrlRgstr = (uint32_t*) 0x40023830;
    uint32_t * pPortAModeRegstr = (uint32_t*) 0x40020000;
    uint32_t * pPortAOutRegstr = (uint32_t*) 0x40020014;

    //1. ENABLE CLOCK GPIO A PERIPHERAL IN AHB1ENR
    *pClckCntrlRgstr |= 1;

    //2. CONFIGURE MODE OF IO PIN AS OUTPUT
    //a. CLEAR THE REGISTER
    *pPortAModeRegstr &= ~(3 << 10);

    //b. SET REGISTER AS GENERAL PURPOSE OUT
    *pPortAModeRegstr |= (1 << 10);

    //3. SET 5TH BIT OF GPIO OUTPUT DATA REGISTER AS HIGH TO SET PIN 5 AS HIGH
    * pPortAOutRegstr |= (1 << 5);

    while (1);

}
