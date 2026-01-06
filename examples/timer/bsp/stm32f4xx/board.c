#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "timer.h"

#include "gpio.h"
#include "gpio-name.h"

static TimerHandle_t m_timer;
static SwTimer_t m_swTimer;

static uint8_t m_counter = 0;

#if 0
/*
 * NOTE:
 * This gpio is for test only
 */
#endif
static GpioHandle_t m_gpio;

static void OnSwTimer(void)
{
    m_counter++;

    m_gpio.ops->toggle(&m_gpio);
}

void Board_Init(void)
{
    const TimerOps_t* timerOps = TimerGetOps();
    const GpioOps_t* gpioOps = GpioGetOps();

    m_timer.ops = timerOps;
    m_gpio.ops = gpioOps;

    m_gpio.ops->open(&m_gpio, PC_4, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);

    SwTimerInit(&m_swTimer, &m_timer, 10, PERIODIC);

    SwTimerRegisterCallback(&m_swTimer, OnSwTimer);
}

SwTimer_t* Board_GetSwTimer(void)
{
    return &m_swTimer;
}

