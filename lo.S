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
