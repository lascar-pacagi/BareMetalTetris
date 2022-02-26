#ifndef __GDT_H__
#define __GDT_H__
#include "types.h"

#define GDTBASE    0x0		/* addr. physique ou doit resider la gdt */
#define GDTSIZE    0xFF		/* nombre max. de descripteurs dans la table */

/* Descripteur de segment */
struct gdtdesc {
	u16 lim0_15;
	u16 base0_15;
	u8 base16_23;
	u8 acces;
	u8 lim16_19:4;
	u8 other:4;
	u8 base24_31;
} __attribute__ ((packed));

/* Registre GDTR */
struct gdtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));

/* extern struct gdtdesc kgdt[]; */
/* extern struct gdtr kgdtr; */

void init_gdt_desc(u32, u32, u8, u8, volatile struct gdtdesc *);
void init_gdt(void);

#endif
