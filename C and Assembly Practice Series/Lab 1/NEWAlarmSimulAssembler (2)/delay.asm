;------------------------------------------------------
; Alarm System Simulation Assembler Program
; File: delay.asm
; Description: The Delay Module
; Author: Gilbert Arbez
; Date: Fall 2010
;------------------------------------------------------

; Some definitions

	SWITCH code_section

;------------------------------------------------------
; Subroutine setDelay
; Parameters: cnt - accumulator D
; Returns: nothing
; Global Variables: delayCount
; Description: Intialises the delayCount 
;              variable.
;------------------------------------------------------
setDelay: 

   ; Complete this subroutine
   std delayCount ;On met la valeur de delayCount dans l'accumulateur
   rts


;------------------------------------------------------
; Subroutine: polldelay
; Parameters:  none
; Returns: TRUE when delay counter reaches 0 - in accumulator A
; Local Variables
;   retval - acc A cntr - X register
; Global Variables:
;      delayCount
; Description: The subroutine delays for 1 ms, decrements delayCount.
;              If delayCount is zero, return TRUE; FALSE otherwise.
;   Core Clock is set to 24 MHz, so 1 cycle is 41 2/3 ns
;   NOP takes up 1 cycle, thus 41 2/3 ns
;   Need 24 cyles to create 1 microsecond delay
;   8 cycles creates a 333 1/3 nano delay
;	DEX - 1 cycle
;	BNE - 3 cyles - when branch is taken
;	Need 4 NOP
;   Run Loop 3000 times to create a 1 ms delay   
;------------------------------------------------------
; Stack Usage:
	OFFSET 0  ; to setup offset into stack
PDLY_VARSIZE:
PDLY_PR_Y   DS.W 1 ; preserve Y
PDLY_PR_X   DS.W 1 ; preserve X
PDLY_PR_B   DS.B 1 ; preserve B
PDLY_RA     DS.W 1 ; return address

polldelay: pshb
   pshx	      	   ;on place x sur un stack
   pshy            ;on place y sur un stack

   ldx #10000 	   ;10 secondes

   ldy #delayCount ;on place la valeur de delayCount dans y
   ldaa #FALSE     ;accumulator = FALSE



	; Complete this routine
  
delayLoop:         ;loop de delay 1 ms commence ici
   nop
   nop
   nop
   nop
   dex
   bne delayLoop   ;on retourne pour un autre loop de 1 ms si condition n'est pas atteint

   ;si condition atteint on continue   

 
   ldy delayCount  ;Ici on décrement delayCount. Si la condition de BNE est on pass a returnEtExit pour 
   dey
   sty delayCount
   bne returnAndExit
   ldaa #True
   





;restore registers and stack
returnAndExit:
   puly            ;on pull les valeurs de y,x et b du stack
   pulx
   pulb
   rts             ;return du subroutine



;------------------------------------------------------
; Global variables
;------------------------------------------------------
   switch globalVar
delayCount ds.w 1   ; 2 byte delay counter
