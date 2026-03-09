#include <stddef.h>
#include <stdint.h>

#include "led.h"
#include "board.h"
#include "event.h"
#include "esp8266.h"

static void OnEspResponse(ESP_RESPONSE response)
{
    Event_t e;

    switch (response)
    {
    case ESP_RESPONSE_OK:
        e.type = EVENT_ESP_NEXT;
        e.context = NULL;
        EventQueue_Enqueue(&e);
        break;

    case ESP_RESPONSE_LED_ON:
        e.type = EVENT_ESP_LED_ON;
        e.context = NULL;
        EventQueue_Enqueue(&e);
        break;

    case ESP_RESPONSE_LED_OFF:
        e.type = EVENT_ESP_LED_OFF;
        e.context = NULL;
        EventQueue_Enqueue(&e);
        break;

    default:
        /* TODO: handle error state */
        break;
    }
}

int main (void)
{
    BoardInit();

    Led_t* ledGreen = BoardGetLed(BOARD_LED_GREEN);
    Led_t* ledYellow = BoardGetLed(BOARD_LED_YELLOW);
    Led_t* ledWhite = BoardGetLed(BOARD_LED_WHITE);

    LedOn(ledGreen);
    LedOn(ledYellow);
    LedOn(ledWhite);

    LedOff(ledGreen);
    LedOff(ledYellow);
    LedOff(ledWhite);

    EventQueueInit();

    EspHandle_t* esp = BoardGetEsp();
    EspRegisterResponseHandler(esp, &OnEspResponse);

    EspSendCommand(esp, "AT");
    esp->state = ESP_STATE_AT_SENT;

    while (1)
    {
        Event_t e;
        if (EventQueue_Dequeue(&e))
        {
            if (e.type == EVENT_ESP_NEXT)
            {
                switch (esp->state)
                {
                    case ESP_STATE_AT_SENT:
                        EspSendCommand(esp, "AT+GMR");
                        esp->state = ESP_STATE_GMR_SENT;
                        break;

                    case ESP_STATE_GMR_SENT:
                        EspSendCommand(esp, "AT+CWMODE_CUR=2");
                        esp->state = ESP_STATE_MODE_SENT;
                        break;

                    case ESP_STATE_MODE_SENT:
                        EspSendCommand(esp, "AT+CWSAP_CUR=\"ST-ESP8266\",\"12345678\",5,3");
                        esp->state = ESP_STATE_APCFG_SENT;
                        break;

                    case ESP_STATE_APCFG_SENT:
                        EspSendCommand(esp, "AT+CIPMUX=1");
                        esp->state = ESP_STATE_ENABLE_CONN;
                        break;

                    case ESP_STATE_ENABLE_CONN:
                        EspSendCommand(esp, "AT+CIPSERVER=1,3333");
                        esp->state = ESP_STATE_READY;
                        break;

                    case ESP_STATE_READY:
                        esp->state = ESP_STATE_IDLE;
                        LedOn(ledGreen);
                        break;

                    default:
                        break;
                }
            }
            else if (e.type == EVENT_ESP_LED_ON)
            {
                LedOn(ledWhite);
                LedOn(ledYellow);
            }
            else if (e.type == EVENT_ESP_LED_OFF)
            {
                LedOff(ledWhite);
                LedOff(ledYellow);
            }
        }
    }

    return 0;
}

