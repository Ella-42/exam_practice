/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1st_try.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:04:02 by lpeeters          #+#    #+#             */
/*   Updated: 2023/08/10 01:00:18 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILLED 82
#define EMPTY 114

typedef struct s_data
{
	char	**rectangle;
	int		height;
	int		width;
	char	bg;
}			t_data;

typedef struct s_rect
{
	char	type;
	float	y;
	float	x;
	float	height;
	float	width;
	char	filler;
}			t_rect;

int	main(int ac, char **av)
{
	t_data	dz;
	t_rect	d;
	FILE	*op_file;
	int		y;
	int		x;
	int		fret;

	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	op_file = fopen(av[1], "r");
	if (fscanf(op_file, "%i %i %c\n", &dz.width, &dz.height, &dz.bg) != 3 || 1 > dz.width || dz.width > 300 || 1 > dz.height || dz.height > 300)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	dz.rectangle = (char **)malloc(sizeof(char *) * (dz.height + 1));
	y = 0;
	while (y < dz.height)
	{
		dz.rectangle[y] = (char *)malloc(sizeof(char) * (dz.width + 1));
		y++;
	}
	y = 0;
	while (y < dz.height)
	{
		x = 0;
		while (x < dz.width)
		{
			dz.rectangle[y][x] = dz.bg;
			x++;
		}
		dz.rectangle[y][x] = '\0';
		y++;
	}
	dz.rectangle[y] = NULL;
	while ((fret = fscanf(op_file, "%c %f %f %f %f %c\n", &d.type, &d.x, &d.y, &d.width, &d.height, &d.filler)))
	{
		if (fret == -1)
			return (0);
		else if (fret == 6)
			;
		else
			return (1);
		printf("%c\n", d.type);
		printf("%f\n", d.x);
		printf("%f\n", d.y);
		printf("%f\n", d.width);
		printf("%f\n", d.height);
		printf("%c\n", d.filler);
	}
	y = 0;
	while (dz.rectangle[y] != NULL)
	{
		x = 0;
		while (dz.rectangle[y][x] != '\0')
		{
			write(1, &dz.rectangle[y][x], 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}
