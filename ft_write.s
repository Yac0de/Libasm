section .text
global ft_write
extern __errno_location

; ssize_t write(int fd, const void *buf, size_t count);
ft_write:
 ; Perform the syscall
 mov     rax, 1              ; Syscall number for write
 syscall

 ; Check if syscall succeeded
 cmp     rax, 0              ; Check if rax >= 0
 jge     done                ; If syscall succeeded, skip error handling

 ; Handle the error
 neg     rax                 ; Convert error code to positive
 mov     rdi, rax            ; Store the positive error code in rdi
 call    [rel __errno_location wrt ..got] ; Get errno address
 mov     [rax], edi          ; Set errno

 mov     rax, -1             ; Return -1 for failure
 ret

done:
 ; Syscall succeeded, return number of bytes written
 ret
