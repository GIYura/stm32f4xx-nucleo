#include <stddef.h>
#include <stdint.h>

#include "sw-timer.h"
#include "board.h"

int main (void)
{
    Board_Init();

    SwTimer_t* swTimer = Board_GetSwTimer();

    SwTimerStart(swTimer);

    while (1)
    {

    }

    return 0;
}

