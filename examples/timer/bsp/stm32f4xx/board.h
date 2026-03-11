#ifndef BOARD_H
#define BOARD_H

#include "gpio.h"

typedef enum
{
    BOARD_GPIO_ID_1 = 0,
    BOARD_GPIO_ID_2,
    BOARD_GPIO_COUNT
} BOARD_GPIO_ID;

/*Brief: Board initialization
* [in] - none
* [out] - none
* */
void BoardInit(void);

GpioHandle_t* BoardGetGpio(BOARD_GPIO_ID id);

#endif /* BOARD_H */
