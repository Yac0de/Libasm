extern malloc
extern ft_strlen
extern ft_strcpy

global ft_strdup

section .text

; char *strdup(const char *s);
ft_strdup:
    ; Save the original string address in rbx
    mov     rbx, rdi

    ; Calculate string length using ft_strlen
    call    ft_strlen

    ; Allocate memory using malloc
    inc     rax                 ; Add 1 for the null terminator
    mov     rdi, rax            ; Pass size to malloc
    call    malloc wrt ..plt    ; Call malloc through PLT

    ; Check if malloc failed
    test    rax, rax            ; Is rax NULL?
    je      strdup_fail         ; If NULL, return NULL

    ; Save the allocated memory address in r15
    mov     r15, rax            ; Save malloc result

    ; Copy the string using ft_strcpy
    mov     rdi, rax            ; Set destination to allocated memory
    mov     rsi, rbx            ; Restore original source string
    call    ft_strcpy           ; Perform the copy

    ; Return the allocated memory address
    mov     rax, r15
    ; Return the duplicated string
    ret

strdup_fail:
    xor     rax, rax            ; Return NULL
    ret
