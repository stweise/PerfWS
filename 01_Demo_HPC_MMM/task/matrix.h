#include <stdio.h>
#include <stdlib.h>
struct matrix
{
  int dims[2];
  void * val; 
};

typedef struct matrix matrix;
matrix * matrix_new(int * dims);
void matrix_init(matrix * this, int * dims);
void matrix_kill(matrix * this);
void matrix_fill_row(matrix * this, int colIdx,double * arr);
void matrix_print(matrix * this);
void  matrix_multiply(matrix * pm1, matrix * pm2, matrix * res);
