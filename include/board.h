#ifndef __BOARD_H__
#define __BOARD_H__

#include "piece.h"
#include "shapes.h"

#define FREE -1
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define PIECE_I -1
#define PIECE_J 3

struct board
{
  struct piece current_piece;
  struct piece next_piece;
  int area[BOARD_HEIGHT][BOARD_WIDTH];
  uint score;
  uint level;
  uint lines;
  bool game_over;
};

void init_board(struct board *b);
void set_current_piece(struct board *b, struct piece p);
struct piece * get_current_piece(struct board *b);
void set_next_piece(struct board *b, struct piece p);
struct piece * get_next_piece(struct board *b);
bool collision(struct board *b, int i, int j, int kind, int orientation);
void fill(struct board *b, int i, int j, int kind, int orientation, int color);
void draw_piece(struct board *b, struct piece *p);
void clear_piece(struct board *b, struct piece *p);
void clear(struct board *b);
bool is_current_piece_movable(struct board *b, int i, int j);
bool is_current_piece_rotable(struct board *b, int o);
void move_current_piece_down(struct board *b);
void move_current_piece_left(struct board *b);
void move_current_piece_right(struct board *b);
void rotate_current_piece_left(struct board *b);
void rotate_current_piece_right(struct board *b);
void delete_line(struct board *b, int y);
int delete_possible_lines(struct board *b);
void drop_current_piece(struct board *b);
bool is_current_piece_fallen(struct board *b);
bool is_game_over(struct board *b);
uint get_score(struct board *b);
uint get_level(struct board *b);
uint get_lines(struct board *b);
void add_to_score(struct board *b, uint score);
void set_level(struct board *b, uint level);
void add_to_lines(struct board *b, uint lines);
bool get_game_over(struct board *b);

#endif
