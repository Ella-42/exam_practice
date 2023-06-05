/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:23:35 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/30 13:01:13 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	*word;
	int		num_read;

	line = malloc(10000);
	word = line;
	while (1)
	{
		num_read = read(fd, word, 1);
		if (num_read < 1 || *word == '\n')
			break ;
		word++;
	}
	if (word > line)
		return (*word = '\0', line);
	else
		return (free(line), NULL);
}

/*
char *get_next_line(int fd)
{
    char *line = malloc(10000), *word = line;
    while(read(fd, word, 1) > 0 && *word++ != '\n' );
    return ((word > line) ? (*word = 0, line) : (free(line), NULL));
}
*/

#include <stdio.h>

int main(void)
{
    char *line;

    line = get_next_line(0);
    while(line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(0);
    }
    return 0;
}
