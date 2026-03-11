#include <stddef.h>
#include <stdint.h>

#include "sw-timer.h"
#include "board.h"

static SwTimerHandle_t m_swTimer1;
static uint8_t m_counter1 = 0;

static SwTimerHandle_t m_swTimer2;
static uint8_t m_counter2 = 0;

void OnSwTimer1(void* context)
{
    m_counter1++;

    GpioHandle_t* gpio = (GpioHandle_t*)context;

    gpio->ops->toggle(gpio);
}

void OnSwTimer2(void* context)
{
    m_counter2++;

    GpioHandle_t* gpio = (GpioHandle_t*)context;

    gpio->ops->toggle(gpio);
}

int main (void)
{
    BoardInit();

    GpioHandle_t* gpio1 = BoardGetGpio(BOARD_GPIO_ID_1);
    GpioHandle_t* gpio2 = BoardGetGpio(BOARD_GPIO_ID_2);

    SwTimerInit(&m_swTimer1, 150, SW_TIMER_PERIODIC);
    SwTimerRegisterCallback(&m_swTimer1, &OnSwTimer1, gpio1);

    SwTimerInit(&m_swTimer2, 250, SW_TIMER_PERIODIC);
    SwTimerRegisterCallback(&m_swTimer2, &OnSwTimer2, gpio2);

    SwTimerStart(&m_swTimer1);
    SwTimerStart(&m_swTimer2);

    while (1);

    return 0;
}

