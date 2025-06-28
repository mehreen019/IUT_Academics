ORG 0100H
.DATA
average db ?
largest db ?
smallest db ?
arr db 50 dup(0)
message db 'Enter the value of N:$'
lm db 'largest num is:$'
sm db 'smallest num is:$'
am db 'average num is:$' 

.CODE
MAIN PROC
MOV AX, @DATA
MOV DS,AX
XOR BX,BX
XOR CX,CX    

lea dx, message ; (similar meaning like Load Effective Address)
mov ah, 09h ;display string function
int 21h ;display message
mov ah, 01h
int 21h   
          
MOV CL, AL
SUB CL, 48d
MOV SI, 0d
XOR AL, AL
CALL inputNum 
              
XOR DI, DI
XOR AL, AL
MOV DI, 0h
CALL FINDLARGEST

mov largest, dl 

XOR DI, DI
XOR Ax, Ax
MOV DI, 0h
MOV AL, 255D
CALL FINDSMALLEST   

mov smallest, dl
                 
XOR AX, AX
MOV DI, 0h
CALL FINDAVERAGE 

mov average, dl

MOV AH, 4Ch
MOV AL, 00h
INT 21h

MAIN ENDP     

INPUTNUM PROC
    INPUT:
      MOV AH, 01H
      int 21h
      MOV ARR[SI], AL
      INC SI
      DEC CL
      XOR AL, AL
      CMP CL, 0d
      JG INPUT   
    RET
INPUTNUM ENDP

findLargest PROC   
    FINLARGE:  
         MOV BL, ARR[DI]
         CMP AL, BL
         JG CONT 
         MOV AL, BL
         CONT:
            INC DI
            CMP DI, SI
            JL FINLARGE
             
    mov bl, al
    LEA DX, LM
    mov ah, 09h
    int 21h    
    
    mov ah, 02h
    mov dl, bl
    int 21h  
    RET
findLargest ENDP 

findSmallest PROC
    FINSMOL:
       MOV BL, ARR[DI]
       CMP AL, BL
       JB CONTag 
       MOV AL, BL
       CONTag:
        INC DI
        CMP DI, SI
        JL FINSMOL
              
    mov bl, al
    LEA DX, SM 
    mov ah, 09h
    int 21h    
    
    mov ah, 02h
    mov dl, bl
    int 21h 
    RET
findSmallest ENDP    

findAverage PROC
    ADDNUM:
       ADD AL, ARR[DI]
       INC DI
       CMP DI, SI
       JL ADDNUM
       
    MOV BX, SI
    DIV BL
    mov bl, al
    LEA DX, AM 
    mov ah, 09h
    int 21h    
    
    mov ah, 02h
    mov dl, bl
    int 21h 
    RET
        
END MAIN 
