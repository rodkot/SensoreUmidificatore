/* 
* SPinterface.h
*
* Created: 27.05.2023 22:23:25
* Author: rodio
*/


#ifndef __SPINTERFACE_H__
#define __SPINTERFACE_H__

#include <avr/io.h>

#define SPI_PORT PORTB
#define SPI_DDR DDRB
#define SPI_CS PB2
#define SPI_CLOCK_RATE 1000000  // SPI clock rate in Hz
#define SPI_MODE 0

class SPinterface
{
//variables
public:
protected:
private:

//functions
public:
	SPinterface();
	
	static void begin();
	
	static void begin_transaction(void);
	
	static void end_transaction(void);

	static uint8_t  is_busy(void);
	static uint8_t  transmit(uint8_t data);
	
	~SPinterface();
protected:
private:
	SPinterface( const SPinterface &c );
	SPinterface& operator=( const SPinterface &c );

}; //SPinterface

#endif //__SPINTERFACE_H__
