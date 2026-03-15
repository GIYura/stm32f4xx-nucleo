#include <stddef.h>

#include "custom-assert.h"
#include "adxl345.h"
#include "adxl345-regs.h"
#include "board.h"
#include "event.h"
#include "ignore.h"

#if 0
NOTE: for test default registers only.
static AdxlRegisters_t m_adxlRegisters[ADXL_REGISTERS_COUNT];
#endif

static uint8_t m_accelId = 0;
static Acceleration_t m_accelVector = { 0 };
static uint8_t m_accelPowerControl = 0x08;      /* turn on measurement */

static void OnAccelRegisterRead(void* data, void* context)
{
    ASSERT(data != NULL);
    ASSERT(context != NULL);

    uint8_t* pValue = (uint8_t*)context;
    *pValue = *(uint8_t*)data;

    Event_t e = { .type = EVENT_ACCEL_ID_READY, .context = pValue };

    EventQueue_Enqueue(&e);
}

static void OnAccelRegisterWrite(void* data, void* context)
{
    IGNORE(data);
    IGNORE(context);

    Event_t e = { .type = EVENT_ACCEL_CONFIG_READY, .context = NULL };

    EventQueue_Enqueue(&e);
}

static void OnAccelVectorRead(void* vector, void* context)
{
    ASSERT(vector != NULL);
    ASSERT(context != NULL);

    Acceleration_t* pValue = (Acceleration_t*)context;
    Acceleration_t* pVector = (Acceleration_t*)vector;

    pValue->x = pVector->x;
    pValue->y = pVector->y;
    pValue->z = pVector->z;

    Event_t e = { .type = EVENT_ACCEL_VECTOR_READY, .context = pValue };

    EventQueue_Enqueue(&e);
}

int main (void)
{
    BoardInit();

    EventQueueInit();

    AdxlHandle_t* adxl = BoardGetAdxl();

    AdxlRegisterReadRegHandler(adxl, &OnAccelRegisterRead);
    AdxlRegisterWriteRegHandler(adxl, &OnAccelRegisterWrite);
    AdxlRegisterReadVectorHandler(adxl, &OnAccelVectorRead);

    AdxlReadRegisterAsyncSpi(adxl, ADXL345_DEVID, &m_accelId);

    while (1)
    {
        Event_t e;
        if (EventQueue_Dequeue(&e))
        {
            switch (e.type)
            {
                case EVENT_ACCEL_VECTOR_READY:

                    AdxlReadVectorAsyncSpi(adxl, ADXL345_DATAX0, &m_accelVector);

                    break;

                case EVENT_ACCEL_CONFIG_READY:

                    AdxlReadVectorAsyncSpi(adxl, ADXL345_DATAX0, &m_accelVector);

                    break;

                case EVENT_ACCEL_ID_READY:

                    if (*(uint8_t*)e.context == ADXL345_ID)
                    {
                        AdxlWriteRegisterAsyncSpi(adxl, ADXL345_POWER_CTL, &m_accelPowerControl);
                    }

                    break;

                default:
                    /* never reach here */
                    break;
            }
        }
    }

    return 0;
}

