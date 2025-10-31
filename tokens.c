/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorceac <dgorceac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:07:39 by dgorceac          #+#    #+#             */
/*   Updated: 2025/10/31 19:09:40 by dgorceac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token(t_token_type type, char *value)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
    {
        perror("token malloc failed");
        return (NULL);
    }
    token->type = type;
    token->value = ft_strdup(value);
    if (!token->value)
    {
        perror("Error\ntoken value malloc\n");
        return (NULL);
    }
    token->next = NULL;
    return (token);
}

void    add_token(t_token **head, t_token *new_token)
{
    t_token *cur;

    cur = *head;
    if (!cur)
    {
        *head = new_token;
        return ;
    }
    while (cur->next)
        cur = cur->next;
    cur->next = new_token;
}

void    free_tokens(t_token *head)
{
    t_token *cur = head;
    while (cur)
    {
        t_token *tmp = cur->next;
        free(cur->value);
        free(cur);
        cur = tmp;
    }
}

// test
t_token_type classify_token(const char *s)
{
    if (strcmp(s, "<") == 0)
        return TOKEN_IN;
    if (strcmp(s, ">") == 0)
        return TOKEN_OUT;
    if (strcmp(s, "<<") == 0)
        return TOKEN_HEREDOC;
    if (strcmp(s, ">>") == 0)
        return TOKEN_APPEND;
    if (strcmp(s, "|") == 0)
        return TOKEN_PIPE;
    return TOKEN_WORD;
}
