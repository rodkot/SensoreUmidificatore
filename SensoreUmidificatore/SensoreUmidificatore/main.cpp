
#include <avr/io.h>
#include <avr/interrupt.h>
 
#include "inc/bme280.h"

BME280_SPI bme;
bool flag = false;
float boarder = 70.f;

 void timer_init()
 {
	 // Set Timer/Counter1 to CTC (Clear Timer on Compare) mode
	 TCCR1B |= (1 << WGM12);
	 
	 // Set the compare value for 5 minutes (assuming 16MHz clock and prescaler of 1024)
	 OCR1A = 46875;  // (5 minutes * 16MHz) / (1024 prescaler)
	 
	 // Enable Timer/Counter1 Compare Match A interrupt
	 TIMSK1 |= (1 << OCIE1A);
	 
	 // Set the prescaler to 1024
	 TCCR1B |= (1 << CS12) | (1 << CS10);
	 
	 // Enable global interrupts
	 sei();
 }
 
 ISR(TIMER1_COMPA_vect)
 {
	flag = true;
 }
 
int main(void)
{
   DDRD = 0xFF;
   
   bme.begin();
 
   timer_init();
   
   // Main program loop
   while (1)
   {
	   if (flag)
	   {
		   bme.readSensor();
		   flag = false;
		   if(bme.getHumidity()<boarder){
			   PORTD = 0b00000001;
		   }else{
			   PORTD = 0;
		   }
		   
	   }
	   // Your main program code here
   }
 
	
	return 0;
}
/* EOF: mcp23s17.c */