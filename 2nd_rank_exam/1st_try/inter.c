/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:59:40 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/29 18:28:39 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_checkdup(char c, char *str)
{
	int i = 0;
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
	if (ac != 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	int i = 0;
	int j = 0;
	char str[9999];
	while (av[1][i])
	{
		if (!ft_checkdup(av[1][i], str))
		{
			if (ft_checkdup(av[1][i], av[2]))
			{
				str[j] = av[1][i];
				write(1, &str[j], 1);
				j++;
			}
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
