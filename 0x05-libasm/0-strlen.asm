global asm_strlen
asm_strlen:
	enter	0, 0
	xor	rax, rax
	cmp	BYTE [rdi], 0
	je	.DONE
.LOOP:
	inc	rax
	cmp	BYTE [rdi+rax], 0
	jne	.LOOP
.DONE:
	leave
	ret
