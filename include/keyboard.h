#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "types.h"

enum keys { KEY_NONE = 0, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_SPACE, KEY_PAUSE, KEY_NEW, KEY_SOUND };

extern volatile int __key;

#define KEY_PRESSED() __key

void isr_keyboard_int(void);

#endif
