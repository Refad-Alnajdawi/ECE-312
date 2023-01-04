#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <stdbool.h>
#include "defines.h"
#include "hd44780.h"
#include "lcd.h"
#include <util/delay.h>


FILE lcd_str = FDEV_SETUP_STREAM (lcd_putchar, NULL, _FDEV_SETUP_WRITE); // to write on L1
FILE lcd_str2 = FDEV_SETUP_STREAM (lcd_putchar, NULL, _FDEV_SETUP_WRITE); // to write on L2
double t0, t1, distance, time, period, maximum, minimum;

int main(int argc, char** argv) {
   
   lcd_init();
   DDRB &= ~(1<<DDB0); // echo is an INPUT
   PORTB &= ~(1<<PB0); // OUTPUT low high disables input
   TCCR1B |= (1<<CS10); // CLOCK select ON   
   DDRB |= (1<<DDB1); // trig set as an output
   PORTB &= ~(1<<PB1); // OUTPUT set low
   DDRB &= ~(1 << PB2 ); // enable switch as an input
   PORTB |= (1 << PORTB2); // make sure switch is HIGH when not pressed
   
   maximum = -1;
   minimum = -1;
   
   while(1) {   
 
   TCCR1B |= (1<<ICES1); //enables edge select (for while loop below)
   TIFR1 |= (1<<ICF1); // CLEAR flag
    
   PORTB |= (1<<PB1); // create a wave (ON) falling edge 
   _delay_us(10); // need at least 10 microseconds 
   PORTB &= ~(1<<PB1); // create a wave (OFF) rising edge
   
   while (!(TIFR1 & (1<<ICF1))); // for rising edge 
   t0 = ICR1; // reads the time that was just captured
   TIFR1 |= (1<<ICF1); // Clear the Input Capture Flag
   
   TCCR1B &= ~(1<<ICES1); //disables edge select for negative edge
   
   while (!(TIFR1 & (1<<ICF1))); // for falling edge
   t1 = ICR1; //reads the time that was just captured
   TIFR1 |= (1<<ICF1); // Clear the Input Capture Flag
   
   if (t1<t0){ // if/else statement for OVERFLOW check
       period = (65536+t1) - t0;
   }
   else {
       period = t1-t0; 
   }
   
   time = (period)/ 1843200; // 1843200 is clock frequency divided by 8
   distance = (time * 34300); // speed of sound in cm/s times total time gives us the distance
  
   if (minimum == -1){ // to display max or min values 
       maximum = distance;
       minimum = distance;
   }
   else if ( distance >70){
       fprintf(&lcd_str, " Out Of Range"); 
   }
   else if (distance>maximum){ // this keeps updating every time distance becomes greater than previous maximum
       maximum = distance;
   }
   else if (distance<minimum){ // this keeps updating every time distance becomes small than previous minimum
       minimum = distance;
   }
      
   fprintf (&lcd_str, "%0.1f cm\x1b\xc0", distance);// to write on first line of LCD
   _delay_ms(5); // found this delay to be the most comfortable to the eye 
   fprintf (&lcd_str2, "%0.1f cm %0.1f cm\x1b\x02",maximum, minimum);// to write on second line of LCD
   
   if(!(PINB & (1 << PINB2))){ // when the button is pressed (LOW) reset maximum and minimum values ( set back to original value)
   maximum = -1;
   minimum = -1;
   
   }
   }
   }
