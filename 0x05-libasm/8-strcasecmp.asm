GLOBAL asm_strcasecmp
asm_strcasecmp:
        xor     r8d, r8d	; zero counter
        jmp     .NEXT		; start loop at counter=0
.COMPARE:
        jecxz	.RETURN		; return if char1 == '\0'
        inc	r8
.NEXT:
        movzx	ecx, BYTE [rdi+r8]	; read next char string 1
        movzx	edx, BYTE [rsi+r8]	; read next char string 2
        lea	r9d, [rcx-'A']		; lower bound of char1 from uppercase range
        lea	eax, [rcx+'a'-'A']	; get possible lowercase for char1
        cmp	r9b, 'Z'-'A'		; if char1 was uppercase...
        cmovbe	ecx, eax		; ...set char1 to lowercase
        lea	r9d, [rdx-'A']		; same for char2
        lea	eax, [rdx+'a'-'A']	; ...
        cmp	r9b, 'Z'-'A'		; ...
        cmovbe	edx, eax		; ...
        movzx	eax, cl		; store char1
        movzx	edx, dl		; store char2
        sub	eax, edx	; store diff as return value
        je	.COMPARE
.RETURN:
        ret
