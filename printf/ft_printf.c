/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorceac <dgorceac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:21:43 by dgorceac          #+#    #+#             */
/*   Updated: 2025/04/23 16:44:28 by dgorceac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_format(char str, va_list args)
{
	if (str == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (str == 's')
		return (ft_str_fd(va_arg(args, char *), 1));
	else if (str == 'd' || str == 'i')
		return (ft_nbr_fd(va_arg(args, int), 1));
	else if (str == 'u')
		return (ft_unsigned(va_arg(args, int)));
	else if (str == 'p')
		return (ft_hex_ptr(va_arg(args, unsigned long long)));
	else if (str == 'x')
		return (ft_hex_min_ptr(va_arg(args, unsigned int)));
	else if (str == 'X')
		return (ft_hex_maj_ptr(va_arg(args, unsigned int)));
	else if (str == '%')
		return (write(1, "%", 1));
	return (check_format(str, args));
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += check_format(str[i + 1], args);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	int x = 10;
// 	int *p = &x;

// 	ft_printf("d: %d\n", 25);
// 	ft_printf("%: %%\n");
// 	ft_printf("I: %i\n", 55);
// 	ft_printf("S: %s\n", "Dumi");
// 	ft_printf("U: %u si %u\n", 0, 215);
// 	ft_printf("p: %p\n", (void *)&x);
// 	ft_printf("Hexa lowercase: %x\n", 3735928559u);
// 	ft_printf("Hexa uppercase: %X\n", 3735928559u);
// 	return (0);
// }
