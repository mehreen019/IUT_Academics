org 100h
.DATA  
A db 1,2,3,4,5,6,7,8,9
message db 'Enter the value of N : 2 - 9 : $'  
res dw ?

.CODE 
MAIN PROC
    
    mov ax, @DATA
    mov ds, ax
    xor ax,ax 
    
    mov si, OFFSET A
    mov dx, OFFSET message 
    
    mov ah, 09h 
    int 21h 
    
    mov ah, 01h
    int 21h 
    
    mov cl, al
    sub cl, 48  
    
    xor ax, ax
    xor bx, bx
    xor dx, dx 
    
    Loop_1:
        mov al, [Si]
        mov bl, [Si]
        
        mul bl
        mul bl  
        
        add dx, ax
        xor ax, ax
         
        inc Si
        loop Loop_1 
    
    mov res, dx
    mov bx, res
        
    mov ah, 02h
    int 21h
        

MAIN ENDP
END MAIN
RET