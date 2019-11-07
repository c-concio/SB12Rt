#include <hidef.h>      /* common defines and macros: file found in CodeWarrior folder */
#include "derivative.h"      /* derivative-specific definitions (e.g.: PORTA, DDDRK) */
//#include <string>


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

void playSound(char,int,int);
void displayNote(char,int);
int getOctave();
                                           

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
     
      PORTA_BIT0 = 1;
      
      if(PORTA != column0){
        while(PORTA_BIT4){//a flat
          playSound('a', 1, 1);
          //displayNote();
        }
        while(PORTA_BIT5){//a
          playSound('a', 0, 1);
          //displayNote();
        }
        while(PORTA_BIT6){//e flat
          playSound('e', 1, 1);
          //displayNote();
        }
        while(PORTA_BIT7){//e
          playSound('e', 0, 1);
          //displayNote();
        }
      } else if(PORTA != column1){
        while(PORTA_BIT4){//b flat
          playSound('b', 1, 1);
          //displayNote();
        }
        while(PORTA_BIT5){//b
          playSound('b', 0, 1);
          //displayNote();
        }
        while(PORTA_BIT6){
          //Nothing
        }
        while(PORTA_BIT7){//f
          playSound('f', 0, 1);
          //displayNote();
        }
      } else if(PORTA != column2){
       while(PORTA_BIT4){
          //Nothing
        }
        while(PORTA_BIT5){//c
          playSound('c', 0, 1);
          //displayNote();
        }
        while(PORTA_BIT6){//g flat
          playSound('g', 1, 1);
          //displayNote();
        }
        while(PORTA_BIT7){//g
          playSound('g', 0, 1);
          //displayNote();
        } 
      } else if(PORTA != column3){
       while(PORTA_BIT4){//a flat
          playSound('d', 1, 1);
          //displayNote();
        }
        while(PORTA_BIT5){//a
          playSound('d', 0, 1);
          //displayNote();
        }
        while(PORTA_BIT6){
          //Nothing
        }
        while(PORTA_BIT7){
          //Nothing
        } 
      }
      PORTA_BIT0 = 0;
    
    }
  } 
    
    
    


    // display the note on the 7 segment display




    // output note onto the DAC



    // DAC then outputs to speaker
    
    
             
    
}

void playSound(char note, int flat, int octave){
  switch(note){
    case 'a':
      if(flat == 1){
          
      } else{
        
      }
      break;
    case 'b':
      if(flat == 1){
          
      } else{
        
      }
      break;
    case 'c':
    case 'd':
      if(flat == 1){
          
      } else{
        
      }
      break;
    case 'e':
      if(flat == 1){
          
      } else{
        
      }
      break;
    case 'f':
      break;
    case 'g':
      if(flat == 1){
          
      } else{
        
      }
      break;
    
  }
}

void displayNote(char note, int flat){
  
  
  switch (note) // <--- can i do this??
	 
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

int getOctave(){
  // read the DIP switches
  if (PTH_PTH0)
    return 0; 
  else if (PTH_PTH1)
    return 1;
  else if (PTH_PTH2)
    return 2;
  else if (PTH_PTH3)
    return 3;
  else if (PTH_PTH4)
    return 4;
  else if (PTH_PTH5)
    return 5;
  else if (PTH_PTH6)
    return 6;
  else if (PTH_PTH7)
    return 7;
}
