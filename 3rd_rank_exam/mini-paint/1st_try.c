/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1st_try.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:48:28 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/14 17:43:31 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define READ_MODE "r"
#define EMPTY 'c'
#define FILLED 'C'

typedef struct s_draw_zone
{
	int		w;
	int		h;
	char	bg;
}			t_draw_zone;

typedef struct s_drawing
{
	char	t;
	float	x;
	float	y;
	float	r;
	char	f;
}			t_drawing;

int	calc_coord(t_drawing *d, int y, int x)
{
	if (sqrt(powf((y - d->y), 2) + powf((x - d->x), 2)) > d->r)
		return (-1);
	else if (d->r - sqrt(powf((y - d->y), 2) + powf((x - d->x), 2)) < 1)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	FILE		*op_file;
	int			fret;
	t_draw_zone	dz;
	t_drawing	d;
	if (!(op_file = fopen(av[1], READ_MODE)) || (fret = fscanf(op_file, "%i %i %c\n", &dz.w, &dz.h, &dz.bg)) != 3 || 0 > dz.w || dz.w > 301 || 0 > dz.h || dz.h > 301)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	char **draw_zone = (char **)malloc(sizeof(char *) * (dz.h + 1));
	int	y = 0;
	while (y < dz.h)
		draw_zone[y++] = (char *)malloc(dz.w + 1);
	draw_zone[y] = NULL;
	y = 0;
	while (draw_zone[y] != NULL)
	{
		int x = 0;
		while (x < dz.w)
		{
			draw_zone[y][x] = dz.bg;
			x++;
		}
		draw_zone[y][x] = '\0';
		y++;
	}
	while ((fret = fscanf(op_file, "\n%c %f %f %f %c", &d.t, &d.x, &d.y, &d.r, &d.f)) != -1)
	{
		if (fret != 5 || (d.t != EMPTY && d.t != FILLED) || d.r <= 0)
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
		y = 0;
		while (draw_zone[y] != NULL)
		{
			int x = 0;
			while (draw_zone[y][x] != '\0')
			{
				int ret = calc_coord(&d, y, x);
				if ((ret == 0 && d.t == FILLED) || ret == 1)
					draw_zone[y][x] = d.f;
				x++;
			}
			y++;
		}
	}
	y = 0;
	while (draw_zone[y] != NULL)
	{
		int x = 0;
		while (draw_zone[y][x] != '\0')
		{
			write(1, &draw_zone[y][x], 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
	return (0);
}
