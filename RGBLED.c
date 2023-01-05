/* 
 * File:   main.c
 * Author: Refad Alnajdawi
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#define F_CPU 1200000UL


int main(void) {

    typedef enum { RED,
            YELLOW,
            GREEN,
            CYAN,
            BLUE,
            MAGENTA,
            WHITE }colour;
    
            colour chosenColour = RED; // by Default the LED needs to be RED
    
    DDRB &= ~(1 << PB4); // ensures PB4 is an input 
    DDRB |= (1 << DDB0); // make PB0 an output
    DDRB |= (1 << DDB1); // make PB1 an output
    DDRB |= (1 << DDB2); // make PB2 and output
    PORTB |= (1 << PORTB4); // when switch not on set PB4 as high 
    
    while(1){
        
        switch(chosenColour){ // after every colour use this statement to increment switch statement 
            
        case RED:{ //for RED only
            
            if(PINB & (1 << PINB4)){ //if the switch NOT pressed
            _delay_ms(100); 
            PORTB &= ~(1 << PORTB0); //BLUE off
            PORTB &= ~(1 << PORTB1); //GREEN off 
            PORTB |= (1 << PORTB2); //RED on
            
        }
            else{ // FOR ALL the else statements below in each case, when the switch is pressed turn off all colours and increment switch statement
            _delay_ms(100);
            PORTB &= ~(1 << PORTB0); // OFF
            PORTB &= ~(1 << PORTB1); // OFF
            PORTB &= ~(1 << PORTB2); // OFF
            chosenColour++; // increment switch statement to go through ALL cases
        }
            break;
        }
        
        case YELLOW:{//Red and Green ON to make yellow  
            if(PINB & (1 << PINB4)){
              _delay_ms(100); //if the switch is NOT pressed
              PORTB |= (1 << PORTB0);// GREEN on
              PORTB &= ~(1 << PORTB1);// BLUE off
              PORTB |= (1 << PORTB2);// RED on
            }
       
            else{
              _delay_ms(100);// if switch is pressed
              PORTB &= ~(1 << PORTB0); // OFF
              PORTB &= ~(1 << PORTB1); // OFF
              PORTB &= ~(1 << PORTB2); // OFF
              chosenColour++; // increment switch statement to go through ALL cases
        }
            break;
        }
        
         case GREEN:{// for GREEN only 
            if(PINB & (1 << PINB4)){
              _delay_ms(100);//if the switch NOT pressed
              PORTB |= (1 << PORTB0);//GREEN on 
              PORTB &= ~(1 << PORTB1);//BLUE off
              PORTB &= ~(1 << PORTB2);//RED off      
        }
       
            else{
              _delay_ms(100);//if switch pressed
              PORTB &= ~(1 << PORTB0);// OFF
              PORTB &= ~(1 << PORTB1);// OFF
              PORTB &= ~(1 << PORTB2);// OFF
              chosenColour++; // increment switch statement to go through ALL cases
        }
            break;
        }
               
        case CYAN:{// for CYAN, turn on GREEN and BLUE only
            if(PINB & (1 << PINB4)){
              _delay_ms(100); //if the switch NOT pressed
              PORTB |= (1 << PORTB0);//Green on
              PORTB |= (1 << PORTB1);//Blue on
              PORTB &= ~(1 << PORTB2);//Red off
        }
       
            else{
              _delay_ms(100);//if switch is pressed
              PORTB &= ~(1 << PORTB0); // OFF
              PORTB &= ~(1 << PORTB1); // OFF
              PORTB &= ~(1 << PORTB2); // OFF
              chosenColour++; // increment switch statement to go through ALL cases
        }
            break;
        }
        
        case BLUE:{// ONLY BLUE
            if(PINB & (1 << PINB4)){
              _delay_ms(100); //if the switch NOT pressed
              PORTB &= ~(1 << PORTB0);//GREEN off
              PORTB |= (1 << PORTB1);//BLUE on
              PORTB &= ~(1 << PORTB2);//RED off
              
        }
       
            else{
              _delay_ms(100);//if switch is pressed
              PORTB &= ~(1 << PORTB0);// OFF
              PORTB &= ~(1 << PORTB1);// OFF
              PORTB &= ~(1 << PORTB2);// OFF
              
              chosenColour++; // increment switch statement to go through ALL cases 
        }
            break;
        }
        
        case MAGENTA:{// both RED and BLUE need to be on
            if(PINB & (1 << PINB4)){
              _delay_ms(100); //if the switch NOT pressed
              PORTB &= ~(1 << PORTB0);//GREEN off
              PORTB |= (1 << PORTB1);//BLUE on
              PORTB |= (1 << PORTB2);//RED on
              
        }
       
            else{
              _delay_ms(100);//if switch is pressed
              PORTB &= ~(1 << PORTB0);//OFF
              PORTB &= ~(1 << PORTB1);//OFF
              PORTB &= ~(1 << PORTB2);//OFF
              chosenColour++; // increment switch statement to go through ALL cases 
        }
            break;
        }
        
        case WHITE:{ // ALL need to be on
            if(PINB & (1 << PINB4)){
              _delay_ms(100); //if the switch NOT pressed
              PORTB |= (1 << PORTB0);// GREEN on
              PORTB |= (1 << PORTB1);// BLUE on
              PORTB |= (1 << PORTB2);// RED on
           
        }
       
            else{
              _delay_ms(100);//if switch pressed
              PORTB &= ~(1 << PORTB0);//OFF
              PORTB &= ~(1 << PORTB1);//OFF
              PORTB &= ~(1 << PORTB2);//OFF
              chosenColour++; // increment switch statement to go through ALL cases 
        }
            break;
            
        default:    
            chosenColour = 0; // the colour we started off with is RED, reset back to RED 
        }
        }
    } 
  return(EXIT_SUCCESS);  
}
