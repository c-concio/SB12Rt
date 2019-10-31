#include <hidef.h>      /* common defines and macros: file found in CodeWarrior folder */
#include "derivative.h"      /* derivative-specific definitions (e.g.: PORTA, DDDRK) */


#define column0 0x01
#define column2 0x02
#define column3 0x04
#define column4 0x08 

/*
; I/O usage: 7-seg and DIP switches
            ;  pt  g   f   e   d   c   b   a
            ; PB7 PB6 PB5 PB4 PB3 PB2 PB1 PB0
            ;  1   0   1   1   1   1   1   1   =  0xBF = '0' in the 7-segment display
            ;  1   0   0   0   0   1   1   0   =  0x86 = '1' in the 7-segment display
            ;  1   1   0   1   1   0   1   1   =  0xDB = '2' in the 7-segment display
            ;  1   1   0   0   1   1   1   1   =  0xCF = '3' in the 7-segment display
            ;  1   1   1   0   0   1   1   0   =  0xE6 = '4' in the 7-segment display
            ;  1   1   1   0   1   1   0   1   =  0xED = '5' in the 7-segment display
            ;  1   1   1   1   1   1   0   1   =  0xFD = '6' in the 7-segment display
            ;  1   0   0   0   0   1   1   1   =  0x87 = '7' in the 7-segment display
            ;  1   1   1   1   1   1   1   1   =  0xFF = '8' in the 7-segment display
            ;  1   1   1   0   1   1   1   1   =  0xEF = '9' in the 7-segment display
            ;  1   1   1   1   0   1   1   1   =  0xF7 = 'A' in the 7-segment display
            ;  1   1   1   1   1   1   0   0   =  0xFC = 'B' in the 7-segment display
            ;  1   0   1   1   1   0   0   1   =  0xB9 = 'C' in the 7-segment display
            ;  1   1   0   1   1   1   1   0   =  0xDE = 'D' in the 7-segment display
            ;  1   1   1   1   1   0   0   1   =  0xF9 = 'E' in the 7-segment display
            ;  1   1   1   1   0   0   0   1   =  0xF1 = 'F' in the 7-segment display

*/
                                           

void main(void) { // in Assembly code, this is treated as a SubRoutine


  // Variables
  bool keyPressed = false;
  int keypadValue[8];                      
  


  // Data Direction Register Setup
  DDRA = 0xF0;  // Keypad
  DDRB = 0xFF;  // Cathodes of 7Seg
  DDRP = 0xFF;  // 7Seg
  
  while(true){
    
    
    // Get input from keypad
    while(true){
      // Scan through all the columns and rows
      
      // for all four columns, look through the MSB bits of port A and see if any of them is set
      // if not set, go throught the other columns
      
      
      // look at column 1 and see if any of the bits are pressed
      // Set column0
      PORTA = PORTA OR column0;
      if(PORTA != column0){
        keypadValue = PTA;
          
      }
      
      
      
      
      
      
      
    }
    
    
    keypadValue[] 
    


    // display the note on the 7 segment display




    // output note onto the DAC



    // DAC then outputs to speaker
              
  
  
  }
  
  
  
  
  
  
  
  avg = 0;
  for (i = 0; i < 10; i++) { 
      avg = avg + array[i]; // Since avg is signed, the quantities in array[i] will be sign-extended
  } 
  avg = avg/10; // integer portion ($1F)
  asm ("ldd avg"); // inline Assembly instructions  
  
  while (1) {
    
    DIPSW = PTH; // same as asm("movb PTH, val")
    LEDS = myOR(DIPSW,avg);         
  
    PORTB = LEDS; // or asm("movb LEDS,PORTB")  
  }
  
  
  
}
