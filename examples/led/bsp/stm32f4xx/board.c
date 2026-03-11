#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "board-pin.h"
#include "gpio.h"

/* LEDs gpios */
static GpioHandle_t m_gpioLedGreen;
static GpioHandle_t m_gpioLedYellow;
static GpioHandle_t m_gpioLedWhite;

/* LEDs */
static Led_t m_ledGreen;
static Led_t m_ledYellow;
static Led_t m_ledWhite;

void BoardInit(void)
{
    const GpioOps_t* ops = GpioGetOps();

    m_gpioLedGreen.ops = ops;
    m_gpioLedWhite.ops = ops;
    m_gpioLedYellow.ops = ops;

    LedInit(&m_ledGreen, &m_gpioLedGreen, BOARD_LED_GREEN);
    LedInit(&m_ledYellow, &m_gpioLedYellow, BOARD_LED_YELLOW);
    LedInit(&m_ledWhite, &m_gpioLedWhite, BOARD_LED_WHITE);
}

Led_t* BoardGetLed(BOARD_LED_ID id)
{
    ASSERT(id < BOARD_LED_COUNT);

    switch (id)
    {
    case BOARD_LED_ID_GREEN:
        return &m_ledGreen;
        break;

    case BOARD_LED_ID_YELLOW:
        return &m_ledYellow;
        break;

    case BOARD_LED_ID_WHITE:
        return &m_ledWhite;
        break;

    default:
        /* never reach here */
        return NULL;
        break;
    }
}

