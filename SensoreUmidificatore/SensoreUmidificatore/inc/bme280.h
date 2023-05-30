

#ifndef __BME280_SPI_H__

#define __BME280_SPI_H__

#include <avr/io.h>



#define BME280_ADDRESS      0x77          // define the default I2C address

// Name of Registers used in the BME280
#define    BME280_DIG_H1_REG   0xA1
#define    BME280_DIG_H2_REG   0xE1
#define    BME280_DIG_H3_REG   0xE3
#define    BME280_DIG_H4_REG   0xE4
#define    BME280_DIG_H5_REG   0xE5
#define    BME280_DIG_H6_REG   0xE6
#define    BME280_DIG_H7_REG   0xE7
    
#define    BME280_REGISTER_CHIPID       0xD0
#define    BME280_REGISTER_VERSION      0xD1
#define    BME280_REGISTER_SOFTRESET    0xE0
#define    BME280_REGISTER_CAL26        0xE1
#define    BME280_REGISTER_CONTROLHUMID     0xF2
#define    BME280_REGISTER_CONTROL          0xF4
#define    BME280_REGISTER_CONFIG           0xF5
#define    BME280_REGISTER_PRESSUREDATA     0xF7
#define    BME280_REGISTER_TEMPDATA         0xFA
#define    BME280_REGISTER_HUMIDDATA        0xFD

typedef int8_t byte;

// structure to hold the calibration data that is programmed into the sensor in the factory
// during manufacture

struct BME280_Calibration_Data
{
    public:
        uint8_t  dig_H1;
        int16_t  dig_H2;
        uint8_t  dig_H3;
        int16_t  dig_H4;
        int16_t  dig_H5;
        int8_t   dig_H6;
    
};

/*=========================================================================

Main Class for the BME280 SPI library

=========================================================================*/


class BME280_SPI

{
    
public:
    
    BME280_SPI();							// use this for hardware SPI

	bool  begin(void);
    
    void readSensor(void);
    float getHumidity(void);
    
private:
    
    BME280_Calibration_Data cal_data;
   
    void readHumidity(void);
    void readSensorCoefficients(void);
    
	float    tempcal;							// stores the temp offset calibration
    float    humidity;                          // stores humidity
    
    // functions used for sensor communications
    
    uint8_t spixfer(uint8_t x);
    void      write8(byte reg, byte value);
    uint8_t   read8(byte reg);
    uint16_t  read16(byte reg);
	uint32_t  read24(byte reg);
    int16_t   readS16(byte reg);
    uint16_t  read16_LE(byte reg); // little endian
    int16_t   readS16_LE(byte reg); // little endian
    uint8_t   _i2caddr;
    int32_t   _sensorID;
    int32_t t_fine;

};

#endif
