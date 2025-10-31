/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 15:52:12 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			write(STDOUT, envp[i], ft_strlen(envp[i]));
			write(STDOUT, "\n", 1);
		}
		i++;
	}
	return (0);
}
