#include "piece.h"
#include "video.h"

void random_piece(struct piece *p, int i, int j)
{
  p->kind = rand() % NB_KINDS;
  p->orientation = 0;
  p->color = kind_to_color(p->kind);
  p->row_pos = i;
  p->column_pos = j;
}

void set_kind(struct piece *p, int k)
{
  p->kind = k;
}

void set_orientation(struct piece *p, int o)
{
  p->orientation = o;
}

int get_kind(struct piece *p)
{
  return p->kind;
}

int get_orientation(struct piece *p)
{
  return p->orientation;
}

void set_color(struct piece *p, uint8_t c)
{
  p->color = c;
}

uint8_t get_color(struct piece *p)
{
  return p->color;
}

void set_row(struct piece *p, int row)
{
  p->row_pos = row;
}

int get_row(struct piece *p)
{
  return p->row_pos;
}

void set_column(struct piece *p, int column)
{
  p->column_pos = column;
}

int get_column(struct piece *p)
{
  return p->column_pos;
}

int get_shape_value(struct piece *p, int i, int j)
{
  return PIECES[p->kind][p->orientation][i][j];
}

uint8_t kind_to_color(int k)
{
  switch (k)
    {
      case I_KIND:
        return COLOR_CYAN;
      case J_KIND:
        return COLOR_BLUE;
      case L_KIND:
        return COLOR_LIGHT_RED;
      case O_KIND:
        return COLOR_YELLOW;
      case S_KIND:
        return COLOR_GREEN;
      case T_KIND:
        return COLOR_MAGENTA;
      case Z_KIND:
        return COLOR_RED;
      default:
        return COLOR_RED;
    }
}
