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
.GLOBAL _firstmcb
_firstmcb:
	push ds

	; Call DOS to determine the first MCB
	mov ah,#0x52
	int #0x21

	; Move ES into DS
	push es
	pop ds

	; Move ES:BX+2 into AX
	sub bx,#0x02
	mov ax,[bx]

	pop ds
	ret

; Get MCB's name given segment address
.GLOBAL _getmcb
_getmcb:
	push bp
	mov bp,sp
	push ds
	pop es
	mov ds,4[bp]
	mov di,6[bp]

	; 'Z' means last
	mov ax,#0x0001
	xor bx,bx
	cmpb [bx],#0x5a
	je last
	mov ax,#0x0000

#ifdef DEBUG
	; All other MCBs have 'M'
	cmpb [bx],#0x4d
	jne badmcb
#endif /* DEBUG */

last:
	; Set the last flag in output struct
	stosw

	; PID
	mov si,#0x01
	mov cx,#0x02
pidcopy:
	lodsb
	stosb
	loop pidcopy

	; Length
	mov si,#0x03
	mov cx,#0x02
lencopy:
	lodsb
	stosb
	loop lencopy

	; Name
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

#ifdef DEBUG

badmcb:
	push es
	pop ds
	push #mcberr
	call _panic

.DATA

mcberr:
.ASCII "Invalid MCB"
.BYTE 0

.TEXT

#endif /* DEBUG */
