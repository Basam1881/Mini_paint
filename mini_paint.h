#ifndef MINI_PAINT_H
# define MINI_PAINT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_cir
{
	char	**str;
	char	*path;
	FILE	*fd;
	int		b_width, b_hight;
	char	b_c, c, fill_flag;
	float	x, y, r;
}				t_cir;

#endif