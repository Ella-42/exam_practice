/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1st_try.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:04:02 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/13 22:54:59 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILLED 82
#define EMPTY 114

typedef struct s_draw_zone
{
	char	**zone;
	int		height;
	int		width;
	char	bg;
}			t_draw_zone;

typedef struct s_drawing
{
	char	type;
	float	y;
	float	x;
	float	height;
	float	width;
	char	filler;
}			t_drawing;

int	calc_coord(t_drawing *d, int y, int x)
{
	if (y < d->y || x < d->x || d->y + d->height < y || d->x + d->width < x)
		return (-1);
	else if (y - d->y < 1 || x - d->x < 1 || d->y + d->height - y < 1 || d->x + d->width - x < 1)
		return (1);
	else
		return (0);
}

int	replace_chars(t_draw_zone *dz, t_drawing *d)
{
	int	y;
	int	x;
	int	calc_val;

	if (d->height <= 0 || d->width <= 0 || (d->type != EMPTY && d->type != FILLED))
		return (1);
	y = 0;
	while (dz->zone[y] != NULL)
	{
		x = 0;
		while (dz->zone[y][x] != '\0')
		{
			calc_val = calc_coord(d, y, x);
			if ((calc_val == 0 && d->type == FILLED) || calc_val == 1)
				dz->zone[y][x] = d->filler;
			x++;
		}
		y++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_draw_zone	dz;
	t_drawing	d;
	FILE		*op_file;
	int			y;
	int			x;
	int			fret;

	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	op_file = fopen(av[1], "r");
	if (op_file == NULL || fscanf(op_file, "%d %d %c\n", &dz.width, &dz.height, &dz.bg) != 3 || 1 > dz.width || dz.width > 300 || 1 > dz.height || dz.height > 300)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	dz.zone = (char **)malloc(sizeof(char *) * (dz.height + 1));
	y = 0;
	while (y < dz.height)
	{
		dz.zone[y] = (char *)malloc(sizeof(char) * (dz.width + 1));
		y++;
	}
	y = 0;
	while (y < dz.height)
	{
		x = 0;
		while (x < dz.width)
		{
			dz.zone[y][x] = dz.bg;
			x++;
		}
		dz.zone[y][x] = '\0';
		y++;
	}
	dz.zone[y] = NULL;
	while ((fret = fscanf(op_file, "\n%c %f %f %f %f %c", &d.type, &d.x, &d.y, &d.width, &d.height, &d.filler)))
	{
		if (fret == -1)
			break ;
		else if (fret == 6)
			;
		else
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
		if (replace_chars(&dz, &d))
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
	}
	y = 0;
	while (dz.zone[y] != NULL)
	{
		x = 0;
		while (dz.zone[y][x] != '\0')
		{
			write(1, &dz.zone[y][x], 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}
