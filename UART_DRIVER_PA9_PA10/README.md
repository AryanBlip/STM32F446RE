# STM32F446RE Bare-Metal UART Controlled LED

A bare-metal C program for the STM32F446RE that configures USART1 and GPIO Port A using direct register manipulation. 
Using the simple task of controlling the onboard user LED (LD2) to demonstrate functional data transmission and reception.

## Hardware Configuration
* **Microcontroller:** STM32F446xx (ARM Cortex-M4)
* **USART Peripheral:** USART1
* **UART Pins:** 
    * `PA9` -> TX (Alternate Function 7)
    * `PA10` -> RX (Alternate Function 7)
* **User LED (LD2):** `PA5` (Configured as General Purpose Output)
* **Baud Rate:** 9600 bps (assuming a 16 MHz internal/HSI clock source)
* **Frame Format:** 8 Data Bits, 1 Stop Bit, No Parity

## Application Logic
To demonstrate successful configuration and terminal interaction, the program executes a basic control loop. 
It checks the USART1 status flags and changes the state of the LD2 LED based on ASCII characters received via terminal input:

| Received Character | LED State | UART Response Message |
| :--- | :--- | :--- |
| `'0'` | Turns OFF | `LIGHTS OFF\n` |
| Any Alphanumeric (`1-9`, `a-z`, `A-Z`) | Turns ON | `LIGHTS ON\n` |
| Any Alphanumeric (while already on) | No Change | `LIGHTS ARE ALREADY ON\n` |
| `'0'` (while already off) | No Change | `LIGHTS ARE ALREADY OFF\n` |

## Implementation Steps

The initialization and runtime flow follow a deterministic register-level sequence:

### 1. Clock Initialization (initClocks())
* Enables the clock for **GPIOA** by setting Bit 0 (`RCC_AHB1ENR_GPIOAEN`) in the `RCC_AHB1ENR` register.
* Enables the clock for **USART1** by setting Bit 4 (`RCC_APB2ENR_USART1EN`) in the `RCC_APB2ENR` register.

### 2. GPIO Configuration (configUart1Pins())
* **Mode Setup (`configPinMode`):** Clears the mode bits for `PA9` and `PA10` in `GPIOA_MODER`, then configures both pins to **Alternate Function Mode**.
* **Alternate Function Selection (`setAF`):** Clears the relevant fields in the Alternate Function High Register (`GPIOA_AFR1`),
* then maps both pins to **AF7** (USART1).

### 3. LED Configuration (configureLD2())
* Ensures GPIOA clock is enabled.
* Clears bits 10 and 11 of `GPIOA_MODER`, then writes `1` to bit 10 to configure `PA5` as a **General Purpose Output**.

### 4. USART1 Configuration (configureUART1())
* Clears configuration registers (`USART1_CR1`, `USART1_CR2`, `USART1_CR3`) to reset oversampling (set to 16), word length (8 data bits),
* and turn off standard interrupts.
* Sets the `USART1_CR3_ONEBIT` sampling method.
* Writes `1667` to the Baud Rate Register (`USART1_BRR`) to achieve a 9600 baud rate from a 16 MHz clock.
* Enables the peripheral, transmitter, and receiver by setting the `UE`, `TE`, and `RE` bits in `USART1_CR1`.

### 5. Polling and Execution Loop (main())
* Calls the core execution routine which continually checks the `USART1_ISR` register flag and `USART_ISR_RXNE` (Receive Data Register Not Empty).
* When a byte arrives, it reads `USART1_DR`, evaluates the control conditions, updates the output register for `PA5` to execute the LED toggling,
* and pushes the corresponding response string through `USART1_DR` by polling the `USART_ISR_TXE` (Transmit Data Register Empty) flag.
