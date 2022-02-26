extern isr_default_int, isr_clock_int, isr_keyboard_int
global _asm_default_int, _asm_irq_0, _asm_irq_1

_asm_default_int:
        pushad
        call isr_default_int
        mov al, 0x20
        out 0x20, al
        popad
        iret

_asm_irq_0:
        pushad
        call isr_clock_int
        mov al, 0x20
        out 0x20, al
        popad
        iret

_asm_irq_1:
        pushad
        call isr_keyboard_int
        mov al, 0x20
        out 0x20, al
        popad
        iret
