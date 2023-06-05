/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:50:52 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/31 20:44:53 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char *line = malloc(10000), *word = line;
	while (read(fd, word, 1) > 0 && *word++ != '\n');
	return ((word > line) ? (*word = 0, line) : (free(line), NULL));
}
/*
#include <stdio.h>

int	main(void)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(0);
	}
	return (0);
}*/
