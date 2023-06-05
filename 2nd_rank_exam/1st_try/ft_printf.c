/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:12:14 by lpeeters          #+#    #+#             */
/*   Updated: 2023/05/30 13:09:26 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>

int	cwrite(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_itoa(int num, int count)
{
	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		count += 11;
		return (count);
	}
	if (num < 0)
	{
		count += cwrite('-');
		num = num * -1;
	}
	if (num > 9)
	{
		count = ft_itoa(num / 10, count);
		count += cwrite((num % 10) + 48);
	}
	else
		count += cwrite(num + 48);
	return (count);
}

int	ft_hex(unsigned int hex, int count)
{
	if (hex == 0)
		count += write(1, "0", 1);
	else if (hex > 15)
	{
		count = ft_hex(hex / 16, count);
		count = ft_hex(hex % 16, count);
	}
	else
	{
		if (hex < 10)
			count += cwrite(hex + 48);
		else
			count += cwrite(hex - 10 + 'a');
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	*str;
	va_list	vlist;
	int		num;
	unsigned int	hex;

	i = 0;
	count = 0;
	hex = 0;
	va_start(vlist, format);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
			count += cwrite(format[i]);
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
			{
				str = va_arg(vlist, char *);
				if (!str)
				{
					write(1, "(null)", 6);
					return (6);
				}
				j = 0;
				while (str[j])
				{
					count += cwrite(str[j]);
					j++;
				}
			}
			else if (format[i] == 'd')
			{
				num = va_arg(vlist, int);
				count = ft_itoa(num, count);
			}
			else if (format[i] == 'x')
			{
				hex = va_arg(vlist, unsigned int);
				count = ft_hex(hex, count);
			}
		}
		i++;
	}
	va_end(vlist);
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
//	char	*str;
//	int	num = -2147483648;
	unsigned int	hex = -42;
//	str = ;
//	printf("test: %s", str);
	printf("\nreturn: %i\n", ft_printf("Hexadecimal for %d is %x\n", 42, hex));
	printf("\n=========================================================\n\n");
	printf("printf:\n");
	printf("\nreturn: %i\n", printf("Hexadecimal for %d is %x\n", 42, hex));
//	ft_printf("test: \n");
//	i += 48;
//	write(1, &i, 1);
}

int	main(void)
{
	printf("I - %d\n", printf("qwerty %s\t%d\t%x\n", "stroka1", 2147148145, -42));
  	printf("II - %d\n", ft_printf("qwerty %s\t%d\t%x\n", "stroka2", 2147148145, -42));
}*/
