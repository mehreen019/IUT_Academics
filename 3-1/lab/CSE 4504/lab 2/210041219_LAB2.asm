;task 1
 

mov ah,1
int 21h  
mov cl, al
cmp al,61h
jge greater  
jl less

greater:
    sub cl,32 
    jmp display
        
less:
    add cl,32 
    jmp display 
              
display:  
    mov dl, 0Ah
    mov ah,2  
    int 21h  
    mov dl, 0Dh
    int 21h
    mov dl,cl
    int 21h 
    mov dl, 0Ah 
    int 21h  
    mov dl, 0Dh
    int 21h   
                
;task 2

mov ah,1
int 21h  
mov cl, al
cmp al,61h
jge input_sa 
jl input_ca

input_sa:
    sub cl,32d
    mov ah,2
    
    mov dl, 0Ah 
    int 21h  
    mov dl, 0Dh
    int 21h 
    
    
    mov dl, cl
    mov bl, cl 
    mov cx,0
    jmp cont_add
    
    reset_small_fwd:
        mov dl, 64d
    
    cont_add:
        add dl, 1
        cmp dl,91d
        jge reset_small_fwd
        int 21h
        add cx,1
        cmp cx,5
        jge counter_reset   
        jl cont_add
    
    counter_reset: 
        mov dl, 0Ah 
        int 21h  
        mov dl, 0Dh
        int 21h   
        
        mov dl, bl
        mov cx,0
        jmp cont_sub
    
    reset_small_back:
        mov dl, 91d
        
    cont_sub:
        sub dl, 1
        cmp dl,64d
        jle reset_small_back
        int 21h
        add cx,1
        cmp cx,5
        jge rett   
        jl cont_sub 
        
        
    ret
    
        
input_ca:
    add cl,32d
    mov ah,2
    
    mov dl, 0Ah 
    int 21h  
    mov dl, 0Dh
    int 21h 
    
    
    mov dl, cl 
    mov cx,0
    jmp cont_add2
    
    reset_big_fwd:
        mov dl, 96d
    
    cont_add2:
        add dl, 1
        cmp dl,123d
        jge reset_big_fwd
        int 21h
        add cx,1
        cmp cx,5
        jge counter_reset2   
        jl cont_add2 
    
    counter_reset2: 
        mov dl, 0Ah 
        int 21h  
        mov dl, 0Dh
        int 21h   
        
        mov dl, bl
        mov cx,0
        jmp cont_sub2
    
    reset_big_back:
        mov dl, 123d
        
    cont_sub2:
        sub dl, 1
        cmp dl,96d
        jle reset_big_back
        int 21h
        add cx,1
        cmp cx,5
        jge rett   
        jl cont_sub2
        
    ret 
    
rett:
    ret
   