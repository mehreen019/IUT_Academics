ORG 0000H

; ----- Port definitions -----
PORTA   EQU 00H    ; units (right digit)
PORTB   EQU 02H    ; tens (left digit)
PORTC   EQU 04H    ; LED
PORT_CON EQU 06H   ; control port

; ----- 7-seg patterns for digits 0-9 (immediates) -----
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

; ----- Start -----
START:
    MOV DX, PORT_CON
    MOV AL, 10000000B
    OUT DX, AL

    JMP COUNTDOWN

; ----- Countdown 99 -> 00 (nested loops) -----
COUNTDOWN:
    MOV BL, 9          ; tens = 9

TENS_LOOP:
    MOV BH, 9          ; units = 9

UNITS_LOOP:
    ; show units (BH)
    MOV AL, BH
    CALL SHOW_DIGIT
    MOV DX, PORTA
    OUT DX, AL

    ; show tens (BL)
    MOV AL, BL
    CALL SHOW_DIGIT
    MOV DX, PORTB
    OUT DX, AL

    ; LED toggle + delays
    CALL LED_BLINK

    ; decrement units and loop while >= 0 (signed test)
    DEC BH
    CMP BH, 0
    JGE UNITS_LOOP

    ; decrement tens and loop while >= 0
    DEC BL
    CMP BL, 0
    JGE TENS_LOOP

    ; repeat forever (same behaviour as your original)
    JMP COUNTDOWN

; -----------------------------
; SHOW_DIGIT: AL = 0..9 -> AL = 7-seg pattern
; -----------------------------
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

    ; out-of-range — return blank
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

; -----------------------------
; LED_BLINK: replicates your LED on/off + extra delay
; -----------------------------
LED_BLINK:
    MOV DX, PORTC
    MOV AL, 00000001B
    OUT DX, AL
    MOV CX, 05000H
LBL1:
    LOOP LBL1

    MOV DX, PORTC
    MOV AL, 00000000B
    OUT DX, AL
    MOV CX, 05000H
LBL2:
    LOOP LBL2

    ; extra gap (matches original multiple MOV CX,...)
    MOV CX, 05000H
LBL3:
    LOOP LBL3

    RET

END
