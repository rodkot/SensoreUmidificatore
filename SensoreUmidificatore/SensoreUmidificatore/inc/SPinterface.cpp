/* 
* SPinterface.cpp
*
* Created: 27.05.2023 22:23:24
* Author: rodio
*/


#include "SPinterface.h"


void SPinterface::begin(){
	DDRD=0xFF;
	PORTD=0x00;

	// Initial the AVR ATMega168 SPI Peripheral
	// Set MOSI (PB3),SCK (PB5) and PB2 (SS) as output, others as input
	SPI_DDR = (1<<PB3)|(1<<PB5)|(1<<PB2);
	// CS pin is not active
	SPI_PORT |= (1<<SPI_CS);

	SPCR = (1<<SPE)|(1<<MSTR);
	SPSR |= (1<<SPI2X);
}

void SPinterface::begin_transaction(){
	SPI_PORT &= ~(1<<SPI_CS);
}

void SPinterface::end_transaction(){
	SPI_PORT |= (1<<SPI_CS);
}

uint8_t SPinterface::is_busy(){
	// Check if SPI is busy
	return (!(SPSR & (1 << SPIF)));
}

uint8_t SPinterface::transmit(uint8_t data){
	// Start transmission
	SPDR = data;

	while (is_busy());
	
	return SPDR;
}

// default constructor
SPinterface::SPinterface()
{
} //SPinterface

// default destructor
SPinterface::~SPinterface()
{
} //~SPinterface
