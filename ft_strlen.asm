bits 64

section .text
global ft_strlen

; size_t strlen(const char *s);
ft_strlen:
    ; Initialize length to 0
    xor     rax, rax

strlen_loop:
    ; Compare current character with '\0'. If zero, we're done
    cmp     byte [rdi + rax], 0
    je      done

    ; Increment length and repeat
    inc     rax
    jmp     strlen_loop

done:
    ; Return length in rax
    ret
