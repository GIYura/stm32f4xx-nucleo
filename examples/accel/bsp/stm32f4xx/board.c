#include <stddef.h>

#include "adxl345.h"
#include "board.h"
#include "board-pin.h"
#include "spi.h"
#include "spi-name.h"

#define SPI_CLOCK_FREQ      (5000000)     /* Hz */

/* SPI (transport layer for ADXL345) */
static SpiHandle_t m_spi;

static GpioHandle_t m_gpioCs;

static AdxlHandle_t m_adxl;

void BoardInit(void)
{
    const SpiOps_t* spiOps = SpiGetOps();
    const GpioOps_t* gpioOps = GpioGetOps();

    m_spi.ops = spiOps;
    m_gpioCs.ops = gpioOps;

    m_gpioCs.ops->open(&m_gpioCs, BOARD_ACCEL_CS, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, 1);

    m_spi.ops->open(&m_spi, BOARD_ACCEL_SPI, CPOL_1, CPHA_1, SPI_CLOCK_FREQ);

    AdxlInitSpi(&m_adxl, &m_spi, &m_gpioCs);
}

AdxlHandle_t* BoardGetAdxl(void)
{
    return &m_adxl;
}

