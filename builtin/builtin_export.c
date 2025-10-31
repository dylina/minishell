/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:51:18 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 15:51:28 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

int	builtin_export(char **args, char ***envp)
{
	int		i;
	int		index;
	int		env_size;

	if (!args[1])
		return (print_all_exports(*envp));
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(STDERR, "export: `", 9);
			write(STDERR, args[i], ft_strlen(args[i]));
			write(STDERR, "': not a valid identifier\n", 26);
			i++;
			continue ;
		}
		index = find_env_index(*envp, args[i]);
		if (index != -1 && ft_strchr(args[i], '='))
		{
			free((*envp)[index]);
			(*envp)[index] = ft_strdup(args[i]);
		}
		else if (index == -1)
		{
			env_size = array_len(*envp);
			*envp = realloc_env(*envp, env_size + 1);
			if (!*envp)
				return (1);
			(*envp)[env_size] = ft_strdup(args[i]);
			(*envp)[env_size + 1] = NULL;
		}
		i++;
	}
	return (0);
}
