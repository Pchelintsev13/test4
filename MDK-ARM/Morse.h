#include "stm32f4xx_hal.h"
#include "ctype.h"
#include "main.h"

void sendMorse(const char *text);
void sendMorseSymbol(char symbol);

typedef struct {
    char character;
    const char *morse;
} MorseCode;
