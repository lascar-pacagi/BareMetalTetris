#ifndef __IDT_H__
#define __IDT_H__

#include "types.h"

#define IDTBASE  0x800		/* addr. physique ou doit resider la IDT */
#define IDTSIZE  0xFF		/* nombre max. de descripteurs dans la table */

#define INTGATE  0x8E00		/* utilise pour gerer les interruptions */

/* Descripteur de segment */
struct idtdesc {
	u16 offset0_15;
	u16 select;
	u16 type;
	u16 offset16_31;
} __attribute__ ((packed));

/* Registre IDTR */
struct idtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));

volatile struct idtr kidtr; /* Registre IDTR */
volatile struct idtdesc kidt[IDTSIZE]; /* Table IDT */

void init_idt_desc(u16, u32, u16, volatile struct idtdesc *);
void init_idt(void);

#endif
