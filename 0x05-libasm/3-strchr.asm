GLOBAL asm_strchr
asm_strchr:
.LOOP:
    mov     al, [rdi]
    cmp     al, sil
    je      .MATCH
    test    al, al
    jz      .NULL
    inc     rdi
    jmp     .LOOP
.NULL:
    xor     rax, rax
    jmp     .RETURN
.MATCH:
    mov     rax, rdi
.RETURN:
    ret
