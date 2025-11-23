                                                         ASSUME CS:CODE, DS:CODE, ES:CODE, SS:CODE

PPIC_C EQU 1EH ; Control register address
PPIC EQU 1CH ; Port C address
PPIB EQU 1AH ; Port B address
PPIA EQU 18H ; Port A address

ORG 1000H
MOV AL, 10000000B ; Control register initialization with 8255 mode set
OUT PPIC_C, AL
MOV AL, 11111111B ; Turn off Port A
OUT PPIA, AL

MAIN_LOOP:
    ; Sequence of letters: C S E (space) I U T
    MOV BX, OFFSET C_FONT
    CALL DISPLAY_CHAR
    MOV BX, OFFSET S_FONT
    CALL DISPLAY_CHAR
    MOV BX, OFFSET E_FONT
    CALL DISPLAY_CHAR
    MOV BX, OFFSET SPACE_FONT
    CALL DISPLAY_CHAR
    MOV BX, OFFSET I_FONT
    CALL DISPLAY_CHAR
    MOV BX, OFFSET U_FONT
    CALL DISPLAY_CHAR
    MOV BX, OFFSET T_FONT
    CALL DISPLAY_CHAR
    JMP MAIN_LOOP ; Repeat forever

;-------------------------------------------
; DISPLAY_CHAR: Displays font pointed by BX
;-------------------------------------------
DISPLAY_CHAR:
    MOV SI, BX ; SI points to font data
    MOV AH, 00000001B ; Start with first column bit
NEXT_COL:
    MOV AL, BYTE PTR CS:[SI]
    OUT PPIB, AL ; Output pattern to Port B
    MOV AL, AH
    OUT PPIC, AL ; Output control signal to Port C
    CALL TIMER ; Delay for column display
    INC SI
    CLC
    ROL AH, 1
    JNC NEXT_COL ; Loop until all columns displayed
    RET

;-------------------------------------------
; TIMER: Delay routine
;-------------------------------------------
TIMER:
    MOV CX, 300
TIMER1:
    NOP
    NOP
    NOP
    NOP
    LOOP TIMER1
    RET

;-------------------------------------------
; FONT DATA FOR LETTERS
; Each letter is 8 columns (example patterns)
;-------------------------------------------
C_FONT: DB 11111111B,11000000B,10111111B,10111111B,10111111B,10111111B,11000000B,11111111B
S_FONT: DB 11111111B,10011111B,10011111B,11111111B,11111111B,11111001B,11111001B,11111111B
E_FONT: DB 11111111B,10000001B,10011111B,10011111B,10011111B,10000001B,10000001B,11111111B
SPACE_FONT:DB 11111111B,11111111B,11111111B,11111111B,11111111B,11111111B,11111111B,11111111B
I_FONT: DB 11111111B,11111001B,11111001B,11111001B,11111001B,11111001B,11111001B,11111111B
U_FONT: DB 11111111B,11000011B,11000011B,11000011B,11000011B,11000011B,11111111B,11111111B
T_FONT: DB 11111111B,11111001B,11111001B,11111001B,11111001B,11111001B,11111001B,11111111B

CODE ENDS
END