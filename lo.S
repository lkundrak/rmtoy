.GLOBAL _panic

.TEXT

; Compiler generates references to these

#ifdef __BCC__

.GLOBAL imodu
imodu:
        xor dx,dx
        div bx
        mov ax,dx
        ret

.GLOBAL idiv_u
idiv_u:
        xor dx,dx
        div bx
        ret

#endif /* __BCC__ */

; Library functions

.GLOBAL _exit
_exit:
	xor ax,ax
	int #0x21
	ret ; what for...


.GLOBAL _putchar
_putchar:
	push bp
	mov bp,sp
	mov dl,4[bp]
	mov ah,#0x02
	int #0x21
	pop bp
	ret

; DOS functions

; Returns zero if last MCB was given,
; the first one if 0 was given, otherwise the
; next allocated MCB,
.GLOBAL _nextmcb
_nextmcb:
	push bp
	mov bp,sp

	; Switch to MCB segment
	push ds
	mov ds,4[bp]

	cmp 4[bp],#0x00
	je firstmcb

	; 'Z' means last
	xor ax,ax
	xor bx,bx
	cmpb [bx],#0x5a
	je returnmcb

	; All other MCBs have 'M'
	cmpb [bx],#0x4d
	jne badmcb

	; paragraph count (sans this MCB)
	mov bx,#0x03
	push ds
	pop ax
	add ax,[bx]
	inc ax

checkmcb:
	; We have this MCB in DS now
	; check if it's allocated, otherwise recurse
	mov ds,ax
	cmp 0x0001,#0x0000
	je nextmcb

returnmcb:
	pop ds
	pop bp
	ret

nextmcb:
	; Pick next MCB and let it be checked
	push ds
	call _nextmcb
	add sp,#2
	jmp checkmcb

firstmcb:
	; Call DOS to determine the first MCB
	mov ah,#0x52
	int #0x21
	; Move ES into DS
	push es
	pop ds
	; Move ES:BX+2 into AX
	sub bx,#0x02
	mov ax,[bx]
	jmp checkmcb

badmcb:
	pop ds
	push #mcberr
	call _panic


.DATA

mcberr:
.ASCII "Invalid MCB"
.BYTE 0

.TEXT

; Get MCB's name given segment address
.GLOBAL _mcbname
_mcbname:
	push bp
	mov bp,sp
	push ds
	pop es
	mov ds,4[bp]
	mov di,6[bp]
	mov si,#0x08
	mov cx,#0x08

nmcopy:
	lodsb
	stosb
	loop nmcopy

	push es
	pop ds
	pop bp
	ret
