;task 1
org 100h

.DATA
input_string DB 'We are IUT Students', 0Dh, 0Ah, '$'
number DB 100d

.CODE

MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    XOR CX, CX  
       
    MOV AH, 9
    LEA DX, input_string
    INT 21h
    
    MOV CX, 200d
    MOV BL, 0
    
    MOV SI, DX
    
    JMP CONT_LOOP
    
    CONT_LOOP:
        MOV AL, [SI]
        CMP AL, 24h
        JZ FIN
        
        ADD SI,1d
        ADD BL,1d  
        LOOP CONT_LOOP    
    
    FIN:
        MOV DL, BL 
        MOV DH, 0H
        ;ADD DL, 48d
        MOV AH, 2
        INT 21H
        MOV BL, DL
        MOV BH, 10D
        
        
    FINFR:
        MOV AH, 4CH
        INT 21H
          
MAIN ENDP
END MAIN
RET
        