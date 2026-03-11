#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "board-pin.h"
#include "timer.h"
#include "sw-timer.h"
#include "gpio.h"

#define HW_TIMER_TIMEOUT_MS             1

static GpioHandle_t m_gpio1;
static GpioHandle_t m_gpio2;

/* HW timer */
static TimerHandle_t m_hwTimer;

void BoardInit(void)
{
    const TimerOps_t* hwTimerOps = TimerGetOps();
    const GpioOps_t* gpioOps = GpioGetOps();

    m_gpio1.ops = gpioOps;
    m_gpio2.ops = gpioOps;

    m_gpio1.ops->open(&m_gpio1, BOARD_GPIO_1, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);
    m_gpio1.ops->open(&m_gpio2, BOARD_GPIO_2, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);

    m_hwTimer.ops = hwTimerOps;

    m_hwTimer.ops->open(&m_hwTimer, HW_TIMER_TIMEOUT_MS);

    m_hwTimer.ops->interrupt(&m_hwTimer, SwTimerTick, 6);

    m_hwTimer.ops->start(&m_hwTimer);
}

GpioHandle_t* BoardGetGpio(BOARD_GPIO_ID id)
{
    ASSERT(id < BOARD_GPIO_COUNT);

    switch (id)
    {
    case BOARD_GPIO_ID_1:
        return &m_gpio1;
        break;

    case BOARD_GPIO_ID_2:
        return &m_gpio2;
        break;

    default:
        /* never reach here */
        return NULL;
        break;
    }
}

