bits 64

section .text
global ft_strcmp

; int strcmp(const char *s1, const char *s2);
ft_strcmp:

cmp_loop:
    ; Load a byte from s1 and s2
    mov     al, byte [rdi]
    mov     bl, byte [rsi]

    ; Compare bytes, if different return immediately
    cmp     al, bl
    jne     return_diff

    ; Check if we've reached the null terminator, in this case, strings are equal
    cmp     al, 0
    je      strings_equal

    ; Advance pointers
    inc     rdi
    inc     rsi
    jmp     cmp_loop

return_diff:
    ; Sign-extend the values to 64 bits
    movsx   rax, al            ; Sign-extend al to rax
    movsx   rbx, bl            ; Sign-extend bl to rbx
    sub     rax, rbx           ; Compute the signed difference
    ret

strings_equal:
    ; Return 0 if strings are equal
    xor     rax, rax
    ret
