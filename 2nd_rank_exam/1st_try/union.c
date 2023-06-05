/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:36:13 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/25 18:30:27 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_dup(char *written, char str)
{
	int	i;

	i = 0;
	while (written[i])
	{
		if (written[i] == str)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	int		j;
	char	*str;
	char	written[ft_strlen(av[1]) + ft_strlen(av[2]) + 1];

	if (ac < 3)
		return (0);
	if (ac == 3)
	{
		i = ft_strlen(av[1]);
		j = 0;
		str = av[1];
		while (av[2][j])
		{
			str[i] = av[2][j];
			i++;
			j++;
		}
		str[i] = '\0';
		i = 0;
		j = 0;
		write(1, &str[i], 1);
		written[j] = str[i];
		j = 1;
		while (str[i])
		{
			if (check_dup(written, str[i]))
			{
				write(1, &str[i], 1);
				written[j] = str[i];
				j++;
			}
			i++;
		}
		written[j] = '\0';
	}
	write(1, "\n", 1);
}
