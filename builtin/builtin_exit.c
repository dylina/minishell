/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 16:01:09 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
	{
		i++;
		if (!str[i])
			return (0);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	builtin_exit(char **args, t_minishell *shell)
{
	int			exit_code;
	long long	num;

	write(STDOUT, "exit\n", 5);
	exit_code = shell->exit_status;
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			write(STDERR, "exit: ", 6);
			write(STDERR, args[1], ft_strlen(args[1]));
			write(STDERR, ": numeric argument required\n", 28);
			exit_code = 2;
		}
		else
		{
			if (args[2])
			{
				write(STDERR, "exit: too many arguments\n", 25);
				return (1);
			}
			num = ft_atoll(args[1]);
			exit_code = (unsigned char)num;
		}
	}
	cleanup_exec(&shell->exec);
	free_commands(shell->cmds);
	free_tokens(shell->tokens);
	if (shell->line)
		free(shell->line);
	free_array(shell->envp);
	exit(exit_code);
}
