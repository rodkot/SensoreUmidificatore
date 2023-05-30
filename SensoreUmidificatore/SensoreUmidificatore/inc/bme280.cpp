/***************************************************************************
 
 This is a library for the BME280 humidity, temperature & pressure sensor. It
 only supports the SPI bus. It does not support the I2C bus connection.
 
 No warranty is given
 
***************************************************************************/

#include "bme280.h"

#include "SPinterface.h"
#include <math.h>


/***************************************************************************
 
 PUBLIC FUNCTIONS
 
 ***************************************************************************/

BME280_SPI::BME280_SPI( )
{
	tempcal = 0.0;
    humidity = 0.0;
}


void BME280_SPI::readSensor(void)
{
    readHumidity();
}

float BME280_SPI::getHumidity(void)
{
    return humidity;
}

bool BME280_SPI::begin() {
    
   SPinterface().begin();

    
   if (read8(BME280_REGISTER_CHIPID) != 0x60)
       return false;

    readSensorCoefficients();
    
    // Set Humidity oversampling to 1
    // write8(BME280_REGISTER_CONTROLHUMID, 0x01); // Set before CONTROL (DS 5.4.3)
    
    return true;
    
}

void BME280_SPI::readHumidity(void) {
    
    int32_t adc_H = read16(BME280_REGISTER_HUMIDDATA);
    
    int32_t v_x1_u32r;
    
    v_x1_u32r = (t_fine - ((int32_t)76800));
    
    v_x1_u32r = (((((adc_H << 14) - (((int32_t)cal_data.dig_H4) << 20) -
                    
                    (((int32_t)cal_data.dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
                 
                 (((((((v_x1_u32r * ((int32_t)cal_data.dig_H6)) >> 10) *
                      
                      (((v_x1_u32r * ((int32_t)cal_data.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
                    
                    ((int32_t)2097152)) * ((int32_t)cal_data.dig_H2) + 8192) >> 14));
    
    
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
                               
                               ((int32_t)cal_data.dig_H1)) >> 4));
    
    
    v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
    
    v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
    
    float h = (v_x1_u32r>>12);
    
    humidity = h / 1024.0;
    
}


/**************************************************************************

Read the values that are programmed into the sensor during amanufacture

**************************************************************************/

void BME280_SPI::readSensorCoefficients()
{
      cal_data.dig_H1 = read8(BME280_DIG_H1_REG);
      cal_data.dig_H2 = readS16_LE(BME280_DIG_H2_REG);
      cal_data.dig_H3 = read8(BME280_DIG_H3_REG);
      cal_data.dig_H4 = (read8(BME280_DIG_H4_REG) << 4) | (read8(BME280_DIG_H5_REG) & 0xF);
      cal_data.dig_H5 = (read8(BME280_DIG_H6_REG) << 4) | (read8(BME280_DIG_H5_REG) >> 4);
      cal_data.dig_H6 = (int8_t)read8(BME280_DIG_H7_REG);
    
}

/**************************************************************************

Transfers data over the SPI bus

**************************************************************************/

uint8_t BME280_SPI::spixfer(uint8_t x)
{        
		uint8_t response = SPinterface().transmit(x);
		return response;
}


/**************************************************************************

Writes an 8 bit value over SPI

**************************************************************************/

void BME280_SPI::write8(byte reg, byte value)
{
    

	//spixfer(reg & ~0x80);
	SPinterface().begin_transaction();
	spixfer(reg);
    SPinterface().end_transaction();
	
	SPinterface().begin_transaction();
	spixfer(value);
    SPinterface().end_transaction();


	 
    
}

/**************************************************************************
 
 Reads a signed 8 bit value over the SPI bus
 
 **************************************************************************/

uint8_t BME280_SPI::read8(byte reg)
{
    
    uint8_t value;
    
    SPinterface().begin_transaction();

	spixfer(reg);
	value = spixfer(0);
 
	SPinterface().end_transaction();
    
    return value;
    
}


/**************************************************************************

Reads a signed 16 bit value over the SPI bus

**************************************************************************/

uint16_t BME280_SPI::read16(byte reg)
{
    
    uint16_t value;
   
	SPinterface().begin_transaction();

	spixfer(reg);
	uint8_t v1 = spixfer(0); 
	uint8_t v2 = spixfer(0);
	SPinterface().end_transaction();
	 
	value = (v1 << 8) | v2;
    
    return value;
}

uint16_t BME280_SPI::read16_LE(byte reg) {
    
    uint16_t temp = read16(reg);
    
    return (temp >> 8) | (temp << 8);
}

int16_t BME280_SPI::readS16(byte reg)
{
    return (int16_t)read16(reg);
}

int16_t BME280_SPI::readS16_LE(byte reg)
{
    return (int16_t)read16_LE(reg);
}


/**************************************************************************

Reads a signed 24 bit value over the SPI bus

**************************************************************************/

uint32_t BME280_SPI::read24(byte reg)
{
    
    uint32_t value;

	 SPinterface().begin_transaction();
 
	spixfer(reg );

	value = spixfer(0);
	value <<= 8;
	value |= spixfer(0);
	value <<= 8;
	value |= spixfer(0);

	 SPinterface().end_transaction();

	return value;
}
