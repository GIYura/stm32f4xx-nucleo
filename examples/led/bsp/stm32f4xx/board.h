#ifndef BOARD_H
#define BOARD_H

#include "led.h"

typedef enum
{
    BOARD_LED_ID_GREEN,
    BOARD_LED_ID_WHITE,
    BOARD_LED_ID_YELLOW,
    BOARD_LED_COUNT
} BOARD_LED_ID;

/*Brief: Board initialization
* [in] - none
* [out] - none
* */
void BoardInit(void);

/*Brief: Get board LED
* [in] - id  - LED id
* [out] - pointer to LED object
* */
Led_t* BoardGetLed(BOARD_LED_ID id);

#endif /* BOARD_H */
