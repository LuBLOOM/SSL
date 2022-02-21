#include "../include/linear.h"

/* 4x4 Matrix in Column-Major Order
  00 04 08 12
  01 05 09 13
  02 06 10 14
  03 07 11 15

  4x4 Matrix in Row-Major Order
  00 01 02 03
  04 05 06 07
  08 09 10 11
  12 13 14 15
 */

static inline void _mat4_swap(float *a, float *b)
{
	float tmp = *a; *a = *b; *b = tmp;
}

void mat4_init(float *mat4)
{
	*(mat4+0) = 1.; *(mat4+4) = 0.; *(mat4+8) = 0.;  *(mat4+12) = 0.;
	*(mat4+1) = 0.; *(mat4+5) = 1.; *(mat4+9) = 0.;  *(mat4+13) = 0.;
	*(mat4+2) = 0.; *(mat4+6) = 0.; *(mat4+10) = 1.; *(mat4+14) = 0.;
	*(mat4+3) = 0.; *(mat4+7) = 0.; *(mat4+11) = 0.; *(mat4+15) = 1.;
}

void mat4_scale(float *mat4, float w, float h, float d)
{
	*(mat4+0) = w;
	*(mat4+5) = h;
	*(mat4+10) = d;
}

void mat4_translate(float *mat4, float dx, float dy, float dz)
{
	*(mat4+12) = dx;
	*(mat4+13) = dy;
	*(mat4+14) = dz;
}

void mat4_ortho(float *mat4, float t, float r, float b, float l, float n, float f)
{
	*(mat4+0) = 2/(r-l); *(mat4+4) = 0.;      *(mat4+8) = 0.;        *(mat4+12) = -(r+l)/(r-l);
	*(mat4+1) = 0.;      *(mat4+5) = 2/(t-b); *(mat4+9) = 0.;        *(mat4+13) = -(t+b)/(t-b);
	*(mat4+2) = 0.;      *(mat4+6) = 0.;      *(mat4+10) = -2/(f-n); *(mat4+14) = -(f+n)/(f-n);
	*(mat4+3) = 0.;      *(mat4+7) = 0.;      *(mat4+11) = 0.;       *(mat4+15) = 1.;
}

//switch between column-major and row-major order
void mat4_transpose(float *mat4)
{
	_mat4_swap(mat4+1,  mat4+4);
	_mat4_swap(mat4+2,  mat4+8);
	_mat4_swap(mat4+3,  mat4+12);
	_mat4_swap(mat4+7,  mat4+13);
	_mat4_swap(mat4+11, mat4+14);
	_mat4_swap(mat4+9,  mat4+6);
}
