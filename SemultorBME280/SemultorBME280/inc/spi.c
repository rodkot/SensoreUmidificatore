#include "spi.h"

void spi_master_init(void) {
	// Set MOSI, SCK, and SS pins as outputs
	DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2);

	// Enable SPI, Set as Master, Set clock rate and mode
	SPCR = (1 << SPE) | (1 << MSTR) | (SPI_MODE << CPHA) | (1 << SPR0);
	SPSR = (1 << SPI2X);
}

void spi_slave_init(void) {
	// Set MISO pin as output
	DDRB |= (1 << DDB4);

	// Enable SPI, Set as Slave
	SPCR = (1 << SPE);
}

void spi_master_transmit(uint8_t data) {
	// Start transmission
	SPDR = data;

	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)))
	;
}

uint8_t spi_master_receive(void) {
	// Wait for reception complete
	while (!(SPSR & (1 << SPIF)))
	;

	// Return received data
	return SPDR;
}

void spi_slave_transmit(uint8_t data) {
	// Start transmission
	SPDR = data;

	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)))
	;
}

uint8_t spi_slave_receive(void) {
	// Wait for reception complete
	while (!(SPSR & (1 << SPIF)))
	;

	// Return received data
	return SPDR;
}

uint8_t spi_is_busy(void)
{
	// Check if SPI is busy
	return (!(SPSR & (1 << SPIF)));
}
