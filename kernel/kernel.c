#include "idt.h"
#include "gdt.h"
#include "video.h"
#include "io.h"
#include "test.h"
#include "timer.h"
#include "sound.h"
#include "keyboard.h"
#include "control.h"

void init_pic(void);

void _start(void)
{
  init_gdt();
  /* Initialisation du pointeur de pile %esp */
  asm volatile ("movw $0x18, %ax\n\t"
                "movw %ax, %ss\n\t"
                "movl $0x20000, %esp\n\t");
  init_idt();
  init_pic();
  init_timer();

  sti;
  tetris_loop();
}
