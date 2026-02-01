#include <stddef.h>
#include <stdint.h>

#include "button.h"
#include "board.h"

static uint32_t m_buttonUserCounter = 0;
static uint32_t m_buttonExternalCounter = 0;

static void OnButtonUser(void)
{
    ++m_buttonUserCounter;
}

static void OnButtonExternal(void)
{
    ++m_buttonExternalCounter;
}

int main (void)
{
    Board_Init();

    Button_t* buttonUser = Board_GetButton(BOARD_BUTTON_USER);
    Button_t* buttonExternal = Board_GetButton(BOARD_BUTTON_EXTERNAL);

    ButtonRegisterHandler(buttonUser, OnButtonUser);
    ButtonRegisterHandler(buttonExternal, OnButtonExternal);

    while (1);

    return 0;
}

