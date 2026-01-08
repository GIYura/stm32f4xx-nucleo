#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "timer.h"
#include "sw-timer.h"

static TimerHandle_t m_hwTimer;

void Board_Init(void)
{
    const TimerOps_t* hwTimerOps = TimerGetOps();

    m_hwTimer.ops = hwTimerOps;

    m_hwTimer.ops->open(&m_hwTimer, 10);

    m_hwTimer.ops->interrupt(&m_hwTimer, SwTimerTick);

    m_hwTimer.ops->start(&m_hwTimer);
}

