/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:40:29 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/30 19:37:06 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int	cwrite(char c)
{
	write(1, &c, 1);
	return (1);
}

int	pnum(int num, int count)
{
	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (num < 0)
	{
		count += cwrite('-');
		num = -num;
	}
	if (num < 10)
		count += cwrite(num + 48);
	else
	{
		count = pnum(num / 10, count);
		count++;
		num = pnum(num % 10, count);
	}
	return (count);
}

int	phex(unsigned int hex, int count)
{
	if (hex < 10)
		count += cwrite(hex + 48);
	else if (hex < 16)
		count += cwrite(hex + 87);
	else
	{
		count = phex(hex / 16, count);
		count++;
		hex = phex(hex % 16, count);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		vlist;
	int		count;
	size_t		i;
	size_t		j;
	char		*str;
	int		num;
	unsigned int	hex;

	va_start(vlist, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
			{
				str = va_arg(vlist, char *);
				j = 0;
				if (!str)
				{
					write(1, "(null)", 6);
					return (6);
				}
				while (str[j])
				{
					count += cwrite(str[j]);
					j++;
				}
			}
			if (format[i] == 'd')
			{
				num = va_arg(vlist, int);
				count = pnum(num, count);
			}
			if (format[i] == 'x')
			{
				hex = va_arg(vlist, unsigned int);
				count = phex(hex, count);
			}
		}
		else
			count += cwrite(format[i]);
		i++;
	}
	va_end(vlist);
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
	char *str = "test";
	int ret1 = ft_printf("%s\n", str);
	int ret2 = printf("%s\n", str);

	int num = -2147483648;
	int ret1 = ft_printf("%s %d\n", "num:", num);
	int ret2 = printf("%s %d\n", "num:", num);

	unsigned int hex = 127;
	int ret1 = ft_printf("hex for %d is %x", num, hex);
	int ret2 = printf("hex for %d is %x", num, hex);
	
	printf("\n=====return values=====\nft_printf: %d, printf: %d\n", ret1, ret2);
}*/
