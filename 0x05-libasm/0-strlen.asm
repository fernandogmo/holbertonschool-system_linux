; This program calculates the length of a string as a size_t
section .text
global asm_strlen
asm_strlen:
	enter	64, 0
	xor	rax, rax
	cmp	BYTE [rdi], 0
	je	.DONE

.LOOP:
	add 	rax, 1
	cmp	BYTE [rdi+rax], 0
	jne	.LOOP
	jmp	.DONE

.DONE:
	leave
	ret
