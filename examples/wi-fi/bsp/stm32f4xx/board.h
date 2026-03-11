#ifndef BOARD_H
#define BOARD_H

#include "led.h"
#include "esp8266.h"

typedef enum
{
    BOARD_LED_ID_GREEN = 0,
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
LedHandle_t* BoardGetLed(BOARD_LED_ID id);

/*Brief: Get board ESP
* [in] - none
* [out] - pointer to ESP object
* */
EspHandle_t* BoardGetEsp(void);

#endif /* BOARD_H */
