/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:57 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 15:53:15 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

int	find_env_index(char **envp, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = 0;
	while (key[key_len] && key[key_len] != '=')
		key_len++;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0
			&& (envp[i][key_len] == '=' || envp[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	**realloc_env(char **envp, int new_size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i] = NULL;
	free(envp);
	return (new_env);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] != '_' && (str[0] < 'a' || str[0] > 'z')
		&& (str[0] < 'A' || str[0] > 'Z'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

void	print_export_var(char *var)
{
	int		i;
	char	*eq_pos;

	write(STDOUT, "declare -x ", 11);
	eq_pos = ft_strchr(var, '=');
	if (!eq_pos)
	{
		write(STDOUT, var, ft_strlen(var));
		write(STDOUT, "\n", 1);
		return ;
	}
	i = 0;
	while (var[i] && var[i] != '=')
	{
		write(STDOUT, &var[i], 1);
		i++;
	}
	write(STDOUT, "=\"", 2);
	i++;
	while (var[i])
	{
		write(STDOUT, &var[i], 1);
		i++;
	}
	write(STDOUT, "\"\n", 2);
}

int	print_all_exports(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		print_export_var(envp[i]);
		i++;
	}
	return (0);
}
