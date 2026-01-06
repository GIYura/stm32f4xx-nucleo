#ifndef BOARD_H
#define BOARD_H

#include "sw-timer.h"

/*Brief: Board initialization
* [in] - none
* [out] - none
* */
void Board_Init(void);

SwTimer_t* Board_GetSwTimer(void);

#endif /* BOARD_H */
