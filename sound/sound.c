#include "sound.h"
#include "io.h"
#include "timer.h"

volatile uint8_t music_on = 0;

void play_sound(uint32_t frequence, uint32_t time)
{
  uint32_t div;
  uint8_t tmp;

  //Set the PIT to the desired frequency
  div = 1193180 / frequence;
  outb(0x43, 0xB6);
  outb(0x42, (uint8_t) div);
  outb(0x42, (uint8_t) (div >> 8));

  //And play the sound using the PC speaker
  tmp = inb(0x61);
  if (tmp != (tmp | 3))
    {
      outb(0x61, tmp | 3);
    }
  wait(time);
  //  no_sound();
}

 //make it shutup
void no_sound()
{
  uint8_t tmp = inb(0x61) & 0xFC;
  outb(0x61, tmp);
}

// Make a beep
void beep(void)
{
  play_sound(1000, 10);
}

struct beep
{
  int16_t frequency;
  uint16_t duration;
};

static const struct beep music[] =
  {
    { .frequency = 784, .duration = 440 },
    { .frequency = 587, .duration = 220 },
    { .frequency = 622, .duration = 220 },
    { .frequency = 698, .duration = 440 },
    { .frequency = 622, .duration = 220 },
    { .frequency = 587, .duration = 220 },
    { .frequency = 523, .duration = 440 },
    { .frequency = 523, .duration = 220 },
    { .frequency = 622, .duration = 220 },
    { .frequency = 784, .duration = 440 },
    { .frequency = 698, .duration = 220 },
    { .frequency = 622, .duration = 220 },
    { .frequency = 587, .duration = 660 },
    { .frequency = 622, .duration = 220 },
    { .frequency = 698, .duration = 440 },
    { .frequency = 784, .duration = 440 },
    { .frequency = 622, .duration = 440 },
    { .frequency = 523, .duration = 440 },
    { .frequency = 523, .duration = 440 },
    { .frequency = -1,  .duration = 660},
    { .frequency = 698, .duration = 440 },
    { .frequency = 831, .duration = 220 },
    { .frequency = 1046,.duration = 440 },
    { .frequency = 932, .duration = 220 },
    { .frequency = 831, .duration = 220 },
    { .frequency = 784, .duration = 660 },
    { .frequency = 622, .duration = 220 },
    { .frequency = 784, .duration = 440 },
    { .frequency = 698, .duration = 220 },
    { .frequency = 622, .duration = 220 },
    { .frequency = 587, .duration = 440 },
    { .frequency = 587, .duration = 220 },
    { .frequency = 622, .duration = 220 },
    { .frequency = 698, .duration = 440 },
    { .frequency = 784, .duration = 440 },
    { .frequency = 622, .duration = 440 },
    { .frequency = 523, .duration = 440 },
    { .frequency = 523, .duration = 440 },
    { .frequency = -1,  .duration = 440 }
  };

void play_music(void)
{
  static uint16_t time = 0;
  static uint16_t index = 0;
  if (time == 0)
    {
      no_sound();
      ++index;
      if (index == sizeof(music) / sizeof(struct beep)) index = 0;
      int16_t f = music[index].frequency;
      time = music[index].duration;
      if (f != -1)
        {
          uint32_t div;
          uint8_t tmp;

          //Set the PIT to the desired frequency
          div = 1193180 / f;
          outb(0x43, 0xB6);
          outb(0x42, (uint8_t) div);
          outb(0x42, (uint8_t) (div >> 8));

          //And play the sound using the PC speaker
          tmp = inb(0x61);
          if (tmp != (tmp | 3))
            {
              outb(0x61, tmp | 3);
            }
        }
      else
        {
          no_sound();
        }
    }
  else
    {
      --time;
    }
}

void tetris_theme(void)
{
  play_sound(784, 440);
  play_sound(587, 220);
  play_sound(622, 220);
  play_sound(698, 440);
  play_sound(622, 220);
  play_sound(587, 220);
  play_sound(523, 440);
  play_sound(523, 220);
  play_sound(622, 220);
  play_sound(784, 440);
  play_sound(698, 220);
  play_sound(622, 220);
  play_sound(587, 660);
  play_sound(622, 220);
  play_sound(698, 440);
  play_sound(784, 440);
  play_sound(622, 440);
  play_sound(523, 440);
  play_sound(523, 440);
  wait(660);
  play_sound(698, 440);
  play_sound(831, 220);
  play_sound(1046, 440);
  play_sound(932, 220);
  play_sound(831, 220);
  play_sound(784, 660);
  play_sound(622, 220);
  play_sound(784, 440);
  play_sound(698, 220);
  play_sound(622, 220);
  play_sound(587, 440);
  play_sound(587, 220);
  play_sound(622, 220);
  play_sound(698, 440);
  play_sound(784, 440);
  play_sound(622, 440);
  play_sound(523, 440);
  play_sound(523, 440);
  wait(440);
}

void mario_theme(void)
{
  play_sound(659, 125);
  play_sound(659, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 167);
  play_sound(523, 125);
  play_sound(659, 125);
  play_sound(32400, 125);
  play_sound(784, 125);
  play_sound(32400, 375);
  play_sound(392, 125);
  play_sound(32400, 375);
  play_sound(523, 125);
  play_sound(32400, 250);
  play_sound(392, 125);
  play_sound(32400, 250);
  play_sound(330, 125);
  play_sound(32400, 250);
  play_sound(440, 125);
  play_sound(32400, 125);
  play_sound(494, 125);
  play_sound(32400, 125);
  play_sound(466, 125);
  play_sound(32400, 42);
  play_sound(440, 125);
  play_sound(32400, 125);
  play_sound(392, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 125);
  play_sound(784, 125);
  play_sound(32400, 125);
  play_sound(880, 125);
  play_sound(32400, 125);
  play_sound(698, 125);
  play_sound(784, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 125);
  play_sound(523, 125);
  play_sound(32400, 125);
  play_sound(587, 125);
  play_sound(494, 125);
  play_sound(32400, 125);
  play_sound(523, 125);
  play_sound(32400, 250);
  play_sound(392, 125);
  play_sound(32400, 250);
  play_sound(330, 125);
  play_sound(32400, 250);
  play_sound(440, 125);
  play_sound(32400, 125);
  play_sound(494, 125);
  play_sound(32400, 125);
  play_sound(466, 125);
  play_sound(32400, 42);
  play_sound(440, 125);
  play_sound(32400, 125);
  play_sound(392, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 125);
  play_sound(784, 125);
  play_sound(32400, 125);
  play_sound(880, 125);
  play_sound(32400, 125);
  play_sound(698, 125);
  play_sound(784, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 125);
  play_sound(523, 125);
  play_sound(32400, 125);
  play_sound(587, 125);
  play_sound(494, 125);
  play_sound(32400, 375);
  play_sound(784, 125);
  play_sound(740, 125);
  play_sound(698, 125);
  play_sound(32400, 42);
  play_sound(622, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 167);
  play_sound(415, 125);
  play_sound(440, 125);
  play_sound(523, 125);
  play_sound(32400, 125);
  play_sound(440, 125);
  play_sound(523, 125);
  play_sound(587, 125);
  play_sound(32400, 250);
  play_sound(784, 125);
  play_sound(740, 125);
  play_sound(698, 125);
  play_sound(32400, 42);
  play_sound(622, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 167);
  play_sound(698, 125);
  play_sound(32400, 125);
  play_sound(698, 125);
  play_sound(698, 125);
  play_sound(32400, 625);
  play_sound(784, 125);
  play_sound(740, 125);
  play_sound(698, 125);
  play_sound(32400, 42);
  play_sound(622, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 167);
  play_sound(415, 125);
  play_sound(440, 125);
  play_sound(523, 125);
  play_sound(32400, 125);
  play_sound(440, 125);
  play_sound(523, 125);
  play_sound(587, 125);
  play_sound(32400, 250);
  play_sound(622, 125);
  play_sound(32400, 250);
  play_sound(587, 125);
  play_sound(32400, 250);
  play_sound(523, 125);
  play_sound(32400, 1125);
  play_sound(784, 125);
  play_sound(740, 125);
  play_sound(698, 125);
  play_sound(32400, 42);
  play_sound(622, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 167);
  play_sound(415, 125);
  play_sound(440, 125);
  play_sound(523, 125);
  play_sound(32400, 125);
  play_sound(440, 125);
  play_sound(523, 125);
  play_sound(587, 125);
  play_sound(32400, 250);
  play_sound(784, 125);
  play_sound(740, 125);
  play_sound(698, 125);
  play_sound(32400, 42);
  play_sound(622, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 167);
  play_sound(698, 125);
  play_sound(32400, 125);
  play_sound(698, 125);
  play_sound(698, 125);
  play_sound(32400, 625);
  play_sound(784, 125);
  play_sound(740, 125);
  play_sound(698, 125);
  play_sound(32400, 42);
  play_sound(622, 125);
  play_sound(32400, 125);
  play_sound(659, 125);
  play_sound(32400, 167);
  play_sound(415, 125);
  play_sound(440, 125);
  play_sound(523, 125);
  play_sound(32400, 125);
  play_sound(440, 125);
  play_sound(523, 125);
  play_sound(587, 125);
  play_sound(32400, 250);
  play_sound(622, 125);
  play_sound(32400, 250);
  play_sound(587, 125);
  play_sound(32400, 250);
  play_sound(523, 125);
}

void impossible_mission_theme(void)
{
  play_sound(784, 150);
  wait(300);
  play_sound(784, 150);
  wait(300);
  play_sound(932, 150);
  wait(150);
  play_sound(1047, 150);
  wait(150);
  play_sound(784, 150);
  wait(300);
  play_sound(784, 150);
  wait(300);
  play_sound(699, 150);
  wait(150);
  play_sound(740, 150);
  wait(150);
  play_sound(784, 150);
  wait(300);
  play_sound(784, 150);
  wait(300);
  play_sound(932, 150);
  wait(150);
  play_sound(1047, 150);
  wait(150);
  play_sound(784, 150);
  wait(300);
  play_sound(784, 150);
  wait(300);
  play_sound(699, 150);
  wait(150);
  play_sound(740, 150);
  wait(150);
  play_sound(932, 150);
  play_sound(784, 150);
  play_sound(587, 1200);
  wait(75);
  play_sound(932, 150);
  play_sound(784, 150);
  play_sound(554, 1200);
  wait(75);
  play_sound(932, 150);
  play_sound(784, 150);
  play_sound(523, 1200);
  wait(150);
  play_sound(466, 150);
  play_sound(523, 150);
}
