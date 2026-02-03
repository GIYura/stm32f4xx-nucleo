#include <stddef.h>
#include <stdint.h>

#include "sw-timer.h"
#include "board.h"

#include "gpio.h"
#include "gpio-name.h"
#include "ignore.h"

static SwTimer_t m_swTimer1;
static GpioHandle_t m_gpio1;
static uint8_t m_counter1 = 0;

static SwTimer_t m_swTimer2;
static GpioHandle_t m_gpio2;
static uint8_t m_counter2 = 0;

void OnSwTimer1(void* context)
{
    IGNORE(context);

    m_counter1++;
    m_gpio1.ops->toggle(&m_gpio1);
}

void OnSwTimer2(void* context)
{
    IGNORE(context);

    m_counter2++;
    m_gpio2.ops->toggle(&m_gpio2);
}

int main (void)
{
    const GpioOps_t* gpioOps = GpioGetOps();
    m_gpio1.ops = gpioOps;
    m_gpio1.ops->open(&m_gpio1, PC_4, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);

    m_gpio2.ops = gpioOps;
    m_gpio2.ops->open(&m_gpio2, PC_3, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);

    Board_Init();

    SwTimerInit(&m_swTimer1, 150, SW_TIMER_PERIODIC);
    SwTimerRegisterCallback(&m_swTimer1, &OnSwTimer1, NULL);

    SwTimerInit(&m_swTimer2, 250, SW_TIMER_PERIODIC);
    SwTimerRegisterCallback(&m_swTimer2, &OnSwTimer2, NULL);

    SwTimerStart(&m_swTimer1);
    SwTimerStart(&m_swTimer2);

    while (1);

    return 0;
}

