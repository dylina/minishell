/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorceac <dgorceac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:29:52 by dgorceac          #+#    #+#             */
/*   Updated: 2025/10/08 13:43:46 by dgorceac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_nbr_fd(int n, int fd);
int		ft_str_fd(char *s, int fd);
int		ft_unsigned(unsigned int n);
int		ft_hex_ptr(unsigned long long p);
void	ft_putnbr_hex(unsigned long long p);
int		ft_hex_maj_ptr(unsigned long long p);
void	ft_putnbr_maj_hex(unsigned long long p);
int		ft_hex_min_ptr(unsigned long long p);
void	ft_putnbr_min_hex(unsigned long long p);

#endif
