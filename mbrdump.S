.GLOBAL _main
_main:
	; Stash all the registers
	push sp
	push bp
	push di
	push si

	push cs
	push ss
	push es
	push ds

	push dx
	push cx
	push bx
	push ax

	pushf

	; Begin to print them
	mov si,#0x464c
	call p
	call n

	mov si,#0x4158
	call p
	mov si,#0x4258
	call p
	mov si,#0x4358
	call p
	mov si,#0x4458
	call p
	call n

	mov si,#0x4453
	call p
	mov si,#0x4553
	call p
	mov si,#0x5353
	call p
	mov si,#0x4353
	call p
	call n

	mov si,#0x5349
	call p
	mov si,#0x4449
	call p
	mov si,#0x4250
	call p
	mov si,#0x5350
	call p
	call n

; Loop indefinitely
lp:
	hlt
	jmp lp

; Print a register name given in SI,
; followed by value popped from stack
p:
	pop bp
	call prs
	pop si
	call prn
	push bp
	ret

; Line break
n:
	mov ah,#0x0e
	mov al,#0xd
	int #0x10
	mov al,#0xa
	int #0x10
	ret

; Print a 16 bit number given SI (in hex)
prn:
	; Most significant digit
	mov ax,si
	mov cl,#0xc
	call outn
	; Second digit
	mov ax,si
	mov cl,#0x8
	call outn
	; Third digit
	mov ax,si
	mov cl,#0x4
	call outn
	; Last digit
	mov ax,si
	xor cl,cl
	call outn
	; A space
	mov al,#0x20
	int #0x10
	ret
	
; Print a single hex digit of number given in AX,
; with shift given in CL
outn:
	shr ax,cl
	and al,#0x0f
	cmp al,#0x0a
	jl o
	add al,#0x7
o:	add al,#0x30
	mov ah,#0x0e	; Output character
	int #0x10
	ret

; Print two letters given in SI, followed
; by a colon and space
prs:
	; First letter
	mov ax,si
	mov al,ah
	mov ah,#0x0e
	int #0x10
	; Second letter
	mov ax,si
	mov ah,#0x0e
	int #0x10
	; Colon
	mov al,#0x3a
	int #0x10
	; Space
	mov al,#0x20
	int #0x10
	ret

; PC boot signature
org 0x1fe
.word 0xaa55
