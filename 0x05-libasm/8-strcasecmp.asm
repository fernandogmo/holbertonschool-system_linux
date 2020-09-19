GLOBAL asm_strcasecmp
asm_strcasecmp:
        xor     edx, edx
.LOOP:
        mov     cl, BYTE [rdi+rdx]
        mov     al, BYTE [rsi+rdx]
        lea     r9d, [rcx-'A']
        lea     r8d, [rcx+'a'-'A']
        cmp     r9b, 'z'-'a'
        cmovb   ecx, r8d
        lea     r9d, [rax-'A']
        lea     r8d, [rax+'a'-'A']
        cmp     r9b, 'z'-'a'
        cmovnb  r8d, eax
        movsx   eax, cl
        movsx   r8d, r8b
        sub     eax, r8d
        jne     .RETURN
        inc     rdx
        test    cl, cl
        jne     .LOOP
.RETURN:
        ret
