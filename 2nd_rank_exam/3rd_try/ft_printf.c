/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:37:49 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/31 20:41:20 by lpeeters         ###   ########.fr       */
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
	if (num < 0)
	{
		count += cwrite('-');
		num = -num;
	}
	if (num > 9)
	{
		count = pnum((num / 10), count);
		count = pnum((num % 10), count);
	}
	else
		count += cwrite(num + 48);
	return (count);
}

int	phex(unsigned int hex, int count)
{
	if (hex > 15)
	{
		count = phex((hex / 16), count);
		count = phex((hex % 16), count);
	}
	else if (hex < 16 && hex > 9)
		count += cwrite(hex + 87);
	else
		count += cwrite(hex + 48);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		vlist;
	size_t		i;
	size_t		j;
	int		count;
	char		*str;
	int		num;
	unsigned int	hex;

	va_start(vlist, format);
	i = 0;
	j = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
			{
				str = va_arg(vlist, char *);
				if (!str)
				{
					write(1, "(null)", 6);
					count += 6;
				}
				else
				{
					while (str[j])
					{
						count += cwrite(str[j]);
						j++;
					}
				}
			}
			if (format[i] == 'd')
			{
				num = va_arg(vlist, int);
				if (num == -2147483648)
				{
					write (1, "-2147483648", 11);
					count += 11;
				}
				else
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
	int calc = (55 + 32);
	printf("calculator: %d\n", calc);

	char *str1 = NULL;
	printf("ft return: %d\n", ft_printf("%s\n", str1));
	printf("return: %d\n", printf("%s\n", str1));

	char *str2 = "testing: ";
	int num = -2147483648;
	printf("ft return: %d\n", ft_printf("%s%d\n", str2, num));
	printf("return: %d\n", printf("%s%d\n", str2, num));

	char *str3 = "testing: ";
	unsigned int hex = 3294873278;
	printf("ft return: %d\n", ft_printf("%s%x\n", str3, hex));
	printf("return: %d\n", printf("%s%x\n", str3, hex));
}*/
