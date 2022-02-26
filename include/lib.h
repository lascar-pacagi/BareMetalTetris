#ifndef __LIB_H__
#define __LIB_H__

#include "types.h"

void *memcpy(void *, const void *, unsigned int);
static inline int abs(int x)
{
  return x >= 0 ? x : -x;
}
char *itoa(int i);
void srand();
uint32_t rand(void);

#endif
