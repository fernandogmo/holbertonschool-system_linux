GLOBAL asm_strncmp
asm_strncmp:
        xor	eax, eax
        test	rdx, rdx
        je      .RETURN
.LOOP:
        movzx	ecx, BYTE [rdi+rax]
        movzx	r8d, BYTE [rsi+rax]
        test	ecx, ecx
        je	.EXIT
        cmp	cl, r8b
        jne	.EXIT
        inc	rax
        cmp	rdx, rax
        jne	.LOOP
.EXIT:
        sub	ecx, r8d
        mov	eax, ecx
        sar	eax, 31
        test	ecx, ecx
        mov	edx, 1
        cmovg	eax, edx
.RETURN:
        ret