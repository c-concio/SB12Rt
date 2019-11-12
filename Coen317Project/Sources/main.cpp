#include <hidef.h>      /* common defines and macros: file found in CodeWarrior folder */
#include "derivative.h"      /* derivative-specific definitions (e.g.: PORTA, DDDRK) */
//#include <string>
#include "notes.h"

#define column0 0x01
#define column1 0x02
#define column2 0x04
#define column3 0x08 

// ------------------ Global Variable ------------------
int octave;

// ------------------ Start of Interrupts Section ------------------
#pragma CODE_SEG NON_BANKED

// ISR functions
interrupt void changeOctave(void){
  if (PTH_PTH0){
    octave = 0; 
    PTH_PTH0 = 0;
  } 
  else if (PTH_PTH1){
    octave = 1; 
    PTH_PTH1 = 0;
  }  
  else if (PTH_PTH2){
    octave = 2; 
    PTH_PTH2 = 0;
  }   
  else if (PTH_PTH3){
    octave = 3; 
    PTH_PTH3 = 0;
  }   
  else if (PTH_PTH4){
    octave = 4; 
    PTH_PTH4 = 0;
  }   
  else if (PTH_PTH5){
    octave = 5; 
    PTH_PTH5 = 0;
  }   
  else if (PTH_PTH6){
    octave = 6; 
    PTH_PTH6 = 0;
  }   
  else if (PTH_PTH7){
    octave = 7; 
    PTH_PTH7 = 0;
  }         
}

#pragma CODE_SEG DEFAULT

// interrupt vector table
typedef void (*near tIsrFunc)(void);
const tIsrFunc _vect[] @0xFFCC = {
  changeOctave
};

// ------------------ End of Interrupts Section ------------------


void playSound(char,int,int);
void displayNote(char,int);
int getOctave();

  
                                           

void main(void) { // in Assembly code, this is treated as a SubRoutine


  // -------------- Variables --------------                 
  


  // Data Direction Register Setup
  DDRA = 0x0F;  // Keypad
  DDRB = 0xFF;  // Cathodes of 7Seg
  DDRP = 0xFF;  // 7Seg
  
  PORTA = 0x00;
  
  // Setup interrupts to work with PORTH
  // enable all pins in PORTH to cause interrupts
  PIEH = 0xFF;
  // select the polarities of PORTH to either be falling edge(0) or rising edge(1)
  PPSH = 0xFF;
  
  // -------------- PWM Setup --------------  
  
  // PWM registers:
  // PWMCTL (PWM Control Register): 
  
  // 1. Setup PWM channel A
  // 2. Set prescale factor
  // 3. Set alignment
  // 4. Assign period value
  // 5. Assign duty cycle
  
  PWMCLK = 0x00; // Selects clock A as the clcock source to PWM0
  PWMPOL = 0x01;
  PWMCTL = 0x0C;
  PWMCAE = 0x00;
  PWMPRCLK = 0x04; // prescale set
   
  // -------------- Get input from keypad --------------
  while(1){
    // Scan through all the columns and rows
    
    // for all four columns, look through the MSB bits of port A and see if any of them is set
    // if not set, go throught the other columns
    
    
    
    // ----- COLUMN 0 -----
    PORTA_BIT0 = 1;
    
    if(PORTA != column0){
      while(PORTA_BIT4){//a flat
        playSound('a', 1, octave);
        //displayNote();
        
        // enable PWM signal
        PWME = 0x01;
      }
      while(PORTA_BIT5){//a
        playSound('a', 0, octave);
        //displayNote();
        
        
        PWME = 0x01;
      }
      while(PORTA_BIT6){//e flat
        playSound('e', 1, octave);
        //displayNote();
        
        
        PWME = 0x01;
      }
      while(PORTA_BIT7){//e
        playSound('e', 0, octave);
        //displayNote();
        
        
        PWME = 0x01;
      }
      
      // disable PWM
      PWME = 0x00;
    }
    
    PORTA_BIT0 = 0;
    
    // ----- COLUMN 1 ----- 
    PORTA_BIT1 = 1; 
    
    if(PORTA != column1){
      while(PORTA_BIT4){//b flat
        playSound('b', 1, octave);
        //displayNote();
        
        PWME = 0x01;
      }
      while(PORTA_BIT5){//b
        playSound('b', 0, octave);
        //displayNote();
        
        PWME = 0x01;
      }
      while(PORTA_BIT6){
        //Nothing
      }
      while(PORTA_BIT7){//f
        playSound('f', 0, octave);
        //displayNote();
        
        PWME = 0x01;
      }
      
      PWME = 0x00;
    } 
    
    PORTA_BIT1 = 0;
    
    // ----- COLUMN 2 -----
    PORTA_BIT2 = 1;
    
    if(PORTA != column2){
     while(PORTA_BIT4){
        //Nothing
      }
      while(PORTA_BIT5){//c
        playSound('c', 0, octave);
        //displayNote();
        
        PWME = 0x01;
      }
      while(PORTA_BIT6){//g flat
        playSound('g', 1, octave);
        //displayNote();
        
        PWME = 0x01;
      }
      while(PORTA_BIT7){//g
        playSound('g', 0, octave);
        //displayNote();
        
        PWME = 0x01;
      } 
      
      PWME = 0x00;
    } 
    
    PORTA_BIT2 = 0;
    
    // ----- COLUMN 3 -----
    PORTA_BIT3 = 1;      
    
    if(PORTA != column3){
     while(PORTA_BIT4){//a flat
        playSound('d', 1, octave);
        //displayNote();
        
        PWME = 0x01;
      }
      while(PORTA_BIT5){//a
        playSound('d', 0, octave);
        //displayNote();
        
        PWME = 0x01;
      }
      while(PORTA_BIT6){
        //Nothing
      }
      while(PORTA_BIT7){
        //Nothing
      } 
      
      PWME = 0x00;
    }
    
    PORTA_BIT3 = 0;
  }      
    
}

// ------------------ playSound Function ------------------
void playSound(char note, int flat, int octave){

  // PWMPER0 period
  // PWMDTY0 duty cycle

  switch(note){
    case 'a':
      if(flat == 1){
        PWMPER0 = noteAb/(2^octave);
      } else{
        PWMPER0 = noteA/(2^octave);
      }
      break;
    case 'b':
      if(flat == 1){
        PWMPER0 = noteBb/(2^octave);
      } else{
        PWMPER0 = noteB/(2^octave);
      }
      break;
    case 'c':
      PWMPER0 = noteC/(2^octave);
      break;
    case 'd':
      if(flat == 1){
        PWMPER0 = noteDb/(2^octave);
      } else{
        PWMPER0 = noteD/(2^octave);
      }
      break;
    case 'e':
      if(flat == 1){
        PWMPER0 = noteEb/(2^octave);
      } else{
        PWMPER0 = noteE/(2^octave);
      }
      break;
    case 'f':
      PWMPER0 = noteF/(2^octave);
      break;
    case 'g':
      if(flat == 1){
        PWMPER0 = noteGb/(2^octave);
      } else{
        PWMPER0 = noteG/(2^octave);
      }
      break;
  }
  
  // Set the octave
  PWMDTY0 = PWMPER0/2;
}

 //-------------------Display on 7-segment--------------------
 
 void displayNote(char note, int flat){
  
  
  switch (note) {
    
	 
		case 'a':
		 //key="1";
		 if(flat==0){   //if flat==0 (ie: regular root note)
		 PTP=0x04;
		 PORTB=0x77;   //display just root note
		 }
		 if(flat==1){    // if flat==1 (ie: flat note)
		 PTP=0x04;
		 PORTB=0x77;  
		 PTP=0x08;
		 PORTB=0x7c;    //Display root note with a "b" prefix
		 }
		 break;
		 
		case 'b':
		 //key="2";
		 if (flat==0){
		 PTP=0x04;
		 PORTB=0x7C;
		 }
		 if(flat==1){
		 PTP=0x04;
		 PORTB=0x7C;
		  PTP=0x08;
		 PORTB=0x7c;
		 }
		 break;
		 
		case 'd':
		 //key="A";
		 if(flat==0){
		 PTP=0x04;
		 PORTB=0x5e;
		 }
		 if (flat==1){
		 PTP=0x04;
		 PORTB=0x5e;
		  PTP=0x08;
		 PORTB=0x7c;
		 }
		 break;
		 
		case 'c':       //no C flat
		 //key="6";
		 PTP=0x04;
		 PORTB=0x58;
		 break;
		 
		 
		case 'e':
		// key="7";
		if(flat==0){
			PTP=0x04;
		 PORTB=0x79;
		}
		if(flat==1){
		PTP=0x04;
		 PORTB=0x79;
		  PTP=0x08;
		 PORTB=0x7c;
		}
		break;
		
		case 'g':
		// key="9";
		if(flat==0){
			PTP=0x04;
		PORTB= 0x6f;
		}
		if(flat==1){
		PTP=0x04;
		PORTB= 0x6f;
		  PTP=0x08;
		 PORTB=0x7c;
		}
		break;
	
		case 'f':        // no F flat
		 //key="0";
		 PTP=0x04;
		 PORTB=0x71;
		 break;
		 
  }
		 
}
