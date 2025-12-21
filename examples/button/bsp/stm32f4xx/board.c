#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "button.h"
#include "gpio.h"
#include "gpio-name.h"

/* Button gpio */
static GpioHandle_t m_gpioButton;

/* Button */
static Button_t m_button;

void Board_Init(void)
{
    const GpioOps_t* ops = GpioGetOps();

    m_gpioButton.ops = ops;

    ButtonInit(&m_button, &m_gpioButton, PC_13);
}

