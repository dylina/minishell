/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 16:09:54 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

static char	*get_env_value(char **envp, char *key)
{
	int		i;
	int		key_len;

	if (!envp || !key)
		return (NULL);
	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0
			&& envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

static void	update_pwd_env(char ***envp, char *oldpwd)
{
	char	cwd[1024];
	char	*pwd_str;
	char	*oldpwd_str;

	if (!envp || !*envp)
		return ;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd: error retrieving current directory");
		return ;
	}
	pwd_str = ft_strjoin("PWD=", cwd);
	if (pwd_str) {
		builtin_export((char *[]){"export", pwd_str, NULL}, envp);
		free(pwd_str);
	}
	if (oldpwd && oldpwd[0])
	{
		oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
		if (oldpwd_str)
		{
			builtin_export((char *[]){"export", oldpwd_str, NULL}, envp);
			free(oldpwd_str);
		}
	}
}

static int	change_to_home(char ***envp)
{
	char	*home;
	char	oldpwd[1024];

	home = get_env_value(*envp, "HOME");
	if (!home)
	{
		write(STDERR, "cd: HOME not set\n", 17);
		return (1);
	}
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		oldpwd[0] = '\0';
	if (chdir(home) == -1)
	{
		write(STDERR, "cd: ", 4);
		write(STDERR, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR, "\n", 1);
		return (1);
	}
	update_pwd_env(envp, oldpwd);
	return (0);
}

static int	change_to_oldpwd(char ***envp)
{
	char	*oldpwd;
	char	current_pwd[1024];

	oldpwd = get_env_value(*envp, "OLDPWD");
	if (!oldpwd)
	{
		write(STDERR, "cd: OLDPWD not set\n", 19);
		return (1);
	}
	if (getcwd(current_pwd, sizeof(current_pwd)) == NULL)
		current_pwd[0] = '\0';
	if (chdir(oldpwd) == -1)
	{
		write(STDERR, "cd: ", 4);
		write(STDERR, oldpwd, ft_strlen(oldpwd));
		write(STDERR, ": ", 2);
		write(STDERR, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR, "\n", 1);
		return (1);
	}
	write(STDOUT, oldpwd, ft_strlen(oldpwd));
	write(STDOUT, "\n", 1);
	update_pwd_env(envp, current_pwd);
	return (0);
}

int	builtin_cd(char **args, char ***envp)
{
	char	oldpwd[1024];

	if (!args || !envp || !*envp)
		return (1);
	if (!args[1])
		return (change_to_home(envp));
	if (args[2])
	{
		write(STDERR, "cd: too many arguments\n", 23);
		return (1);
	}
	if (ft_strcmp(args[1], "-") == 0)
		return (change_to_oldpwd(envp));
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		oldpwd[0] = '\0';
	if (chdir(args[1]) == -1)
	{
		write(STDERR, "cd: ", 4);
		write(STDERR, args[1], ft_strlen(args[1]));
		write(STDERR, ": ", 2);
		write(STDERR, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR, "\n", 1);
		return (1);
	}
	update_pwd_env(envp, oldpwd);
	return (0);
}
