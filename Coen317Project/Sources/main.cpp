#include <hidef.h>      /* common defines and macros: file found in CodeWarrior folder */
#include "derivative.h"      /* derivative-specific definitions (e.g.: PORTA, DDDRK) */
#include <string>


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
            ;  1   1   0   1   1   0   1  
             1   =  0xDB = '2' in the 7-segment display
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

void playSound(char,int);
void displayNote();
                                           

void main(void) { // in Assembly code, this is treated as a SubRoutine


  // Variables                  
  


  // Data Direction Register Setup
  DDRA = 0xF0;  // Keypad
  DDRB = 0xFF;  // Cathodes of 7Seg
  DDRP = 0xFF;  // 7Seg
  
  while(1){
    
    
    // Get input from keypad
    while(1){
      // Scan through all the columns and rows
      
      // for all four columns, look through the MSB bits of port A and see if any of them is set
      // if not set, go throught the other columns
      
      
      // look at column 1 and see if any of the bits are pressed
      
      // column0
      
      byte test = PORTA_BIT0;
      
      
      PORTA_BIT0 = 1;
      
      test = PORTA_BIT0;
      if(PORTA != column0){
        while(PORTA_BIT4){
          playSound('a', 1);
          displayNote();
        }
        while(PORTA_BIT5){
          playSound('b', 1);
        }
        while(PORTA_BIT6){
          playSound('c', 1);
        }
        while(PORTA_BIT7){
          playSound('d', 1);
        }
      }
      PORTA_BIT0 = 0;
    
    }
  } 
    
    
    


    // display the note on the 7 segment display




    // output note onto the DAC



    // DAC then outputs to speaker
    
    
             
    
}

void playSound(char note, int octave){
  switch(note){
    case 'ab':
    case 'a':
    case 'bb':
    case 'b':
    case 'c':
    case 'db':
    case 'd':
    case 'eb':
    case 'e':
    case 'f':
    case 'gb':
    case 'g':
    
  }
}

void displayNote(string note){
  
  
  switch (string note) // <--- can i do this??
	 
		case 'ab':
		 //key="1";
		 PORTP=0x04;
		 PORTB=0x77;   //root note
		 PORTP=0x08;
		 PORTB=0x7c;         //b
		 
		case 'bb':
		 //key="2";
		 PORTP=0x04;
		 PORTB=0x7C;
		  PORTP=0x08;
		 PORTB=0x7c;
		 
		case 'db':
		 //key="A";
		 PORTP=0x04;
		 PORTB=0x5e;
		  PORTP=0x08;
		 PORTB=0x7c;
		 
	  case 'a':
		 //key="4";
		 PORTP=0x04;
		 PORTB=0x77;
		 
		 
		case 'b':
		 //key="5";
		 PORTP=0x04;
		 PORTB=0x7c;
		 
		 
		case 'c':
		 //key="6";
		 PORTP=0x04;
		 PORTB=0x58;
		 
		case 'd':
		// key="B";
		PORTP=0x04;
		 PORTB=0x5e;
		 
		case 'eb':
		// key="7";
		PORTP=0x04;
		 PORTB=0x79;
		  PORTP=0x08;
		 PORTB=0x7c;
		 
		case 'gb':
		// key="9";
		PORTP=0x04;
		PORTB= 0x6f;
		  PORTP=0x08;
		 PORTB=0x7c;
		 
		case 'e':
		// key="*";
		PORTP=0x04;
		PORTB=0x79;
		 
		case 'f':
		 //key="0";
		 PORTP=0x04;
		 PORTB=0x71;
		 
		case 'g':
		 //key="#";
		 PORTP=0x04;
		 PORTB=0x6f;
}
