#include "mini_paint.h"

void	draw(t_cir *cir)
{
	int	i = 0, j;
	while (i < cir->b_hight)
	{
		j = 0;
		while (j < cir->b_width)
		{
			write(1, &cir->str[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		cir->str[i][j] = 0;
		i++;
	}
	cir->str[i] = NULL;
}

void	store_line(t_cir *cir)
{
	int		i = 0, j, y = 0, x;
	float	r;
	while (i < cir->b_hight)
	{
		j = 0;
		x = 0;
		while (j < cir->b_width)
		{
			r = sqrt((x - cir->x) * (x - cir->x) + (y - cir->y) * (y - cir->y));
			if (r <= cir->r)
			{
				if (cir->r - r >= 1)
				{
					if (cir->fill_flag == 'C')
						cir->str[i][j] = cir->c;
				}
				else
					cir->str[i][j] = cir->c;
			}
			j++;
			x++;
		}
		i++;
		y++;
	}
}

int	check_lines(t_cir *cir)
{
	int	parms = 0;
	while (1)
	{
		parms = fscanf(cir->fd, "%c %f %f %f %c\n", &cir->fill_flag, &cir->x, &cir->y, &cir->r, &cir->c);
		if (parms == -1)
			break ;
		if (parms != 5)
			return (1);
		if ((cir->fill_flag != 'C' && cir->fill_flag != 'c') || cir->r <= 0)
			return (1);
		store_line(cir);
	}
	return (0);
}

void	main_store(t_cir *cir)
{
	int	i = 0, j;
	while (i < cir->b_hight)
	{
		j = 0;
		while (j < cir->b_width)
		{
			cir->str[i][j] = cir->b_c;
			j++;
		}
		cir->str[i][j] = 0;
		i++;
	}
	cir->str[i] = NULL;
}

int	file_reader(t_cir *cir)
{
	int	i = 0;
	cir->fd = fopen(cir->path, "r");
	if (!cir->fd)
		return (1);
	if (fscanf(cir->fd, "%d %d %c\n", &cir->b_width, &cir->b_hight, &cir->b_c) == 3)
	{
		if (cir->b_width <= 0 || cir->b_width > 300 || cir->b_hight <= 0 || cir->b_hight > 300)
			return (1);
		cir->str = (char **)malloc(sizeof(char *) * (cir->b_hight + 1));
		if (!cir->str)
			return (1);
		while (i < cir->b_hight)
		{
			cir->str[i] = (char *)malloc(sizeof(char) * (cir->b_width + 1));
			if (!cir->str[i])
				return (1);
			i++;
		}
		main_store(cir);
		if (check_lines(cir))
			return (1);
		draw(cir);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_cir cir;

	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	cir.path = av[1];
	if (file_reader(&cir))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	return (0);
}