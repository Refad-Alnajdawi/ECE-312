#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "defines.h"
#include "hd44780.h"
#include "lcd.h"
#include <util/delay.h>
#include "uart.h"


FILE lcd_str = FDEV_SETUP_STREAM (lcd_putchar, NULL, _FDEV_SETUP_WRITE); // to write on L1
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW); // read/write permission granted
uint16_t Vx, Vy;

int main(int argc, char** argv) {

   lcd_init();
  
   // until line 46 this is all for JOYSTICK ADC conversion
   ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // enables ADC and a divison factor of 128
   ADMUX |= (1<<REFS0) | (1<<ADLAR); // AVCC with external capacitor at AREF pin settings and left adjust ADC result is on
 
   while(1) {
   // FIND X
       
   ADMUX &= ~(1<<MUX0); // ADSC0 which is the x direction on my breadboard 
   ADCSRA |= (1<<ADSC); // starts conversion 
   while((ADCSRA)&(1<<ADSC));

   Vx = ADCH;

   //FIND Y
   
   ADMUX |= (1<<MUX0);// ADSC1 which is the y direction on my breadboard 
   ADCSRA |= (1<<ADSC); // starts conversion
   while((ADCSRA)&(1<<ADSC));

   Vy = ADCH;

   hd44780_outcmd(HD44780_HOME);
   
   fprintf (&lcd_str, "Vx=%u \x1b\xc0Vy=%u ", Vx, Vy);
   }   
   // lines 46 to 52 are for uart and some game initialization 
   stdout = stdin = &uart_str;
   stderr = &lcd_str;
   uart_init();
   UBRR0 = 23; // this number was found by using the UBRRn equation found in the data sheet
   UCSR0B |= (1<<TXEN0) | (1<<RXEN0); // receiver and transmitting pins enabled
   
   
   // for shooting button needs to be initialized
   DDRB &= ~(1<<DDB1); // it is an input (when clicked)
   PORTB |= (1<<PORTB1); // prepare to output high
   
   // to transfer between the controller and the game as well as some initialization
   uint16_t ammo,score,fire; // ammo is 3 digit (aaa) score is 3 digit (sss) fire is used for the button (when shooting)
   score=0;
   char Game_Name, Handle;
   // Game name, Handle, ammo, and score needed on LCD display
   fprintf(stdout,"Q\r\n");
   fscanf(stdin, "%s", Game_Name);
   fprintf(stdout,"Haaa\r\n");
   fscanf(stdin, "%s", Handle);
   fprintf(stdout,"A\r\n");
   fscanf(stdin, "%d", ammo);
   fprintf(stdout,"S\r\n");
   fscanf(stdin, "%d", score);
   
   fprintf(stderr, "%s \x1b\xc0", Game_Name);
   fprintf(stderr, "%s %d %d", Handle, ammo, score);
 
   
}

   
