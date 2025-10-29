#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>

typedef struct s_tokens
{
    //type
	char				*value;
	struct s_tokens		*next;
} t_tokens;

typedef struct s_lexer
{
    int             i;
    char            *str;
    t_tokens        token;
    struct s_lexer  *next;
    struct s_lexer  *prev;

} t_lexer;

#endif