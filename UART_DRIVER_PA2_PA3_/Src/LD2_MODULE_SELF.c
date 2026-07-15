
#include <stdint.h>

void ConfigureLD2(){
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
   //* pPortAOutRegstr |= (1 << 5);
}

/*
void BLINK_LD2(void){
	// INITIALIZE LD2
	ConfigureLD2();

	// TOGGLE LD2
    *pPortAOutRegstr ^= (1 << 5);
}
*/
