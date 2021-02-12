GLOBAL asm_strstr
asm_strstr:
    xor     rax, rax
    xor     rcx, rcx
    xor     r8, r8
    xor     r9, r9
.LOOP:
    mov     rdx, rcx
    xor     rbx, rbx
.MATCH:
    mov     r8b, [rdi + rcx]
    mov     r9b, [rsi + rbx]
    test    r9b, r9b
    jz      .MATCHED
    cmp     r8b, r9b
    jne     .BREAK
    inc     rcx
    inc     rbx
    jmp     .MATCH
.BREAK:
    mov     r8b, [rdi + rcx]
    test    r8b, r8b
    jz      .EXIT
    inc     rcx
    jmp     .LOOP
.MATCHED:
    mov     rax, rdi
    add     rax, rdx
.EXIT:
    ret
