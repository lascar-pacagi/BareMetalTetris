#ifndef __PIECE_H__
#define __PIECE_H__
 
#include "shapes.h"
#include "types.h"

struct piece
{
  int kind;
  int orientation;
  uint8_t color; 
  int row_pos;
  int column_pos;
};

void random_piece(struct piece *p, int i, int j);
void set_kind(struct piece *p, int k);
void set_orientation(struct piece *p, int o); 
int get_kind(struct piece *p);
int get_orientation(struct piece *p);
void set_color(struct piece *p, uint8_t c);
uint8_t get_color(struct piece *p);
void set_row(struct piece *p, int row);
int get_row(struct piece *p);
void set_column(struct piece *p, int column);
int get_column(struct piece *p);
int get_shape_value(struct piece *p, int i, int j);
uint8_t kind_to_color(int k);

#endif
