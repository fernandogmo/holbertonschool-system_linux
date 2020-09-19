GLOBAL asm_strstr
asm_strstr:
	xor	rax, rax
	xor	rcx, rcx
	xor	r8, r8
	xor	r9, r9
loop_strstr:
	mov	rdx, rcx
	xor	rbx, rbx
loop_strstr_match:
	mov	r8b, [rdi + rcx]
	mov	r9b, [rsi + rbx]
	test	r9b, r9b
	jz	match_pos
	cmp	r8b, r9b
	jne	break
	inc	rcx
	inc	rbx
	jmp	loop_strstr_match
break:
	mov	r8b, [rdi + rcx]
	test	r8b, r8b
	jz	end
	inc	rcx
	jmp	loop_strstr
match_pos:
	mov rax, rdi
	add rax, rdx
end:
	ret
