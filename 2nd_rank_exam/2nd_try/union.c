/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:28:14 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/31 14:47:14 by lpeeters         ###   ########.fr       */
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

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*mkstr(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char *str = str1;

	i = 0;
	j = ft_strlen(str1);
	while (str2[i])
	{
		str[j] = str2[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

#include <stdio.h>

int	main(int ac, char **av)
{
	size_t	i;
	size_t	j;

	if (ac == 3)
	{
		char *str = mkstr(av[1], av[2]);
		char result[10000];
		result[0] = str[0];
		i = 0;
		j = 1;
		while (str[i])
		{
			if (!check_dup(result, str[i]))
			{
				result[j] = str[i];
				j++;
			}
			i++;
		}
		printf("%s\n", result);
	}
	write(1, "\n", 1);
}
