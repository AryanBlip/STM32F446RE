

#include <stdint.h>
#include "stm32fxx.h"

void ConfigureLD2();


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/*
 INIT CLOCKS
 ALL CLOCKS REQUIRED ARE INITIALIZED HERE
 */
void initClocks(void){
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC_APB1ENR |= RCC_APB1ENR_USART2EN;
}

/*
 CONFIG PINMODE
 CONFIGURE MDOES OF PIN
 */
void configPinMode(void){

	// CLEAR PA2 AND PA3
	GPIOA_MODER &= ~((3u << 4) | (3u << 6));

	// SET PA2 AND PA3 TO AF
	GPIOA_MODER |= ((2u << 4) | (2u << 6));

}

/*
 setAF
 CONFIGURE ALTERNATE FUNCTION
 */
void setAF(void){
	// RESET ALTERNATE FUNCTION
	// AF[0] IS THE ALTERNATE FUNCTION LOW REGISTER (PA0 to PA7)
	// CLEAR PA2 and pa3
	GPIOA_AFR0 &= ~((15u << 8) | (15u << 12));

	//SET ALTERNATE FUNCTION
	// SET PA2 AND PA3 AS AF7 (USART2)
	GPIOA_AFR0 |= ((7u << 8) | (7u << 12));
}

/*
 configureUartPins
 CONFIGURES REQUIRED PINS TO BE USED AS UART PINS
 */

void configUart2Pins(void){

	// SET PIN MODE TO ALTERNATE FUNCTION
	configPinMode();

	// SET ALTERNATE FUNCTION TO BE UART2
	setAF();
}

/*
 configureUART2
 configures UART2 RELATED REGISTERS TO SET UP PERIPHERAL
 */
void configureUART2(void){
	USART2_CR1 &= ~( USART2_CR1_OVER8    // Clear OVER8 to use Oversampling by 16 (Bit 15)
	                | USART2_CR1_UE       // Clear UE to keep USART disabled for now (Bit 13)
	                | USART2_CR1_M        // Clear M for 1 Start bit, 8 Data bits (Bit 12)
	                | (0x1F << 4)        // Clear standard interrupts (PEIE, TXEIE, TCIE, RXNEIE, IDLEIE at Bits 4-8)
	                | USART2_CR1_TE       // Disable Transmitter (Bit 3)
	                | USART2_CR1_RE       // Disable Receiver (Bit 2)
	                );

	USART2_CR2 &= ~( USART2_CR2_LBDIE
	                | USART2_CR2_CLKEN
	                | USART2_CR2_STOP
	                | USART2_CR2_LINEN
	               );

	USART2_CR3 &= ~( USART2_CR3_EIE
					| (0x7F << 3)
					| USART2_CR3_IREN
			        );

	USART2_CR3 |= USART2_CR3_ONEBIT;

	// SET BAUD RATE TO 115200 (Assuming 16MHz HSI clock source: 16MHz / (16 * 115200) = 8.68 -> BRR = 8.6875 -> 139)
	USART2_BRR = 139;

	//ENABLE UART
	USART2_CR1 |= ( USART2_CR1_UE  //ENABLE UART2 (BIT 13) - Corrected logic to |=
					| USART2_CR1_RE  // ENABLE RECEIVER (BIT 2)
			        | USART2_CR1_TE   // ENABLE TRANSMITTER (BIT 3)
					);
}

/*
 *receiveUART
 THIS FUNCTION READS A BYTE OF DATA FROM RECEIVE DATA REGISTER, IF THERE IS DATA
 TO BE READ, AND RETURNS A BYTE OF DATA READ FROM RECEIVE DATA REGISTER
 */

uint8_t receiveUART(void){
	uint8_t rxData = 0;

	//IF THERE IS DATA IN RECEIVE DATA REGISTER
	// USART_SR_RXNE EXPANDS TO (1 << 5)
	if (USART2_SR & USART_SR_RXNE){
		rxData = USART2_DR;
	}

	return rxData;
}

/*
 transmitUART(uint8_t data)
 This function sends a byte of data over UART
 */
void transmitUART(uint8_t data){
	//WAIT UNTILL TRANSMIT DATA REGISTER IS READY TO TAKE DATA
	//USART_SR_TXE EXPANDS TO (1 << 7)
	while (!(USART2_SR & USART_SR_TXE));

	USART2_DR = data;
}

/*
 INIT UART
 THIS FUNCTION CONTAINS ALL CODE TO INITIALIZE UART
 */
void initUART(void){

	// INITIALIZE CLOCKS
	initClocks();

	//CONFIGURE PINS TO UART2
	configUart2Pins();

	// CONFIGURE UART2
	configureUART2();

	// CONFIGURE LD2
	ConfigureLD2();
}

void LD2_ON(){
	LD2 |= (1 << 5);
}

void LD2_OFF(){
	LD2 &= ~(1 << 5);
}

int main(void)
{
	// SET UP UART
	initUART();

	while (1){
//		uint8_t receivedData = receiveUART();
//		if (receivedData > 0){
//			transmitUART(85);
//		} else if (receivedData == 0){
//			transmitUART(67);
//		}

		uint8_t received_char = receiveUART();

				// Check if we actually received a character (value is greater than 0)
				if (received_char > 0){

					// If the user typed the character '0' (ASCII 48)
					if (received_char == '0'){
						// LIGHT OFF
						transmitUART('0');
						LD2_OFF();
					} else if ((received_char >= '1' && received_char <= '9') ||
					           (received_char >= 'a' && received_char <= 'z') ||
					           (received_char >= 'A' && received_char <= 'Z')) {

						// LIGHT ON
						transmitUART('1');
						LD2_ON();
					}
				}
	}
	//BLINK_LD2();


}
