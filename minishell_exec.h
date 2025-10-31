/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:05:56 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 16:01:00 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				here_doc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	int		**pipes;
	pid_t	*pids;
	int		pipe_count;
	int		cmd_count;
}	t_exec;

typedef struct s_minishell
{
	char		*line;
	t_token		*tokens;
	t_cmd		*cmds;
	char		**envp;
	int			exit_status;
	t_exec		exec;
}	t_minishell;

int		builtin_export(char **args, char ***envp);
int		builtin_unset(char **args, char ***envp);
int		builtin_cd(char **args, char ***envp);
int	builtin_env(char **envp);
int	builtin_pwd(void);
int	builtin_echo(char **args);
int	execute_builtin(t_minishell *shell, t_cmd *cmd);
int	is_builtin(char *cmd);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
int		array_len(char **array);
void	free_array(char **array);
void	free_tokens(t_token *tokens);
void	free_commands(t_cmd *cmds);
void	cleanup_exec(t_exec *exec);
int	find_env_index(char **envp, char *key);
char	**realloc_env(char **envp, int new_size);
int	is_valid_identifier(char *str);
void	print_export_var(char *var);
int	print_all_exports(char **envp);
int	builtin_exit(char **args, t_minishell *shell);

#endif
