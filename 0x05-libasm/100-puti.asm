BITS 64
CPU X64

	;;
	;; asm_puti - print each digit of a signed base 10 number to STDOUT using
	;; asm_putc routine (defined in the 100-putc.asm file)
	;;
	;; Prototype: size_t asm_puti(int n);
	;; @n: the base 10 number to be printed
	;;

segment .text
	global asm_puti		; Define and export asm_puti symbol
	extern asm_putc		; Import the asm_putc function/routine

asm_puti:			; Implement the asm_puti function/routine
	push rbp		; Routine prologue, create new stack frame
	mov rbp, rsp
	push rbx		; Save registers to be used
	push rcx
	push rdx
	push r8
	xor r8d, r8d		; Reset 32 bits version of r9 register, our accumulator
	mov eax, edi		; Copy 1st arg (number) to eax
	test eax, eax		; Check the number sign
	js negative		; If negative jump to subroutine
num2str:			; Subroutine to convert number to string
	mov ebx, 10		; Copy the divisor to ebx
	xor ecx, ecx		; Start a counter
pushd:	xor edx, edx		; Zero edx register used in the division
	div ebx			; Divide the number (in eax) by 10
	sub rsp, 1		; Reserve on byte on stack
	mov [rsp], dl		; Save the remainder of the division to this byte
	inc cx			; Increment the counter
	test eax, eax		; Check when it reach zero
	jnz pushd		; While not zero, loop
print:	movzx edi, BYTE [rsp]	; Start retrieving each byte from stack, reverse order
	or dil, 0x30		; Add 48 to each digit to convert it to an ASCII character
	call asm_putc		; Call the routine to print each digit
	add r8b, al		; Add the return value of function call to the accumulator
	add rsp, 1		; Remove each byte from stack
	dec cx			; Decrease the counter
	test cx, cx		; Check when it reach zero
	jnz print		; While not zero, loop
	mov eax, r8d		; Transfer the accumulator to eax (return value)
end:
	pop r8			; Restore registers
	pop rdx
	pop rcx
	pop rbx
	mov rsp, rbp		; Routine epilogue, take down the stack frame
	pop rbp
	ret

negative:			; Subroutine to deal with negative numbers
	neg eax			; Flip sign
	push rax		; Save the number to the stack
	mov edi, '-'		; Prepare 1st function argument
	call asm_putc		; Call putc to print the minus sign
	add r8b, al		; Add the return value to the accumulator
	pop rax			; Retrieve the number from stack
	mov edi, eax		; Copy it to edi (1st argument to func call)
	jmp num2str		; Jump to num2str subroutine
