GLOBAL asm_strspn
asm_strspn:
    push    rbp
    mov     rbp, rsp
    push    rcx
    push    r8
    push    r9

    xor     rax, rax
    xor     r8, r8
    xor     r9, r9
.OUTER_LOOP:
    mov     r8b, [rdi + rax]
    test    r8b, r8b
    jz      .EXIT
    xor     rcx, rcx
.INNER_LOOP:
    mov     r9b, [rsi + rcx]
    test    r9b, r9b
    jz      .EXIT
    cmp     r8b, r9b
    je      .BREAK
    inc     rcx
    jmp     .INNER_LOOP
.BREAK:
    inc     eax
    jmp     .OUTER_LOOP
.EXIT:
    pop     r9
    pop     r8
    pop     rcx
    mov     rsp, rbp
    pop     rbp
    ret
