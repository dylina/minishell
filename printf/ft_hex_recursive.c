/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_recursive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorceac <dgorceac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:37:41 by dgorceac          #+#    #+#             */
/*   Updated: 2025/04/23 16:39:39 by dgorceac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hex(unsigned long long p)
{
	if (p >= 16)
		ft_putnbr_hex(p / 16);
	write(1, &"0123456789abcdef"[p % 16], 1);
}

void	ft_putnbr_min_hex(unsigned long long p)
{
	if (p >= 16)
		ft_putnbr_min_hex(p / 16);
	write(1, &"0123456789abcdef"[p % 16], 1);
}

void	ft_putnbr_maj_hex(unsigned long long p)
{
	if (p >= 16)
		ft_putnbr_maj_hex(p / 16);
	write(1, &"0123456789ABCDEF"[p % 16], 1);
}
