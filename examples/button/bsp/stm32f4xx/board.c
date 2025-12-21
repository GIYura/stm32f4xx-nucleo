#include <stddef.h>

#include "custom-assert.h"
#include "board.h"
#include "button.h"
#include "gpio.h"
#include "gpio-name.h"

/* Button gpio */
static GpioHandle_t m_gpioButtonUser;

/* Button */
static Button_t m_buttonUser;

void Board_Init(void)
{
    const GpioOps_t* ops = GpioGetOps();

    m_gpioButtonUser.ops = ops;

    ButtonInit(&m_buttonUser, &m_gpioButtonUser, PC_13);
}

Button_t* Board_GetButton(BOARD_BUTTON_ID id)
{
    ASSERT(id < BOARD_BUTTON_COUNT);

    switch (id)
    {
    case BOARD_BUTTON_USER:
        return &m_buttonUser;
        break;

    default:
        /* never reach here */
        return NULL;
        break;
    }
}

