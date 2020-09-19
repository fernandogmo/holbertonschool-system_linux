GLOBAL asm_strcasecmp
asm_strcasecmp:
	xor	rcx, rcx
.MAINLOOP:
	movzx	r8d, BYTE [rdi + rcx]
	movzx	r9d, BYTE [rsi + rcx]
	cmp	r8b, 'A'
	jl	.2ndSTRING
	cmp	r8b, 'Z'
	jg	.2ndSTRING
	add	r8b, 'a' - 'A'
.2ndSTRING:
	cmp	r9b, 'A'
	jl	.DIFF
	cmp	r9b, 'Z'
	jg	.DIFF
	add	r9b, 'a' - 'A'
.DIFF:
	mov	eax, r8d
	sub	eax, r9d
	test	eax, eax
	jnz	.RETURN
	test	r8b, r8b
	jz	.RETURN
	inc	rcx
	jmp	.MAINLOOP
.RETURN:
	ret
