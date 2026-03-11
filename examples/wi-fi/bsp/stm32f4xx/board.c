#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "board-pin.h"
#include "timer.h"
#include "sw-timer.h"
#include "uart.h"
#include "uart-name.h"

#define HW_TIMER_TIMEOUT_MS             (1)
#define ESP_RESPONSE_TIMEOUT_MS         (30)

/* LEDs gpios */
static GpioHandle_t m_gpioLedGreen;
static GpioHandle_t m_gpioLedYellow;
static GpioHandle_t m_gpioLedWhite;

/* LEDs */
static LedHandle_t m_ledGreen;
static LedHandle_t m_ledYellow;
static LedHandle_t m_ledWhite;

/* UART (transport layer for ESP) */
static UartHandle_t m_uart;

/* SW timer */
static SwTimerHandle_t m_swTimer;

/* ESP */
static EspHandle_t m_esp;

/* HW timer */
static TimerHandle_t m_hwTimer;

void BoardInit(void)
{
    const GpioOps_t* gpioOps = GpioGetOps();
    const TimerOps_t* hwTimerOps = TimerGetOps();
    const UartOps_t* uartOps = UartGetOps();

    m_gpioLedGreen.ops = gpioOps;
    m_gpioLedWhite.ops = gpioOps;
    m_gpioLedYellow.ops = gpioOps;

    LedInit(&m_ledGreen, &m_gpioLedGreen, BOARD_LED_GREEN);
    LedInit(&m_ledYellow, &m_gpioLedYellow, BOARD_LED_YELLOW);
    LedInit(&m_ledWhite, &m_gpioLedWhite, BOARD_LED_WHITE);

    m_uart.ops = uartOps;
    m_uart.ops->open(&m_uart, BOARD_ESP_UART, BAUD_115200, &m_swTimer, ESP_RESPONSE_TIMEOUT_MS);

    EspInit(&m_esp, &m_uart);

    m_hwTimer.ops = hwTimerOps;

    m_hwTimer.ops->open(&m_hwTimer, HW_TIMER_TIMEOUT_MS);

    m_hwTimer.ops->interrupt(&m_hwTimer, SwTimerTick, 7);

    m_hwTimer.ops->start(&m_hwTimer);
}

LedHandle_t* BoardGetLed(BOARD_LED_ID id)
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

EspHandle_t* BoardGetEsp(void)
{
    return &m_esp;
}

