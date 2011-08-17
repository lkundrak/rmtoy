#ifdef BIOS

; BIOS putchar
.GLOBAL _putchar
_putchar:
	push bp
	mov bp,sp

	; CRLF conversion
	cmp 4[bp],#0xa
	jne __putchar
	mov ax,#0xd
	push ax
	call _putchar
	add sp,#2
__putchar:

	; BIOS Teletype output
	mov al,4[bp]
	mov ah,#0x0e	; Output character
	int #0x10
	cmp al,#0xa
	pop bp
	ret

; Lame duck exit
.GLOBAL _exit
_exit:
	hlt
	jmp _exit

#endif

; BIOS VGA mode
.GLOBAL _vgamode
_vgamode:
	push bp
	mov bp,sp

	xor ah,ah
	mov al,4[bp]
	int #0x10

	pop bp
	ret
