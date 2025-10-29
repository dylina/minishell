/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorceac <dgorceac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:27:03 by dgorceac          #+#    #+#             */
/*   Updated: 2025/04/23 16:39:29 by dgorceac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_ptr(unsigned long long p)
{
	int		i;

	i = 0;
	if (!p)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	ft_putnbr_hex(p);
	while (p > 0)
	{
		i++;
		p = p / 16;
	}
	return (i + 2);
}

int	ft_hex_min_ptr(unsigned long long p)
{
	int		i;

	i = 0;
	if (p == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_putnbr_min_hex(p);
	while (p > 0)
	{
		i++;
		p = p / 16;
	}
	return (i);
}

int	ft_hex_maj_ptr(unsigned long long p)
{
	int		i;

	i = 0;
	if (p == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_putnbr_maj_hex(p);
	while (p > 0)
	{
		i++;
		p = p / 16;
	}
	return (i);
}
