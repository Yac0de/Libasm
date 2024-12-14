bits 64

section .text
global ft_strcpy

; char *strcpy(char *dest, const char *src)
ft_strcpy:
    ; Save the destination address for return
    mov rax, rdi

copy_loop:
    ; Copy current byte from src (rsi) to dest (rdi)
    mov al, byte [rsi]
    mov byte [rdi], al

    ; Check if we reached the end of the string
    cmp al, 0
    je done

    ; Advance to the next character
    inc rsi
    inc rdi
    jmp copy_loop

done:
    ret