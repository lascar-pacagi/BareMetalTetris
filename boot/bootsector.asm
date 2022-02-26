%define BASE  0x100
%define KSIZE 50

[BITS 16]
[ORG 0x7C00]

jmp start

;---------------------------------------------------------------------
; Synopsis:	Affiche une chaine de caracteres se terminant par 0x0
; Entree:	ds:si -> pointe sur la chaine a afficher
;---------------------------------------------------------------------
afficher:
	push ax
    mov ah,0x0E	; appel au service 0x0e, int 0x10 du bios
    cld
.debut:
	lodsb		; ds:si -> al
	cmp al,0	; fin chaine ?
	jz .fin	
	int 0x10
    jmp .debut

.fin:
	pop ax
	ret

;--------------------------------------------------------------------
; CalcAdr
; Entree:
;    ax -> segment
;    bx -> offset
; Sortie:
;    ecx -> adresse lineaire sur 32 bits
; Modifie: partie haute de ebx
;--------------------------------------------------------------------
calcadr:
    xor ecx, ecx
    mov cx, ax
    shl ecx, 4
    and ebx, 0x0000FFFF
    add ecx, ebx
    ret
;--------------------------------------------------------------------


;--------------------------------------------------------------------
; descInit
;--------------------------------------------------------------------
%macro descInit    5    ; base(32), limite(20/32), acces(8), flags(4/8), adresse(32)
    push eax
; base :
    mov eax, %1
    mov word [%5+2], ax
    shr eax, 16
    mov byte [%5+4], al
    shr eax, 8
    mov byte [%5+7], al
; limite :
    mov eax, %2
    and eax, 0x000FFFFF
    mov word [%5], ax  ; ecrit (0..15)
    shr eax, 16        ; place (16..19) sur le nibble inferieur
    mov byte [%5+6], 0 ; initialise flags+lim(16..19) a 0
    or  [%5+6], al     ; ecrit (16..19)
; flags :
    mov al, %4
    and al, 0x0F
    shl al, 4
    or [%5+6], al
; acces :
    mov byte [%5+5], %3
    pop eax
%endmacro
;--------------------------------------------------------------------

start:
    mov si, msgDebut
    call afficher

; initialisation des segments en 0x07C0
    mov ax, 0x07C0
    mov ds, ax
    mov es, ax
    mov ax, 0x8000
    mov ss, ax
    mov sp, 0xf000

; recuparation de l'unite de boot
    mov [bootdrv], dl    

; charger le noyau
    xor ax, ax
    int 0x13

    push es
    mov ax, BASE
    mov es, ax
    mov bx, 0
    
    mov ah, 2
    mov al, KSIZE
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [bootdrv]
    int 0x13
    pop es


; initialisation de la GDT
    ; descInit base(32), limite(20/32), acces/type(8), flags(4/8), adresse(16)
    descInit 0, 0xFFFFF, 10011011b, 1101b, gdt_cs
    descInit 0, 0xFFFFF, 10010011b, 1101b, gdt_ds

; initialisation du pointeur sur la GDT
    mov ax, gdtend    ; calcule la limite de GDT
    mov bx, gdt
    sub ax, bx
    mov word [gdtptr], ax

    xor eax, eax    ; calcule l'adresse lineaire de GDT
    mov  ax, ds
    mov  bx, gdt
    call calcadr
    mov dword [gdtptr+2], ecx

    mov ax, 0x13
    int 0x10
	
; passage en modep
    cli
    lgdt [gdtptr]    ; charge la gdt
    mov eax, cr0
    or  ax, 1
    mov cr0, eax    ; PE mis a 1 (CR0)

    mov ax, 0x10    ; segment de donne
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x9F000    
	
    jmp dword 0x8:0x1000

    jmp $


;--------------------------------------------------------------------
msgDebut db "Loading kernel", 13, 10, 0

gdt:
gdt_null:
    dw 0, 0, 0, 0
gdt_cs:
    dw 0, 0, 0, 0
gdt_ds:
    dw 0, 0, 0, 0
gdtend:

gdtptr:
    dw    0x0000    ; limite
    dd    0         ; base

bootdrv db 0

;--------------------------------------------------------------------
;; NOP jusqu'a 510
times 510-($-$$) db 144
dw 0xAA55
