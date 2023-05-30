/* 
* sbme280.cpp
*
* Created: 28.05.2023 0:10:12
* Author: rodio
*/


#include "sbme280.h"

// default constructor
sbme280::sbme280()
{
	myArray[0] = 100;
	myArray[1] = 200;
	myArray[2] = 300;
	
	
} //sbme280

void sbme280::wait(){
	while(!(SPSR & (1<<SPIF)));
}

uint8_t sbme280::transmit(uint8_t dataout){
// Put Slave Data On SPDR
SPDR=dataout;
// Wait for transmission complete
wait();
// Return Serial In Value (MISO)
return SPDR;
}
	 
 
void sbme280::response(uint8_t data){
	SPDR = data;

	// Wait for transmission complete
}

uint8_t sbme280::request(){
 // Wait for transmission complete
 while(!(SPSR & (1<<SPIF)));
 // Return Serial In Value (MISO)
 return SPDR;
}

void sbme280::resolve(uint8_t adress){
	 
	switch(adress){
		// Модель BME280
		case BME280_REGISTER_CHIPID:{
			transmit(0x60);
			break;
		}
	
		
		case BME280_REGISTER_CONTROLHUMID:{
		 	 
			uint8_t err = request();	
			break;
		}
		case BME280_DIG_H1_REG:{
		    transmit(A1);
			break;
		}
		case BME280_DIG_H2_REG:{
			// Проблема 
			transmit(E1);
			// SPI Не передает второй байт 
			transmit(E2);
			break;
		}
		
		case BME280_DIG_H3_REG:{
			transmit(E3);
			break;
		}
		case BME280_DIG_H4_REG:{
			transmit(E4);
			break;
		}
		case BME280_DIG_H5_REG:{
			transmit(E5);
			break;
		}
		case BME280_DIG_H6_REG:{
			transmit(E6);
			break;
		}
		case BME280_DIG_H7_REG:{
			transmit(E7);
			break;
		}
		 
		 
	}
}

// default destructor
sbme280::~sbme280()
{
} //~sbme280
