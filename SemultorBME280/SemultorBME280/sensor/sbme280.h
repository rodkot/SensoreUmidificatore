/* 
* sbme280.h
*
* Created: 28.05.2023 0:10:12
* Author: rodio
*/


#ifndef __SBME280_H__
#define __SBME280_H__

#include <avr/io.h>

#define    ARRAY_SIZE 3

// Name of Registers used in the BME280
#define    BME280_DIG_H1_REG   0xA1
#define    BME280_DIG_H2_REG   0xE1
#define    BME280_DIG_H3_REG   0xE3
#define    BME280_DIG_H4_REG   0xE4
#define    BME280_DIG_H5_REG   0xE5
#define    BME280_DIG_H6_REG   0xE6
#define    BME280_DIG_H7_REG   0xE7

#define    BME280_REGISTER_CHIPID       0xD0
#define    BME280_REGISTER_CONTROLHUMID     0xF2

class sbme280
{
//variables
public:
uint8_t  A1 = 75;
uint8_t  E1 = 1;
uint8_t  E2 = 76;
uint8_t  E3 = 0 ;
uint8_t  E4 = 24;
uint8_t  E5 = 13;
uint8_t  E6 = 50;
uint8_t  E7 = 0;
protected:
private:

//functions
public:
    uint16_t myArray[ARRAY_SIZE];
	sbme280();
	void wait(void);
	void resolve(uint8_t);
	void response(uint8_t);
	uint8_t transmit(uint8_t);
	uint8_t request();
	
	~sbme280();
protected:
private:
	sbme280( const sbme280 &c );
	sbme280& operator=( const sbme280 &c );

}; //sbme280

#endif //__SBME280_H__
