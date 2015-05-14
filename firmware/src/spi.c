#include <avr/io.h>
#include "spi.h"



void spi_init(uint8_t config)
{
    SPCR = config;
}


uint8_t spi_transfer(uint8_t txd)
{
    uint8_t rxd;
    SPDR = txd;
    while(!(SPSR & (1 << SPIF));
    rxd = SPDR;
    return rxd;
}
