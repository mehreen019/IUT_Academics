                                        CODE SEGMENT
ASSUME CS:CODE, DS:CODE, ES:CODE, SS:CODE
PPIC_C EQU 1EH ; Control register address
PPIC EQU 1CH ; Port C address
PPIB EQU 1AH ; Port B address
PPIA EQU 18H ; Port A address
ORG 1000H
MOV AL, 10000000B ; Control register initialization with a 8255 Mode set
OUT PPIC_C, AL  

MOV AL, 00000000B ; Turning off Port A
OUT PPIA, AL

MOV AL, 00000000B ; Passing Data to Port B
OUT PPIB, AL

MOV AL, 10000000B ; Passing Data to Port C
OUT PPIC, AL


L1:MOV AL, 10000000B ; Passing Data to Port B  

MOV DX, 4

L2:OUT PPIC, AL
MOV BL, AL
MOV AX, 00000000B  
OUT PPIA, AX

MOV AX, 11111111B  
OUT PPIB, AX

MOV AL, BL
   
   

CALL TIMER
CLC
ROL AL, 1 ; Changing Data of Port C
 

OUT PPIC, AL
MOV BL, AL
MOV AX,  00000000B  
OUT PPIB, AX  

MOV AX, 11111111B  
OUT PPIA, AX

MOV AL,BL

CALL TIMER
CLC

ROL AL, 1 ; Changing Data of Port C


DEC DX

JNZ L2
JMP L1


INT 3

TIMER:MOV CX, 0FFFFH
TIMER1: NOP
NOP
NOP
NOP
LOOP TIMER1
RET
CODE ENDS
END