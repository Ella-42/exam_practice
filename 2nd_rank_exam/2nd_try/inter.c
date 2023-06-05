/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:49:48 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/31 14:26:27 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	check_dup(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	size_t	i;
	size_t	j;
	char save[10000];
	char result[10000];

	if (ac == 3)
	{
		i = 0;
		j = 0;
		while (av[1][i])
		{
			if (check_dup(av[2], av[1][i]))
			{
				save[j] = av[1][i];
				j++;
			}
			i++;
		}
		result[0] = save[0];
		i = 0;
		j = 1;
		while (save[i])
		{
			if (!check_dup(result, save[i]))
			{
				result[j] = save[i];
				j++;
			}
			i++;
		}
		i = 0;
		while (result[i])
		{
			write(1, &result[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
