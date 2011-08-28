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

