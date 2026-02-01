#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "button.h"
#include "gpio.h"
#include "gpio-name.h"
#include "timer.h"
#include "sw-timer.h"

#define HW_TIMER_TIMEOUT_MS             1
#define BUTTON_DEBOUNCE_TIMEOUT_MS      20

/* Button gpio */
static GpioHandle_t m_gpioButtonUser;
static GpioHandle_t m_gpioButtonExternal;

/* Button */
static Button_t m_buttonUser;
static Button_t m_buttonExternal;

/* Debounce timer (based on HW timer) */
static SwTimer_t debounceTimer;
static SwTimer_t debounceTimerExternal;

/* HW timer */
static TimerHandle_t m_hwTimer;

void Board_Init(void)
{
    const GpioOps_t* gpioOps = GpioGetOps();
    const TimerOps_t* hwTimerOps = TimerGetOps();

    m_gpioButtonUser.ops = gpioOps;
    m_gpioButtonUser.ops->open(&m_gpioButtonUser, PC_13, PIN_MODE_INPUT, PIN_TYPE_PULL_UP, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_HIGH);

    m_gpioButtonExternal.ops = gpioOps;
    m_gpioButtonExternal.ops->open(&m_gpioButtonExternal, PC_2, PIN_MODE_INPUT, PIN_TYPE_PULL_UP, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_HIGH);

    ButtonInit(&m_buttonUser, &m_gpioButtonUser, &debounceTimer, BUTTON_DEBOUNCE_TIMEOUT_MS);
    ButtonInit(&m_buttonExternal, &m_gpioButtonExternal, &debounceTimerExternal, BUTTON_DEBOUNCE_TIMEOUT_MS);

    m_hwTimer.ops = hwTimerOps;

    m_hwTimer.ops->open(&m_hwTimer, HW_TIMER_TIMEOUT_MS);

    m_hwTimer.ops->interrupt(&m_hwTimer, SwTimerTick);

    m_hwTimer.ops->start(&m_hwTimer);
}

Button_t* Board_GetButton(BOARD_BUTTON_ID id)
{
    ASSERT(id < BOARD_BUTTON_COUNT);

    switch (id)
    {
    case BOARD_BUTTON_USER:
        return &m_buttonUser;
        break;

    case BOARD_BUTTON_EXTERNAL:
        return &m_buttonExternal;
        break;

    default:
        /* never reach here */
        return NULL;
        break;
    }
}

