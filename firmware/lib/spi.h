
#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/* configuration OR mask */
#define SPI_INTERRUPT_ENABLE 0x80

#define SPI_ENABLE           0x40

#define SPI_LSB_FIRST        0x20
#define SPI_MSB_FIRST        0x00

#define SPI_MODE_MASTER      0x10
#define SPI_MODE_SLAVE       0x00

#define SPI_CLK_INVERT       0x08

#define SPI_SAMPLE_2ND_EDGE  0x04
#define SPI_SAMPLE_1ND_EDGE  0x00

#define SPI_CLKDIV_4         0x00
#define SPI_CLKDIV_16        0x01
#define SPI_CLKDIV_64        0x02
#define SPI_CLKDIV_128       0x03

/* PUBLIC FUNCTIONS */

/**
 * \fn spi_init
 * \brief Initialize SPI device registers.
 *
 * \param config 
 */
void spi_init(uint8_t config);

/**
 * \fn spi_transfer
 * \brief Invoke a full duplex SPI transfer.
 *
 * \details This function starts a data tranfer over the SPI bus.
 * The SPI device transfers data in full duplex mode. It's transmitting
 * and receiving at the same time. To receive data without transmitting,
 * the function needs a dummy byte (like 0x00) to start the transfer.
 *
 * \param txd Data to transfer to the slave.
 *
 * \return rxd Data received from the slave.
 */
uint8_t spi_transfer(uint8_t);


#endif
