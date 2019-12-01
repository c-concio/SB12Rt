; declare delay
 
  XDEF ASMdelay
 
 
; code creates a delay of 150 ms
 
CodeSec: SECTION
ASMdelay:
  pshx
  ldx #60000 ;2 E cycles
loop:
  psha ; 2 E cycles
  pula ; 3 E cycles
  psha
  pula 
  psha
  pula
  psha
  pula
  psha
  pula
  psha
  pula 
  psha
  pula
  psha
  pula
  psha
  pula
  psha
  pula
  psha
  pula
  nop   ; 1 E cycles
  nop   
  dbne x,loop
  pulx
  rts