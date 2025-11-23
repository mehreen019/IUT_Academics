ORG 0000H

PORTA   EQU 00H    
PORTB   EQU 02H    
PORTC   EQU 04H    
PORT_CON EQU 06H   

PAT0    EQU 00111111B
PAT1    EQU 00000110B
PAT2    EQU 01011011B
PAT3    EQU 01001111B
PAT4    EQU 01100110B
PAT5    EQU 01101101B
PAT6    EQU 01111101B
PAT7    EQU 00000111B
PAT8    EQU 01111111B
PAT9    EQU 01101111B

START:
    MOV DX, PORT_CON
    MOV AL, 10000000B
    OUT DX, AL
    
    
    MOV DI, 999
    
MAIN_LOOP:
    
    MOV AX, DI          
    MOV BX, 100         
    MOV DX, 0           
    DIV BX              
    MOV CL, AL          
    
    
    MOV AX, DX          
    MOV BX, 10          
    MOV DX, 0           
    DIV BX              
    MOV BL, AL          
    MOV BH, DL          
    
    MOV AL, BH
    CALL SHOW_DIGIT
    MOV DX, PORTA
    OUT DX, AL

    MOV AL, BL
    CALL SHOW_DIGIT
    MOV DX, PORTB
    OUT DX, AL
    
    MOV AL, CL
    CALL SHOW_DIGIT
    MOV DX, PORTC
    OUT DX, AL
    
    CALL DELAY
    

    DEC DI
    CMP DI, 0FFFFH   
    JNE MAIN_LOOP
    

    MOV DI, 999
    JMP MAIN_LOOP


SHOW_DIGIT:
    CMP AL, 0
    JE L0
    CMP AL, 1
    JE L1
    CMP AL, 2
    JE L2
    CMP AL, 3
    JE L3
    CMP AL, 4
    JE L4
    CMP AL, 5
    JE L5
    CMP AL, 6
    JE L6
    CMP AL, 7
    JE L7
    CMP AL, 8
    JE L8
    CMP AL, 9
    JE L9
    
    MOV AL, 00000000B
    RET
L0:
    MOV AL, PAT0
    RET
L1:
    MOV AL, PAT1
    RET
L2:
    MOV AL, PAT2
    RET
L3:
    MOV AL, PAT3
    RET
L4:
    MOV AL, PAT4
    RET
L5:
    MOV AL, PAT5
    RET
L6:
    MOV AL, PAT6
    RET
L7:
    MOV AL, PAT7
    RET
L8:
    MOV AL, PAT8
    RET
L9:
    MOV AL, PAT9
    RET

DELAY:
    MOV CX, 08000H
DELAY_LOOP:
    LOOP DELAY_LOOP
    RET
END