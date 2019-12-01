                         
#include "delay.h"
#include <hidef.h>      /* common defines and macros: file found in CodeWarrior folder */
#include "derivative.h"      /* derivative-specific definitions (e.g.: PORTA, DDDRK) */
#include <stdlib.h>
#include "notes.h"

#define column0 0x01
#define column1 0x02
#define column2 0x04
#define column3 0x08 

// ------------------ Global Variable ------------------
int octave;
int period;

// ------------------ Start of Interrupts Section ------------------
#pragma CODE_SEG NON_BANKED
            
//ISR for timer
interrupt void oc0ISR(void){
  // add the to TC5 the period
  TC5 = TC5 + (period/2);
}

// ISR function for DIP switches
interrupt void changeOctave(void){
  if (PTH_PTH0){
    octave = 0; 
    
  } 
  else if (PTH_PTH1){
    octave = 1; 
    
  }  
  else if (PTH_PTH2){
    octave = 2; 
    
  }   
  else if (PTH_PTH3){
    octave = 3; 
    
  }   
  else if (PTH_PTH4){
    octave = 4; 
    
  }   
  else if (PTH_PTH5){
    octave = 5; 
    
  }   
  else if (PTH_PTH6){
    octave = 6; 
    
  }   
  else if (PTH_PTH7){
    octave = 7; 
    
  }    
    
  PIFH = 0xFF;   
}

#pragma CODE_SEG DEFAULT

// interrupt vector table
typedef void (*near tIsrFunc)(void);
const tIsrFunc _vect[] @0xFFCC = {
  changeOctave
};

 #pragma CODE_SEG DEFAULT /* change code section to DEFAULT (for Small Memory Model, this is $C000) */
 // Interrupt Vector Table   
 typedef void (*near tIsrFunc)(void); // keyword in HCS12 so that the following is in nonbanked (a PPAGE value is not added) memory
 const tIsrFunc _vect2[] @0xFFE4 = { // 0xFFEE is the address to the enchanced capture timer of channel 0
    /* Interrupt table */
    oc0ISR // OC5 Interrupt
 };


// ------------------ End of Interrupts Section ------------------


void playSound(char,int);
void displayNote(char,int);

int pow(int a, int b){
  if(b == 0)
    return 1;
  int val = a;
  for (int i = 0; i < (b-1); i++){
    val *= a;
  }
  return val;
}
                  

//void delay();

void main(void) { // in Assembly code, this is treated as a SubRoutine

  EnableInterrupts;

  // -------------- Variables --------------                 
  
                                                         

  // Data Direction Register Setup
  DDRA = 0x0F;  // Keypad
  DDRB = 0xFF;  // Cathodes of 7Seg
  DDRP = 0xFF;  // 7Seg
  DDRH = 0x00;  // Dip Switches
  
  
  PORTA = 0x00; //
  
  
  
  // Setup interrupts to work with PORTH
  // enable all pins in PORTH to cause interrupts
  PIEH = 0xFF;
  // select the polarities of PORTH to either be falling edge(0) or rising edge(1)
  PPSH = 0xFF;
  
  // ------------ Output Compare ------------
  period = 10;
  
  TSCR1 = 0x10; // clear all flags (TFFCA)
  TSCR2 = 0x06; // set prescaler to 64
  TIOS_IOS5 = 1; // set channel 5 as output compare
  
  TCTL1 = 0x0C; // sets the pin PT0 to high
  TFLG1 = 0xFF; // clears all flags by setting to 1
  
  TC5 = TCNT + period; // delay timer by 10 to start it off

  TCTL1 = 0x04; // make the timer to toggle mode
  TIE = 0x20; // enable interrupt  
  
  // -------------- Get input from keypad --------------
  while(1){
    // Scan through all the columns and rows
    
    // for all four columns, look through the MSB bits of port A and see if any of them is set
    // if not set, go throught the other columns
       
    PORTB = 0x00;
    
    
    // ----- COLUMN 0 -----
    PORTA_BIT0 = 1;
    
    if(PORTA != column0){ 
      while(PORTA_BIT4){
        //Nothing
      }
      while(PORTA_BIT5){//c      
        TSCR1_TEN = 1;    //enable the timer
        period = noteC/pow(2, octave);
        displayNote('c', 0);
      }
      while(PORTA_BIT6){//g flat   
        TSCR1_TEN = 1;
        period = noteGb/pow(2, octave);
        displayNote('g', 1);
      }
      while(PORTA_BIT7){//g      
        TSCR1_TEN = 1;
        period = noteG/pow(2, octave);
        displayNote('g', 0);
      }
      TSCR1_TEN = 0; // disable the timer
    }
    
    PORTA_BIT0 = 0; 
    
    // ----- COLUMN 1 ----- 
    PORTA_BIT1 = 1; 
    
    if(PORTA != column1){
      while(PORTA_BIT4){//d flat
        TSCR1_TEN = 1;
        period = noteDb/pow(2, octave);
        displayNote('d', 1);
      }
      while(PORTA_BIT5){//d   
        TSCR1_TEN = 1;
        period = noteD/pow(2, octave);
        displayNote('d', 0);
      }
      while(PORTA_BIT6){//a flat
        TSCR1_TEN = 1;
        period = noteAb/pow(2, octave);
        displayNote('a', 1);
      }
      while(PORTA_BIT7){//a   
        TSCR1_TEN = 1;
        period = noteA/pow(2, octave);
        displayNote('a', 0);
      }            
        TSCR1_TEN = 0;
    } 
    
    PORTA_BIT1 = 0;
    
    // ----- COLUMN 2 -----
    PORTA_BIT2 = 1;
    
    if(PORTA != column2){
     while(PORTA_BIT4){//e flat
        TSCR1_TEN = 1;
        period = noteEb/pow(2, octave);
        displayNote('e', 1);
      }
      while(PORTA_BIT5){//e   
        TSCR1_TEN = 1;
        period = noteE/pow(2, octave);
        displayNote('e', 0);
      }
      while(PORTA_BIT6){//b flat 
        TSCR1_TEN = 1;
        period = noteBb/pow(2, octave);
        displayNote('b', 1);
      }
      while(PORTA_BIT7){//b  
        TSCR1_TEN = 1;
        period = noteB/pow(2, octave);
        displayNote('b', 0);
      }     
        TSCR1_TEN = 0;
    } 
    
    PORTA_BIT2 = 0;
    
    // ----- COLUMN 3 -----
    PORTA_BIT3 = 1;      
    
    if(PORTA != column3){
     //asm(SWI);
     while(PORTA_BIT4){  
        //Nothing
      }
      while(PORTA_BIT5){//f     
        TSCR1_TEN = 1;
        period = noteF/pow(2, octave);
        displayNote('f', 0);
      }
      while(PORTA_BIT6){
        //Nothing
      }
      while(PORTA_BIT7){//c
        TSCR1_TEN = 1;
        period = noteC/pow(2, octave + 1); //raise the second C by an octave 
        displayNote('c', 0);
      }          
        TSCR1_TEN = 0;
    }
    
    PORTA_BIT3 = 0;
  }      
    
}

 //-------------------Display on 7-segment--------------------
 
 void displayNote(char note, int flat){
 
  
  
  switch (note) {
    
	  // ----- NOTE A -----
		case 'a':
		 //key="1";
		 if(flat==0){   //if flat==0 (ie: regular root note)
  		 PTP = 0x0B;
  		 PORTB=0x77;   //display just root note
		 }
		 if(flat==1){    // if flat==1 (ie: flat note)
  		 PTP = 0x0B;
  		 PORTB=0x77;
  		 
  		 // delay
  		 ASMdelay();
  		 
  		 PTP = 0x07;
  		 PORTB=0x7c;    //Display root note with a "b" prefix
		 }
		 break;
		
		// ----- NOTE B ----- 
		case 'b':
		 //key="2";
		 if (flat==0){
  		 PTP = 0x0B;
  		 PORTB=0x7C;
		 }
		 if(flat==1){
  	   PTP = 0x0B;
  	   PORTB=0x7C;
  	   
  	   ASMdelay();
  		 
  		 PTP = 0x07;
  	  
  	   PORTB=0x7c;
		 }
		 break;
		 
		 // ----- NOTE C -----  
		case 'c':
	   PTP = 0x0B;
		 PORTB=0x39;
		
		 break;
		 
		// ----- NOTE D -----   
		case 'd':
		 //key="A";
		 if(flat==0){
		   PTP = 0x0B;
  		 PORTB=0x5E;
		 }
		 if (flat==1){
  	   PTP = 0x0B;
  	   PORTB=0x5E;
  	   
  	   ASMdelay();
  		 
  		 PTP = 0x07;
  	   PORTB=0x7C;
		 }
		 break;
		
		
  	// ----- NOTE E -----  	 
		case 'e':
		// key="7";
		if(flat==0){		
      PTP = 0x0B;
  	  PORTB=0x79;
		}
		if(flat==1){
      PTP = 0x0B;
      PORTB=0x79;
       
      ASMdelay();
      
    	PTP = 0x07;
      PORTB=0x7C;
		}
		break;
		
		// ----- NOTE F -----  
		case 'f':    
		  PTP = 0x0B;
  	  PORTB=0x71;
		 break;
		
		// ----- NOTE G ----- 
		case 'g':
		// key="9";
		if(flat==0){
	  	PTP = 0x0B;
  	  PORTB=0x3D;
		}
		if(flat==1){
  		PTP = 0x0B;
      PORTB=0x3D;
       
      ASMdelay();
    	 
      PTP = 0x07;
      PORTB=0x7C;
		}
		break;
	
	  
  }
		
}
