#include <avr/io.h>
#include <util/delay.h>
#include "sensor/sbme280.h"

#define SPI_PORT PORTB
#define SPI_DDR DDRB
#define SPI_CS PB2

 
int main(void)
{
    DDRD = 0xff;
	// Initial the AVR ATMega168 SPI Slave Peripheral
	// Set MISO (PB4) as output, others as input
	SPI_DDR |= (1<<PB4);
	// Enable SPI as Slave
	SPCR = (1<<SPE);
	
	sbme280 sensor;
	 
		// Poll the SPI Data
		while(1){
			while(!(SPSR & (1<<SPIF)));
			sensor.resolve(SPDR);
		}
	return 0;
}