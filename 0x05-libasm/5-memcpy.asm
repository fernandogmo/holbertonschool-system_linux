GLOBAL asm_memcpy
asm_memcpy:
.LOOP:
    test    rdx, rdx
    jz     .DONE
    mov     bl, [rsi]
    mov     [rdi], bl
    inc     rdi
    inc     rsi
    dec     rdx
    jmp     .LOOP
.DONE:
    ret
