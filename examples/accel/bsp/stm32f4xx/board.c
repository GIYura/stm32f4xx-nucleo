#include <stddef.h>

#include "custom-assert.h"
#include "adxl345.h"
#include "adxl345-regs.h"
#include "board.h"
#include "board-pin.h"
#include "spi.h"
#include "spi-name.h"

#define SPI_CLOCK_FREQ      (5000000)     /* Hz */

/* SPI (transport layer for ADXL345) */
static SpiHandle_t m_spi;

static GpioHandle_t m_gpioCs;

static AdxlHandle_t m_adxl;

static AdxlRegisters_t m_adxlConfig[] = {
        { ADXL345_POWER_CTL, 0x08 },    /* measure mode */
        { ADXL345_DATA_FORMAT, 0x0B },  /* full resolution, +- 16g */
        { ADXL345_BW_RATE, 0x0A },      /* 100 Hz */
};

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

AdxlRegisters_t* BoardGetAdxlConfig(uint8_t* const size)
{
    ASSERT(size != NULL);

    *size = (sizeof(m_adxlConfig) / sizeof(m_adxlConfig[0]));

    return m_adxlConfig;
}
