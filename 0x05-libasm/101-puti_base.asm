BITS 64
CPU X64

	;;
	;; asm_puti_base - prints each digit of a signed number in the given base
	;; to STDOUT using the putc routine that prints one char at a time
	;;
	;; Prototype: size_t asm_puti_base(int n, const char *base);
	;; @n: the signed number to be printed
	;; @base: a string representing the base
	;; Return: the number of digits printed
	;;
	;; This version uses the 'loopnz' instructions to decrease 'ecx' register
	;; and check when it reaches zero. This version happens to be a bit slower
	;; then using the 'dec ecx/jnz' instructions pair but I decide to keep
	;; it to document this alternative.
	;;

	global asm_puti_base		; Define symbol to routine of the same name
	extern asm_putc, asm_strlen	; Import function from external file

segment .text
asm_puti_base:			; Implement asm_put_base function/routine
	push rbp		; Routine prologue, create new stack frame
	mov rbp, rsp
	push rdx		; Save registers that will be overriden
	push r8
	push r9
	push rdi		; Save first function argument
	mov rdi, rsi		; Use 2nd argument as the 1st to call strlen
	call asm_strlen		; Call to strlen, measure the length of string
	pop rdi			; Restore 1st argument
	push rax		; Save return value of strlen (length) to the stack
	lea rdx, [rsp]		; Copy a pointer to the length of string (base)
	xor r9d, r9d		; Start/reset our counter to the number of char printed
	mov eax, edi		; Copy 1st arg to check its sign (positive or negative)
	test eax, eax
	js negative		; If negative jump to subroutine...
				; Otherwise continue to 'print' subroutine
print:				; Subroutine to print each digit
	mov ebx, [rdx]		; Copy the length of string to ebx
	xor ecx, ecx		; Start a counter
	not ecx			; Invert ecx bits to count backwards
iloop:	xor edx, edx		; Reset edx to make the division
	div ebx			; Divide the number (in edx:eax) by length of string
	sub rsp, 1		; Reserve one byte on stack to put the remainder
	mov [rsp], dl		; Save the remainder of division (number / length)
	test eax, eax		; Check when we reach zero
	loopnz iloop		; While not zero, decrement ecx and loop
	not ecx			; Invert bits again to get positive number of bytes
pstr:	movzx r8d, BYTE [rsp]	; After we reach zero start copying bytes from stack
	movzx edi, BYTE [rsi + r8] ; in reverse order to be printed
	call asm_putc		   ; Print each digit
	add r9b, al		   ; Transfer the result of call to putc to our counter
	add rsp, 1		   ; Restore each byte from the stack
	loopnz pstr		   ; While not zero, decrement the counter (ecx) and loop
	mov eax, r9d		   ; When zero, copy the acumulator to return value

end:
	add rsp, 8		; Remove 8 bytes from stack (used by rax)
	pop r9			; Restore GPR (General Purpose Registers)
	pop r8
	pop rdx
	mov rsp, rbp		; Routine epilogue, return from stack frame
	pop rbp
	ret

negative:			; Subroutine to deal with negative numbers
	neg eax			; Make positive (flip sign)
	push rax		; Preserve the number on stack
	mov edi, '-'		; Define 1st arg to putc
	call asm_putc		; Call putc to print the minus sign
	add r9b, al		; Add the return value to r9 to be returned later
	pop rax			; Restore the number
	mov edi, eax		; Use the number as 1st argument to next routine
	jmp print		; Jump to 'print' subroutine

