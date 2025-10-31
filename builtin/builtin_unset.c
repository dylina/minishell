/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:49:29 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 15:49:40 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

int	builtin_unset(char **args, char ***envp)
{
	int	i;
	int	index;
	int	j;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(STDERR, "unset: `", 8);
			write(STDERR, args[i], ft_strlen(args[i]));
			write(STDERR, "': not a valid identifier\n", 26);
			i++;
			continue ;
		}
		index = find_env_index(*envp, args[i]);
		if (index != -1)
		{
			free((*envp)[index]);
			j = index;
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
		}
		i++;
	}
	return (0);
}
