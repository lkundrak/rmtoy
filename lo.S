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

.GLOBAL _draw
_draw:
	push ds
	mov bx,#0xa000
	push bx
	pop ds
	mov cx,#0xffff
__draw:
	mov di,cx
	mov [di],cx
	sub cx,#5
	jmp __draw

	pop ds
	ret

.GLOBAL _stick
_stick:
	push bp
	mov bp,sp
	xor si,si	; X counter
	xor di,di	; Y counter
	xor ax,ax	; port value to return
	mov dx,#0x201	; joystick port
	outb dx,al	; trigger the timer
__stick:
	inb al,dx
	test al,#0x01
	jz nox
	inc si
nox:
	test al,#0x02
	jz noy
	inc di
noy:
	test al,#0x03
	jnz __stick
	mov bx,4[bp]	; store the counters
	mov [bx],si
	mov bx,6[bp]
	mov [bx],di
	pop bp
	ret

.GLOBAL _clear
_clear:
	push ds
	mov bx,#0xb800
	push bx
	pop ds

	mov bx,#00
__clear:
	mov [bx],#0x0f00
	add bx,#2
	cmp bx,#4000
	jng __clear

	pop ds
	ret

.GLOBAL _bar
_bar:
	push bp
	mov bp,sp
	mov di,4[bp]
	mov bx,6[bp]
	mov cx,8[bp]
	mov dx,10[bp]

	push ds
	mov ax,#0xb800
	push ax
	pop ds

	mov ax,#80
	mul bl
	add ax,di
	add ax,ax
	mov bx,ax
__bar:
	movb [bx],dl
	add bx,#2
	movb [bx],dl
	add bx,#158

	loop __bar

	pop ds
	pop bp
	ret
