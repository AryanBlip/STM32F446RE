/*
void LD2_ON(){
    //3. SET 5TH BIT OF GPIO OUTPUT DATA REGISTER AS HIGH TO SET PIN 5 AS HIGH
    * pPortAOutRegstr |= (1 << 5);
}

void LD2_OFF(){
	//4. SET 5TH BIT OF GPIO OUTPUT DATA REGISTER AS LOW TO SET PIN 5 AS LOW
	 * pPortAOutRegstr &= ~(1 << 5);
}
*/



#include <stdint.h>

void configureLD2(void){

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

//	// Toggle Pin 5 (XOR operation: 0 becomes 1, 1 becomes 0)
//	*pPortAOutRegstr ^= (1 << 5);
}
