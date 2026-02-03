#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "timer.h"
#include "sw-timer.h"

#define HW_TIMER_TIMEOUT_MS             1

static TimerHandle_t m_hwTimer;

void Board_Init(void)
{
    const TimerOps_t* hwTimerOps = TimerGetOps();

    m_hwTimer.ops = hwTimerOps;

    m_hwTimer.ops->open(&m_hwTimer, HW_TIMER_TIMEOUT_MS);

    m_hwTimer.ops->interrupt(&m_hwTimer, SwTimerTick);

    m_hwTimer.ops->start(&m_hwTimer);
}

