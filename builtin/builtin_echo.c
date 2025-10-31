/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:48:39 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 15:49:49 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

int	builtin_echo(char **args)
{
	int	i;
	int	newline;
	int	j;

	i = 1;
	newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			newline = 0;
			i++;
		}
		else
			break ;
	}
	while (args[i])
	{
		write(STDOUT, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT, "\n", 1);
	return (0);
}
