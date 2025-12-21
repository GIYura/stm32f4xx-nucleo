#include <stddef.h>
#include <stdint.h>

#include "button.h"
#include "board.h"

static uint32_t m_buttonPressCounter = 0;

static void OnButton(void)
{
    ++m_buttonPressCounter;
}

int main (void)
{
    Board_Init();

    ButtonRegisterPressHandler(OnButton);

    while (1);

    return 0;
}

