;*****************************************************************
;* This stationery serves as the framework for a                 *
;* user application (single file, absolute assembly application) *
;* For a more comprehensive program that                         *
;* demonstrates the more advanced functionality of this          *
;* processor, please see the demonstration applications          *
;* located in the examples subdirectory of the                   *
;* Freescale CodeWarrior for the HC12 Program directory          *
;*****************************************************************

; export symbols
            XDEF Entry, _Startup            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point
   
; Include derivative-specific definitions 
		INCLUDE 'derivative.inc' 

ROMStart    EQU  $4000  ; absolute address to place my code/constant data

; variable/data section
            ORG RAMStart

; Insert here your data definition.
sevsegdata dc.b  $BF, $86, $DB, $CF, $E6, $ED, $FD, $87, $FF, $EF, $F7, $FC, $B9, $DE, $F9, $F1
PAdata dc.b $10, $20, $40, $80
i ds.b 1
key ds.b 1
myptp dc.b $0E, $0D, $0B, $07 


; code section
            ORG   ROMStart

Entry:
_Startup:  
            LDS   #RAMEnd+1       ; initialize the stack pointer
            

; PLL code for 24MHz bus speed from a 4/8/16 crystal
;            sei
;            ldx #0
;            bclr CLKSEL,x,%10000000 ; clear bit 7, clock derived from oscclk
;            bset PLLCTL,x, %01000000 ; Turn PLL on, bit 6 =1 PLL on, bit 6=0 PLL off
;            ldaa #$05 ; 5+1=6 multiplier
;            staa SYNR,x
            ; ldaa #$03 ; divisor=3+1=4, 16*2*6 /4 = 48MHz PLL freq, for 16 MHz crystal
;            ldaa #$01 ; divisor=1+1=2, 8*2*6 /2 = 48MHz PLL freq, for 8 MHz crystal
            ; ldaa #$00 ; divisor=0+1=1, 4*2*6 /1 = 48MHz PLL freq, for 4 MHz crystal
;            staa REFDV,x
;wait_b3:    brclr CRGFLG,x, %00001000, wait_b3 ; Wait until bit 3 = 1
;            bset CLKSEL,x, %10000000

; Dragon12-Light Board:
            ; Port A: Connected to Keypad. Configure it as input/output (DDRA).
            ; Port B: Connected to LEDs. Configure it as output (DDRB). Also set PJ1 to 0, and set DDRJ as output ($FF)
            ;         Also connected to all four 7-seg anodes (PB0-PB7: A,B, ...,G, Dec. Point). Positive logic for both LEDs and 7-seg
            ;
            ; Port P: The last 4 bits (PP3-PP0) are connected to the cathodes of the 7-seg LEDs. Configure those 4 bits as output (DDRP)
            ;         7-seg LEDs cathodes: Negative logic. A '0' is required to turn on a particular 7-seg display
            ; Port H: Connected to DIPSwitches (H7-H0) and Pushbuttons (H3-H0). Configure it as input (DDRH)
            ;         DIPSwitches (H7-H0): Positive logic. Up: 1, Down: 0
            ;         Pushbuttons (H3-H0): When pressed, they send a 0 and take precedence over the DIPswitches.
            ;                              When not pressed, only the DIPswitches are paid attention to..
            ; Port K: Connected to LCD. Configure it as output
            
            ; Port K (3..0), Port P (3..0), Port T, Port A,B, Port H, Port E: Can be used as general I/O (see headers)
                        
            ; I/O Configuration
            movb #$F0, DDRA          ; set Port A (7-4) to be outputs, Port A (3-0) to be inputs
            movb #$FF, DDRB          ; set Port B to be all output
            movb #$FF, DDRP          ; set Port P (3 to 0) to be all output (the others, I don't care)
            movb #$00, DDRH          ; set Port H to be all input
            movb #$FF, DDRK          ; set Port K to be all output
            

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
            
             ldx #sevsegdata; X <- sevsegdata (X grabs the address)            
             movb #$00, PTP   ; All four 7-seg displays cathodes are set to 0 (i.e., they are turned on)
            
            
;showDIPSW:  ldaa PTH        ; Data from DIP switches appear in A. Note that PTH(3..0) are also the pushbuttons
;                            ; Note that data on the 7-seg displays is only valid for DIP switches 3 to 0. (from 0 to F)
;            ldab A, X       ; B <- [A+sevsegdata].
                            ; If A=$00, then, B = [sevsegdata] = $BF
                            ; If A=$03, then, B = [$03+sevsegdata] = $CF
           

            ldy #PAdata                      
forever:    clr i
                                     
; Loop for i = 0 --> 3
loop:       ldaa i ; A <- [i]
            cmpa #4 ; [i]-4            
            beq next; If [i] = 4 then go to 'next'
                        
            movb A,Y,PORTA ; [PORTA] <- [[Y] + [i]]. Write on 4 MSBs of PORTA
            bsr delay1ms
            
            ldaa PORTA ; A <- [PORTA]. Load A (we are interested in the 4 LSBs)
                        
            bsr getidx
            cmpb #$0F
            bne lol
            clra
            bra lolp

lol         movb i, key
            
            ; key <- key*4:
            lsl key 
            lsl key 
            
            ; B <- B + 4*[i]    
            addb key            
            
            ldaa B,X
            
lolp:       staa PORTB
            
            ;bsr delay1ms

            
            inc i
            bra loop;        
; End of Loop for i = 0 --> 3
            
next:       bra forever

         
; ***********            
; Subroutines
; ***********
getidx      bita #$08; A and 00001000. If A=00001000 -> the result is not 0
            bne is3
            bita #$04; A and 00000100. If A=00000100 -> the result is not 0
            bne is2
            bita #$02; A and 00000010. If A=00000010 -> the result is not 0
            bne is1
            bita #$01; A and 00000001. If A=00000001 -> the result is not 0
            bne is0
            ldab #$0f
            bra endi
            
is3:        ldab #3
            bra endi
is2:        ldab #2
            bra endi
is1:        ldab #1
            bra endi
is0:        ldab #0
endi        rts                                                
    
; It generates a delay of 1 ms + (pshx+pulx=5 cycles = 0.21 ms). So it is basically 1 ms
delay1ms    pshx
            
            ldx #2400 ; #400(4 MHz bus speed by default in Dragon12-Light). #2400 (24MHz bus speed)
loops:      psha      ; 2 cycles
            pula      ; 3 cycles
            nop       ; 1 cycle
            nop       ; 1 cycle
            dbne X,loops; ;3 cycles

            pulx
            rts