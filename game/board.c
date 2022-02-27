#include "board.h"
#include "video.h"

void init_board(struct board *b)
{
  for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
      for (int j = 0; j < BOARD_WIDTH; ++j)
	      {
	        b->area[i][j] = FREE;
	      }
    }
  random_piece(&b->current_piece, PIECE_I, PIECE_J);
  random_piece(&b->next_piece, PIECE_I, PIECE_J);
  b->score = 0;
  b->level = 0;
  b->lines = 0;
  b->game_over = false;
  draw_piece(b, &b->current_piece);
}

void set_current_piece(struct board *b, struct piece p)
{
  b->current_piece = p;
}

struct piece * get_current_piece(struct board *b)
{
  return &b->current_piece;
}

void set_next_piece(struct board *b, struct piece p)
{
  b->next_piece = p;
}

struct piece * get_next_piece(struct board *b)
{
  return &b->next_piece;
}

bool collision(struct board *b, int y, int x, int kind, int orientation)
{
  for (int i = 0; i < SIZE; ++i)
    {
      for (int j = 0; j < SIZE; ++j)
	      {
	        if (PIECES[kind][orientation][i][j] != 0 &&
	              (y + i < 0 || y + i >= BOARD_HEIGHT || x + j < 0 || x + j >= BOARD_WIDTH || b->area[y + i][x + j] != FREE))
	          {
	            return true;
	          }
	      }
    }
  return false;
}

void fill(struct board *b, int y, int x, int kind, int orientation, int color)
{
  for (int i = 0; i < SIZE; ++i)
    {
      for (int j = 0; j < SIZE; ++j)
	      {
	        if (PIECES[kind][orientation][i][j] != 0)
	          {
	            b->area[y + i][x + j] = color;
	          }
	      }
    }  
}

void draw_piece(struct board *b, struct piece *p)
{
  fill(b, get_row(p), get_column(p), get_kind(p), get_orientation(p), get_color(p));
}

void clear_piece(struct board *b, struct piece *p)
{
  int i = get_row(p);
  int j = get_column(p);
  
  int k = get_kind(p);
  int o = get_orientation(p);
  
  fill(b, i, j, k, o, FREE);
}

void clear(struct board *b)
{
  for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
      for (int j = 0; j < BOARD_WIDTH; ++j)
	    {
	      b->area[i][j] = FREE;
	    }
    }
}

bool is_current_piece_movable(struct board *b, int i, int j)
{
  struct piece * current_piece = get_current_piece(b);
  clear_piece(b, current_piece);  
  int k = get_kind(current_piece);
  int o = get_orientation(current_piece);
  bool movable = !collision(b, i, j, k, o);
  draw_piece(b, current_piece);
  return movable;
}

bool is_current_piece_rotable(struct board *b, int orientation)
{
  struct piece * current_piece = get_current_piece(b);
  clear_piece(b, current_piece);
  int k = get_kind(current_piece); 
  bool rotable = !collision(b, get_row(current_piece), get_column(current_piece), k, orientation);
  draw_piece(b, current_piece);
  return rotable;
}

enum { MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN };
enum { ROTATE_LEFT, ROTATE_RIGHT };

static void move_current_piece(struct board *b, int dir)
{
  struct piece * current_piece = get_current_piece(b);
  int i = get_row(current_piece);
  int j = get_column(current_piece);

  if (dir == MOVE_LEFT) --j;
  else if (dir == MOVE_RIGHT) ++j;
  else ++i;
  
  if (is_current_piece_movable(b, i, j))
    {
      clear_piece(b, current_piece);
      set_row(current_piece, i);
      set_column(current_piece, j);
      draw_piece(b, current_piece);
    }
}

void move_current_piece_down(struct board *b)
{
  move_current_piece(b, MOVE_DOWN);
}

void move_current_piece_left(struct board *b)
{
  move_current_piece(b, MOVE_LEFT);
}

void move_current_piece_right(struct board *b)
{
  move_current_piece(b, MOVE_RIGHT);
}

void rotate_current_piece(struct board *b, int dir)
{
  struct piece * current_piece = get_current_piece(b);
  int o = get_orientation(current_piece);
  if (dir == ROTATE_LEFT) o = o > 0 ? o - 1 : NB_ROTATIONS - 1;
  else o = o < NB_ROTATIONS - 1 ? o + 1 : 0;
    
  if (is_current_piece_rotable(b, o))
    {
      clear_piece(b, current_piece);
      set_orientation(current_piece, o);
      draw_piece(b, current_piece);
    }
}

void rotate_current_piece_left(struct board *b)
{
  rotate_current_piece(b, ROTATE_LEFT);
}

void rotate_current_piece_right(struct board *b)
{
  rotate_current_piece(b, ROTATE_RIGHT);
}

void delete_line(struct board *b, int row)
{
  for (int i = row; i > 0; --i)
    {
      for (int j = 0; j < BOARD_WIDTH; ++j)
	      {
	        b->area[i][j] = b->area[i-1][j];
	      }
    }
}

int delete_possible_lines(struct board *b)
{
  int nb_lines_deleted = 0;
  for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
      for (int j = 0; j < BOARD_WIDTH && b->area[i][j] != FREE; ++j) 
        if (j == BOARD_WIDTH)
          {
            ++nb_lines_deleted;
            delete_line(b, i);
          }
    }
  return nb_lines_deleted;
}

void drop_current_piece(struct board *b)
{
  struct piece * current_piece = get_current_piece(b);
  int i = get_row(current_piece);
  int j = get_column(current_piece);
 
  while (is_current_piece_movable(b, ++i, j))
    move_current_piece_down(b);
}

bool is_current_piece_fallen(struct board *b)
{
  struct piece * current_piece = get_current_piece(b);
  int i = get_row(current_piece);
  int j = get_column(current_piece);
 
  if (is_current_piece_movable(b, i + 1, j))
    return false;
 
  return true;
}

bool get_game_over(struct board *b)
{
  return b->game_over;
}

bool is_game_over(struct board *b)
{
  if (b->game_over) return true;
  for (int j = 0; j < BOARD_WIDTH; ++j)
    {
      if (b->area[0][j] != FREE)
	      return b->game_over = true;
    }
  return b->game_over = false;
}

uint get_score(struct board *b)
{
  return b->score;
}

uint get_level(struct board *b)
{
  return b->level;
}

uint get_lines(struct board *b)
{
  return b->lines;
}

void add_to_score(struct board *b, uint score)
{
  b->score += score;
}

void set_level(struct board *b, uint level)
{
  b->level = level;
}

void add_to_lines(struct board *b, uint lines)
{
  b->lines += lines;
}
