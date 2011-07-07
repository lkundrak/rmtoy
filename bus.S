.GLOBAL _outb
_outb:
	push bp
	mov bp,sp
	mov dx,4[bp]
	mov al,6[bp]
	out dx,al
	pop bp
	ret

.GLOBAL _inb
_inb:
	push bp
	mov bp,sp
	mov dx,4[bp]
	mov al,6[bp]
	xor ax,ax
	in al,dx
	pop bp
        ret
