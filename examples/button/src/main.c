#include <stddef.h>
#include <stdint.h>

#include "button.h"
#include "board.h"

static uint32_t m_buttonUserCounter = 0;

static void OnButtonUser(void)
{
    ++m_buttonUserCounter;
}

int main (void)
{
    Board_Init();

    Button_t* buttonUser = Board_GetButton(BOARD_BUTTON_USER);

    ButtonRegisterHandler(buttonUser, OnButtonUser);

    while (1);

    return 0;
}

