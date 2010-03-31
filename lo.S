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

.GLOBAL _mcb0
_mcb0:
	mov ah,#0x52
	int #0x21
	push ds
	; Move ES into DS
	push es
	pop ds
	; Move ES:BX+2 into AX
	sub bx,#0x02
	mov ax,[bx]
	; Return
	pop ds
	ret

.GLOBAL _nextmcb
_nextmcb:
	push bp
	mov bp,sp

	; Switch to MCB segment
	push ds
	mov ds,4[bp]

	; 'Z' means last
	xor ax,ax
	xor bx,bx
	cmpb [bx],#0x5a
	je lastmcb

	; All other MCBs have 'M'
	cmpb [bx],#0x4d
	jne badmcb

	; paragraph count (sans this MCB)
	mov bx,#0x03
	push ds
	pop ax
	add ax,[bx]
	inc ax

lastmcb:
	pop ds
	pop bp
	ret

badmcb:
	pop ds
	push #mcberr
	call _panic

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

.DATA

mcberr:
.ASCII "Invalid MCB"
.BYTE 0
