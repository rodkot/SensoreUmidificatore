#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

// SPI configuration settings
#define SPI_CLOCK_RATE 1000000  // SPI clock rate in Hz
#define SPI_MODE 0     // SPI mode (0, 1, 2, or 3)

// SPI function prototypes
void spi_master_init(void);
void spi_slave_init(void);
void spi_master_transmit(uint8_t data);
uint8_t spi_master_receive(void);
void spi_slave_transmit(uint8_t data);
uint8_t spi_slave_receive(void);
uint8_t spi_is_received(void);
uint8_t spi_is_busy(void);

#endif  // SPI_H
