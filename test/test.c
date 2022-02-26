#include "test.h"
#include "keyboard.h"
#include "video.h"
#include "lib.h"
#include "timer.h"
#include "sound.h"

static char* key_to_string[] =
  {
    "", "UP", "LEFT", "RIGHT", "DOWN", "SPACE", "PAUSE", "NEW", "SOUND"
  };

void test_keyboard(void)
{
  static int last_key = KEY_NONE;
  int k = KEY_PRESSED();
  if (k != last_key)
    {
      fill_rect(0, 0, VGA_WIDTH - 1, VGA_HEIGHT - 1, COLOR_BLACK);
      draw_string(130, 100, key_to_string[k], COLOR_WHITE, COLOR_BLACK);
      last_key = k;
    }
}

void test_timer(void)
{
  uint32_t c = __counter;
  draw_string(30, 30, itoa(c), COLOR_WHITE, COLOR_BLACK);
}

void test_sound(void)
{
  mario_theme();
  wait(2000);
  tetris_theme();
}
