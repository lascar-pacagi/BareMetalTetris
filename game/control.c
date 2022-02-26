#include "control.h"
#include "view.h"
#include "lib.h"
#include "timer.h"
#include "board.h"
#include "sound.h"
#include "keyboard.h"

static struct board board;
static volatile bool pause = false;
static volatile bool just_fallen = true;

void tetris_loop()
{
  srand(second());
  init_board(&board);
  while (1)
    {
      view_board(&board);
      if (!pause) move_current_piece_down(&board);
      if (!is_game_over(&board))
        {
          if (is_current_piece_fallen(&board))
            {
              if (just_fallen) just_fallen = false;
              else
                {
                  int nb_lines = delete_possible_lines(&board);
                  add_to_lines(&board, nb_lines);
                  add_to_score(&board, nb_lines * nb_lines * (get_level(&board) + 1) * 10);
                  set_level(&board, get_lines(&board) / 10);
                  set_current_piece(&board, board.next_piece);
                  random_piece(get_next_piece(&board), PIECE_I, PIECE_J);
                  draw_piece(&board, get_current_piece(&board));
                  view_board(&board);
                  just_fallen = true;
                }
            }
        }
      wait(300 - get_level(&board) * 20);      
    }
}

void key_typed(int key)
{
  switch (key)
    {
    case KEY_LEFT:
      if (!pause) move_current_piece_left(&board);
      break;
    case KEY_RIGHT:
      if (!pause) move_current_piece_right(&board);
      break;
    case KEY_UP:
      if (!pause) rotate_current_piece_right(&board);
      break;
    case KEY_DOWN:
      if (!pause) move_current_piece_down(&board);
      break;
    case KEY_SPACE:
      if (!pause)
        {
          drop_current_piece(&board);
          just_fallen = false;
        }
      break;
    case KEY_SOUND:
      music_on = 1 - music_on;
      break;
    case KEY_NEW:
      init_board(&board);
      pause = false;
      break;
    case KEY_PAUSE:
      pause = 1 - pause;
      break;
    }
  view_board(&board);
}
