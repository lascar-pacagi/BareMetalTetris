#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "types.h"
#include "lib.h"

enum vga_color
{
  COLOR_BLACK = 0,
  COLOR_BLUE = 1,
  COLOR_GREEN = 2,
  COLOR_CYAN = 3,
  COLOR_RED = 4,
  COLOR_MAGENTA = 5,
  COLOR_BROWN = 6,
  COLOR_LIGHT_GREY = 26,
  COLOR_DARK_GREY = 8,
  COLOR_LIGHT_BLUE = 9,
  COLOR_LIGHT_GREEN = 10,
  COLOR_LIGHT_CYAN = 11,
  COLOR_LIGHT_RED = 12,
  COLOR_LIGHT_MAGENTA = 13,
  COLOR_YELLOW = 14,
  COLOR_WHITE = 15,
};

#define VGA_WIDTH 320
#define VGA_HEIGHT 200

static volatile uint8_t* const VGA_MEMORY = (uint8_t*) 0x0A0000;
extern uint8_t video_buffer[VGA_WIDTH * VGA_HEIGHT];

void draw_pixel_to_dst(volatile uint8_t * dst, int x, int y, u8 color);
void draw_line_to_dst(volatile uint8_t * dst, int x0, int y0, int x1, int y1, u8 color);
void draw_rect_to_dst(volatile uint8_t * dst, int x, int y, int w, int h, u8 color);
void fill_rect_to_dst(volatile uint8_t * dst, int x, int y, int w, int h, u8 color);
void draw_char_to_dst(volatile uint8_t * dst, int x, int y, char c, u8 foreground, u8 background);
void draw_string_to_dst(volatile uint8_t * dst, int x, int y, char *s, u8 foreground, u8 background);

void draw_pixel(int x, int y, u8 color);
void draw_line(int x0, int y0, int x1, int y1, u8 color);
void draw_rect(int x, int y, int w, int h, u8 color);
void fill_rect(int x, int y, int w, int h, u8 color);
void draw_char(int x, int y, char c, u8 foreground, u8 background);
void draw_string(int x, int y, char *s, u8 foreground, u8 background);

void draw_pixel_to_buffer(int x, int y, u8 color);
void draw_line_to_buffer(int x0, int y0, int x1, int y1, u8 color);
void draw_rect_to_buffer(int x, int y, int w, int h, u8 color);
void fill_rect_to_buffer(int x, int y, int w, int h, u8 color);
void draw_char_to_buffer(int x, int y, char c, u8 foreground, u8 background);
void draw_string_to_buffer(int x, int y, char *s, u8 foreground, u8 background);

void copy_buffer_to_vga_memory();

#endif
