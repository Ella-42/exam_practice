/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1st_try.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:04:02 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/11 23:34:05 by lpeeters         ###   ########.fr       */
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

int	calc(t_drawing *d, int y, int x)
{
	if (y < d->y || x < d->x || y > d->y + d->height || x > d->x + d->height)
		return (-1);
	//else if ()
		//return (1);
	else
		return (0);
}

int	replace_chars(t_draw_zone *dz, t_drawing *d)
{
	int	y;
	int	x;
	int	ret;

	if (d->height <= 0 || d->width <= 0 || (d->type != 'r' && d->type != 'R'))
		return (1);
	printf("%c\n", d->type);
	printf("%f\n", d->x);
	printf("%f\n", d->y);
	printf("%f\n", d->width);
	printf("%f\n", d->height);
	printf("%c\n", d->filler);
	y = 0;
	while (dz->zone[y] != NULL)
	{
		x = 0;
		while (dz->zone[y][x] != '\0')
		{
			ret = calc(d, y, x);
			if ((ret == 0 && d->type == 'R') || ret == 1)
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
	if (op_file == NULL || fscanf(op_file, "%i %i %c\n", &dz.width, &dz.height, &dz.bg) != 3 || 1 > dz.width || dz.width > 300 || 1 > dz.height || dz.height > 300)
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
