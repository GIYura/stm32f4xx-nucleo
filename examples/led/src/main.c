#include <stddef.h>
#include <stdint.h>

#include "led.h"
#include "board.h"
#include "delay.h"

int main (void)
{
    Board_Init();

    Led_t* ledWhite = Board_GetLed(BOARD_LED_WHITE);
    Led_t* ledGreen = Board_GetLed(BOARD_LED_GREEN);
    Led_t* ledYellow = Board_GetLed(BOARD_LED_YELLOW);

/* NOTE: this is done for test only */
#if 1
    LedOn(ledWhite);
    LedOn(ledGreen);
    LedOn(ledYellow);

    LedOff(ledWhite);
    LedOff(ledGreen);
    LedOff(ledYellow);

    LedDeinit(ledWhite);
    LedDeinit(ledGreen);
    LedDeinit(ledYellow);

    Board_Init();
#endif

    while (1)
    {
        LedToggle(ledWhite);
        LedToggle(ledGreen);
        LedToggle(ledYellow);

        DelayMs(100);
    }

    return 0;
}

