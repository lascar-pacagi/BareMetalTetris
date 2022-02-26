#ifndef __SHAPES_H__
#define __SHAPES_H__
 
#define NB_KINDS 7
#define NB_ROTATIONS 4
#define SIZE 4

enum { O_KIND = 0, I_KIND, S_KIND, Z_KIND, L_KIND, J_KIND, T_KIND };

extern const int PIECES[NB_KINDS][NB_ROTATIONS][SIZE][SIZE];

#endif
