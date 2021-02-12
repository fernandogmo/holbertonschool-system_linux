GLOBAL asm_strpbrk
asm_strpbrk:
    push    rbp
    mov     rbp, rsp
    push    rcx
    push    rbx
    push    r8
    push    r9

    xor     rax, rax
    xor     rcx, rcx
    xor     r8, r8
    xor     r9, r9
.INNER_LOOP:
    mov     r8b, [rdi + rcx]
    test    r8b, r8b
    jz      .EXIT
    xor     rbx, rbx
.OUTER_LOOP:
    mov     r9b, [rsi + rbx]
    test    r9b, r9b
    jz      .BREAK
    cmp     r8b, r9b
    je      .MOVE_PTR
    inc     rbx
    jmp     .OUTER_LOOP
.BREAK:
    inc     rcx
    jmp     .INNER_LOOP
.MOVE_PTR:
    mov     rax, rdi
    add     rax, rcx
.EXIT:
    pop     r9
    pop     r8
    pop     rbx
    pop     rcx
    mov     rsp, rbp
    pop     rbp
    ret
