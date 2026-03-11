#include <stddef.h>
#include <stdint.h>

#include "led.h"
#include "board.h"
#include "delay.h"

int main (void)
{
    BoardInit();

    LedHandle_t* ledWhite = BoardGetLed(BOARD_LED_ID_WHITE);
    LedHandle_t* ledGreen = BoardGetLed(BOARD_LED_ID_GREEN);
    LedHandle_t* ledYellow = BoardGetLed(BOARD_LED_ID_YELLOW);

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

    BoardInit();
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

