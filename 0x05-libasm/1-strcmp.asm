GLOBAL asm_strcmp
asm_strcmp:
        xor     ecx, ecx		; zero the rcx register
.LOOP:
        movzx   eax, BYTE [rdi + rcx]	; read next char from s1
        movzx   edx, BYTE [rsi + rcx]	; read next char from s2
        test    eax, eax		; check not at end of s1
        je      .EXIT
        inc     rcx			; advance pointers
        cmp     al, dl			; check chars still equal
        je      .LOOP
.EXIT:
        sub     eax, edx		; get diff of last chars read
        mov     ecx, eax		; store diff in ecx register
        sar     ecx, 31			; set ecx to sign bit (-1 or 0)
        test    eax, eax		; set SF & ZF flag registers
        mov     eax, 1			; return 1 unless
        cmovle  eax, ecx		; (ZF==1 || SF!=0) ? ecx : 1
        ret