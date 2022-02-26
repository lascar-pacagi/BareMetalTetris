#include "view.h"
#include "shapes.h"
#include "lib.h"

#define TOP_LEFT_X 100
#define TOP_LEFT_Y 10
#define SQUARE_SIZE 9
#define BOARD_HORIZONTAL_SIZE BOARD_WIDTH * SQUARE_SIZE
#define BOARD_VERTICAL_SIZE BOARD_HEIGHT * SQUARE_SIZE
#define GAME_OVER_X 1
#define GAME_OVER_Y 1
#define TETRIS_BOARD_COLOR COLOR_LIGHT_GREY
#define TETRIS_BACKGROUND_COLOR COLOR_BLACK
#define TETRIS_LINE_COLOR COLOR_BLACK
#define TETRIS_BORDER_COLOR COLOR_WHITE
#define TETRIS_TITLE_BACKGROUND_COLOR COLOR_BLACK
#define TETRIS_TITLE_FOREGROUND_COLOR COLOR_BROWN
#define TETRIS_TEXT_BACKGROUND_COLOR COLOR_LIGHT_GREY
#define TETRIS_TEXT_FOREGROUND_COLOR COLOR_BLACK
#define TETRIS_BOX_COLOR COLOR_LIGHT_GREY
#define TETRIS_GAME_OVER_FOREGROUND_COLOR COLOR_RED
#define TETRIS_GAME_OVER_BACKGROUND_COLOR COLOR_BLACK
#define NEXT_PIECE 0
#define SCORE 1
#define LEVEL 2
#define LINES 3

struct info
{
  uint16_t title_x;
  uint16_t title_y;
  char *title;
  uint16_t box_x;
  uint16_t box_y;
  uint16_t width;
  uint16_t height;
  uint16_t text_x;
  uint16_t text_y;
};

 static const struct info infos[] =
  {
    {
      .title_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE + 3, 
      .title_y = TOP_LEFT_Y + SQUARE_SIZE,
      .title = "^3xt",
      .box_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE, 
      .box_y = TOP_LEFT_Y + SQUARE_SIZE + 10,
      .width = 4 * SQUARE_SIZE, 
      .height = 4 * SQUARE_SIZE,
      .text_x = 0, .text_y = 0
    },
    {
      .title_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE + 3, 
      .title_y = TOP_LEFT_Y + SQUARE_SIZE + 7 * SQUARE_SIZE,
      .title = "$c0r3",
      .box_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE, 
      .box_y = TOP_LEFT_Y + SQUARE_SIZE + 7 * SQUARE_SIZE + 10,
      .width = 7 * SQUARE_SIZE, 
      .height = 2 * SQUARE_SIZE,
      .text_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE + 3, 
      .text_y = TOP_LEFT_Y + SQUARE_SIZE + 7 * SQUARE_SIZE + 15
    },
    {
      .title_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE + 3, 
      .title_y = TOP_LEFT_Y + SQUARE_SIZE + 11 * SQUARE_SIZE,
      .title = "13\\/31",
      .box_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE, 
      .box_y = TOP_LEFT_Y + SQUARE_SIZE + 11 * SQUARE_SIZE + 10,
      .width = 7 * SQUARE_SIZE, 
      .height = 2 * SQUARE_SIZE,
      .text_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE + 3, 
      .text_y = TOP_LEFT_Y + SQUARE_SIZE + 11 * SQUARE_SIZE + 15
    },
    {
      .title_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE + 3, 
      .title_y = TOP_LEFT_Y + SQUARE_SIZE + 15 * SQUARE_SIZE,
      .title = "1i^3$",
      .box_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE, 
      .box_y = TOP_LEFT_Y + SQUARE_SIZE + 15 * SQUARE_SIZE + 10,
      .width = 7 * SQUARE_SIZE, .height = 2 * SQUARE_SIZE,
      .text_x = TOP_LEFT_X + BOARD_HORIZONTAL_SIZE + SQUARE_SIZE + 3, 
      .text_y = TOP_LEFT_Y + SQUARE_SIZE + 15 * SQUARE_SIZE + 15
    }
  };

static void view_infos(struct board *b)
{
  const struct info *info;
  for (int i = 0; i < sizeof(infos) / sizeof(struct info); ++i)
    {
      info = &infos[i];
      draw_string_to_buffer(info->title_x, info->title_y, info->title, TETRIS_TITLE_FOREGROUND_COLOR, TETRIS_TITLE_BACKGROUND_COLOR);
      fill_rect_to_buffer(info->box_x, info->box_y, info->width, info->height, TETRIS_BOX_COLOR);
      draw_rect_to_buffer(info->box_x - 1, info->box_y - 1, info->width + 2, info->height + 2, TETRIS_BORDER_COLOR);
    }
  struct piece *next_piece = get_next_piece(b);
  if (next_piece != NULL)
    {
      uint8_t color = get_color(next_piece);
      info = &infos[NEXT_PIECE];
      for (int i = 0; i < SIZE; ++i)
        {
          for (int j = 0; j < SIZE; ++j)
            {
              int v = get_shape_value(next_piece, i, j);
              if (v != 0)
                fill_rect_to_buffer(info->box_x + j * SQUARE_SIZE, info->box_y + i * SQUARE_SIZE,
                                    SQUARE_SIZE, SQUARE_SIZE, color);
            }
        }
    }
  info = &infos[SCORE];
  draw_string_to_buffer(info->text_x, info->text_y, itoa(get_score(b)), TETRIS_TEXT_FOREGROUND_COLOR, TETRIS_TEXT_BACKGROUND_COLOR);
  info = &infos[LEVEL];
  draw_string_to_buffer(info->text_x, info->text_y, itoa(get_level(b)), TETRIS_TEXT_FOREGROUND_COLOR, TETRIS_TEXT_BACKGROUND_COLOR);
  info = &infos[LINES];
  draw_string_to_buffer(info->text_x, info->text_y, itoa(get_lines(b)), TETRIS_TEXT_FOREGROUND_COLOR, TETRIS_TEXT_BACKGROUND_COLOR);
}

void view_board(struct board *b)
{
  fill_rect_to_buffer(0, 0, VGA_WIDTH, VGA_HEIGHT, TETRIS_BACKGROUND_COLOR);
  fill_rect_to_buffer(TOP_LEFT_X, TOP_LEFT_Y,
                      BOARD_HORIZONTAL_SIZE,
                      BOARD_VERTICAL_SIZE,
                      TETRIS_BOARD_COLOR);
  for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
      for (int j = 0; j < BOARD_WIDTH; ++j)
        {
          draw_rect_to_buffer(TOP_LEFT_X + j * SQUARE_SIZE, TOP_LEFT_Y + i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, TETRIS_LINE_COLOR);
        }
    }
  draw_rect_to_buffer(TOP_LEFT_X - 1, TOP_LEFT_Y - 1,
                      2 * BOARD_HORIZONTAL_SIZE, BOARD_VERTICAL_SIZE + 2,
                      TETRIS_BORDER_COLOR);
  draw_line_to_buffer(TOP_LEFT_X + BOARD_HORIZONTAL_SIZE, TOP_LEFT_Y,
                      TOP_LEFT_X + BOARD_HORIZONTAL_SIZE, TOP_LEFT_Y + BOARD_VERTICAL_SIZE,
                      TETRIS_BORDER_COLOR);
  view_infos(b);

  for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
      for (int j = 0; j < BOARD_WIDTH; ++j)
        {
          if (b->area[i][j] != FREE)
            fill_rect_to_buffer(TOP_LEFT_X + j * SQUARE_SIZE, TOP_LEFT_Y + i * SQUARE_SIZE,
                                SQUARE_SIZE, SQUARE_SIZE, b->area[i][j]);
        }
    }
  if (get_game_over(b))
    {
      draw_string_to_buffer(GAME_OVER_X, GAME_OVER_Y,
                            "+--------------------------------------+\n"
                            "|                                      |\n"
                            "|         __|    \\     \\  |  __|       |\n"
                            "|        (_ |   _ \\   |\\/ |  _|        |\n"
                            "|       \\___| _/  _\\ _|  _| ___|       |\n"
                            "|                                      |\n"
                            "|         _ \\ \\ \\   / __|  _ \\         |\n"
                            "|        (   | \\ \\ /  _|     /         |\n"
                            "|       \\___/   \\_/  ___| _|_\\         |\n"
                            "|                                      |\n"
                            "+--------------------------------------+\n",
                            TETRIS_GAME_OVER_FOREGROUND_COLOR, TETRIS_GAME_OVER_BACKGROUND_COLOR);
    }
  copy_buffer_to_vga_memory();
}
