#include "stm32f4xx_hal.h"
#include "ctype.h"
#include "main.h"




void textLedMorse(TIM_HandleTypeDef *htim11,char *text,uint16_t spidMorse);// starts displaying the Morse code sequence on an led using a timer

void prerivTim(); //Handles the timer interrupt and sends the next Morse symbol

textSizeMorse textInMorse(char* text);// converts plain text to Morse code

typedef struct {
    char SIM;            // uppercase letters
		char sim;            // lowercase letters
    char *morse;				 // morse code 
		uint8_t sizMorzeCod; // size morse code 
} MorseCode;
