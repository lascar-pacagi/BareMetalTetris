#include "keyboard.h"
#include "video.h"
#include "io.h"
#include "sound.h"
#include "control.h"

#define INIT 0
#define WAIT_FOR_CURSOR 1

volatile int __key = KEY_NONE;

void isr_keyboard_int(void)
{
  static int state = INIT;
  u8 scan_code;
  scan_code = inb(0x60);
  if (scan_code == 0xE0)
    {
      state = WAIT_FOR_CURSOR;      
      return;
    }
  if (state == WAIT_FOR_CURSOR)
    {
      switch (scan_code)
	      {
          case 0x48: __key = KEY_UP; break;
          case 0x4B: __key = KEY_LEFT; break;
          case 0x4D: __key = KEY_RIGHT; break;
          case 0x50: __key = KEY_DOWN; break;
          default: __key = KEY_NONE; break;
        }
    }
  else
    {
      switch (scan_code)
        {
          case 0x18: __key = KEY_SOUND; break;
          case 0x19: __key = KEY_PAUSE; break;
          case 0x31: __key = KEY_NEW; break;
          case 0x39: __key = KEY_SPACE; break;
          default: __key = KEY_NONE; break;
        }
    }
  if (__key != KEY_NONE) key_typed(__key);
  state = INIT;
}
