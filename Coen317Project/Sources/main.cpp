#include <hidef.h>      /* common defines and macros: file found in CodeWarrior folder */
#include "derivative.h"      /* derivative-specific definitions (e.g.: PORTA, DDDRK) */
//#include <string>


#define column0 0x01
#define column1 0x02
#define column2 0x04
#define column3 0x08 


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
  DDRA = 0x0F;  // Keypad
  DDRB = 0xFF;  // Cathodes of 7Seg
  DDRP = 0xFF;  // 7Seg
  
  PORTA = 0x00;
  
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
      }
      
      PORTA_BIT0 = 0; 
      PORTA_BIT1 = 1; 
      
      if(PORTA != column1){
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
      } 
      
      PORTA_BIT1 = 0;
      PORTA_BIT2 = 1;
      
      if(PORTA != column2){
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
      } 
      
      PORTA_BIT2 = 0;
      PORTA_BIT3 = 1;      
      
      if(PORTA != column3){
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
      PORTA_BIT3 = 0;
      
    
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


