#include "Morse.h"
#include <stdlib.h>
#include "stm32f4xx_hal.h"


#define simInMorse 37 

char *globaltext=NULL; //The Morse array is copied here and edited with timer interrupts.

TIM_HandleTypeDef *globaltimer; //to send the timer address to the interrupt

uint8_t globalSpidLedMorse=1; //timer period multiplier

const MorseCode morseTable[] = {
    {'A', 'a', ".- ", 3},    {'B', 'b', "-... ", 5},  {'C', 'c', "-.-. ", 5},
    {'D', 'd', "-.. ", 4},   {'E', 'e', ". ", 2},     {'F', 'f', "..-. ", 5},
    {'G', 'g', "--. ", 4},   {'H', 'h', ".... ", 5},  {'I', 'i', ".. ", 3},
    {'J', 'j', ".--- ", 5},  {'K', 'k', "-.- ", 4},   {'L', 'l', ".-.. ", 5},
    {'M', 'm', "-- ", 2},    {'N', 'n', "-. ", 3},    {'O', 'o', "--- ", 4},
    {'P', 'p', ".--. ", 5},  {'Q', 'q', "--.- ", 5},  {'R', 'r', ".-. ", 4},
    {'S', 's', "... ", 4},   {'T', 't', "- ", 2},     {'U', 'u', "..- ", 4},
    {'V', 'v', "..- ", 4},  {'W', 'w', ".- ", 3},   {'X', 'x', "-..- ", 5},
    {'Y', 'y', "-.- ", 4},  {'Z', 'z', "--.. ", 5},
    {'1', '1', ".---- ", 6}, {'2', '2', "..--- ", 6}, {'3', '3', "...-- ", 6},
    {'4', '4', "....- ", 6}, {'5', '5', "..... ", 6}, {'6', '6', "-.... ", 6},
    {'7', '7', "--... ", 6}, {'8', '8', "---.. ", 6}, {'9', '9', "----. ", 6},
    {'0', '0', "----- ", 6}, {' ', ' ', "    ", 3} 

};
void textLedMorse(TIM_HandleTypeDef *htim11,char *text, uint16_t spidMorse){
	if(globaltext==NULL){
		int i=0;
		for(;text[i]!='\0';i++){
			if (text[i] != '.' && text[i] != '-' && text[i] != ' ') {
				return;
			}
		}
		if(text[i-1]!=' '){return;};// in prerivTim in case' ' 
		globaltext = malloc(i);
		for(i=0;text[i]!='\0';i++){
			globaltext[i]=text[i];
		}
		globaltext[i]='\0';
		//globaltext=text;
		globaltimer=htim11;
		globalSpidLedMorse=spidMorse;

		HAL_TIM_Base_Start_IT(htim11);
	}
}

void prerivTim(){
	for(int i=0; globaltext[i] != '\0';  i++){

		switch(globaltext[i]){
			case 'p':
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_SET);
				__HAL_TIM_SET_AUTORELOAD(globaltimer,40*globalSpidLedMorse);
				globaltext[i]='0';
			return;
			case '.':
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_RESET);
				__HAL_TIM_SET_AUTORELOAD(globaltimer,20*globalSpidLedMorse);
				globaltext[i]='p';
			return;
			case '-':
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_RESET);
				__HAL_TIM_SET_AUTORELOAD(globaltimer,100*globalSpidLedMorse);
				globaltext[i]='p';
			return;
			case ' ':
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_SET);
				__HAL_TIM_SET_AUTORELOAD(globaltimer,40*globalSpidLedMorse);
				globaltext[i]='p';
				if(globaltext[i+1] == '\0'){      
					free(globaltext);
					globaltext = NULL;
					HAL_TIM_Base_Stop_IT(globaltimer);
				}
			return;
		}
	}
}

textSizeMorse textInMorse(char* text ) { 
		uint32_t sizeMalloc = 0; 
	
		textSizeMorse textMorseS;
	
		for (int i = 0; text[i] != '\0'; i++) {
			for (int j = 0; j < simInMorse; j++) {
			if (morseTable[j].SIM == text[i] || morseTable[j].sim == text[i]){
					sizeMalloc += morseTable[j].sizMorzeCod;	
			}}
		}
		
		textMorseS.text = malloc(sizeMalloc+1);
		uint32_t t=0;
		
    for (int i = 0; text[i] != '\0'; i++) {
        for (int j = 0; j < simInMorse; j++) {
        if (morseTable[j].SIM == text[i] || morseTable[j].sim == text[i]) {
					
                char *morse = morseTable[j].morse;
                for (int k = 0; morse[k] != '\0'; k++) {
									textMorseS.text[t]=morse[k];								
									t++;			
                }
                break;
        }}
    }
		textMorseS.text[t] = '\0';
		return textMorseS;
}

