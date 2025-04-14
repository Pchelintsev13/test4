#include "Morse.h" 


const MorseCode morseTable[] = {
    {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},
    {'D', "-.."},   {'E', "."},     {'F', "..-."},
    {'G', "--."},   {'H', "...."},  {'I', ".."},
    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
    {'M', "--"},    {'N', "-."},    {'O', "---"},
    {'P', ".--."},  {'Q', "--.-"},  {'R', ".-."},
    {'S', "..."},   {'T', "-"},     {'U', "..-"},
    {'V', "..-"},  {'W', ".-"},   {'X', "-..-"},
    {'Y', "-.-"},  {'Z', "--.."},
    {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
    {'4', "....-"}, {'5', "....."}, {'6', "-...."},
    {'7', "--..."}, {'8', "---.."}, {'9', "----."},
    {'0', "-----"}, {' ', " "} // пробел между словами

};

void sendMorse(const char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = toupper((unsigned char)text[i]);

        for (int j = 0; j < sizeof(morseTable) / sizeof(MorseCode); j++) {
            if (morseTable[j].character == c) {
                const char *morse = morseTable[j].morse;

                for (int k = 0; morse[k] != '\0'; k++) {
                    sendMorseSymbol(morse[k]);
                }

                HAL_Delay(400);  // пауза между буквами
                break;
            }
        }
        if (c == ' ') {
            HAL_Delay(800);  // пауза между словами
        }
    }
}



void sendMorseSymbol(char symbol) {
    if (symbol == '.') {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_Delay(200);  // точка: короткий импульс
    } else if (symbol == '-') {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_Delay(600);  // тире: длинный импульс
    }

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_Delay(200);  // пауза между символами
}
