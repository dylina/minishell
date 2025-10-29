/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorceac <dgorceac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:04:44 by dgorceac          #+#    #+#             */
/*   Updated: 2025/04/23 16:31:59 by dgorceac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbr_fd(int n, int fd)
{
	char	c;
	int		i;

	i = 0;
	if (n <= -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n = n * -1;
		write (fd, "-", 1);
		i++;
	}
	if (n > 9)
	{
		i += ft_nbr_fd(n / 10, fd);
	}
	c = n % 10 + '0';
	write(fd, &c, 1);
	i++;
	return (i);
}

int	ft_unsigned(unsigned int n)
{
	int		count;
	char	c;

	count = 0;
	if (n > 9)
	{
		count += ft_unsigned(n / 10);
	}
	c = n % 10 + '0';
	ft_putchar(c);
	count++;
	return (count);
}
