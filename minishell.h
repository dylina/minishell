#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef enum token_type
{
    TOKEN_IN,//<
    TOKEN_OUT,//>
    TOKEN_HEREDOC,// <<
    TOKEN_APPEND,// >>
    TOKEN_PIPE,
    TOKEN_DOUBLE_Q,
    TOKEN_SINGLE_Q,
    TOKEN_WORD,
    TOKEN_EOF,
} t_token_type;

typedef struct s_token
{
    t_token_type        type;
    char				*value;
    struct s_token		*next;
} t_token;

typedef struct s_lexer
{
    int             i;
    char            *str;
    t_token         token;
    struct s_lexer  *next;
    struct s_lexer  *prev;

} t_lexer;

/*de vazut*/
typedef struct s_command {
    char **argv;          // lista de argumente
    char *infile;         // fisier de intrare (<)
    char *outfile;        // fisier de iesire (>, >>)
    int append;           // flag pentru >>
    struct s_command *next; // pentru pipe
} t_command;
#endif
