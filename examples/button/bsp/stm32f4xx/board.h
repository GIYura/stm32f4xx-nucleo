#ifndef BOARD_H
#define BOARD_H

#include "button.h"

typedef enum
{
    BOARD_BUTTON_ID_USER,
    BOARD_BUTTON_ID_EXTERNAL,
    BOARD_BUTTON_COUNT
} BOARD_BUTTON_ID;

/*Brief: Board initialization
* [in] - none
* [out] - none
* */
void BoardInit(void);

/*Brief: Get board button
* [in] - id  - button id
* [out] - pointer to button object
* */
Button_t* BoardGetButton(BOARD_BUTTON_ID id);

#endif /* BOARD_H */
