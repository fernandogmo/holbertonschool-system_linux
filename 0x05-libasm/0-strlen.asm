GLOBAL asm_strlen
asm_strlen:
	xor	eax, eax
	cmp	BYTE [rdi], 0
	je	.DONE
.LOOP:
	inc	rax
	cmp	BYTE [rdi+rax], 0
	jne	.LOOP
.DONE:
	ret
