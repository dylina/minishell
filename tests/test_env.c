/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:01:28 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 12:12:19 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

static char **create_test_env(void)
{
    char **env = malloc(sizeof(char *) * 6);
    if (!env)
        return (NULL);

    env[0] = ft_strdup("PATH=/usr/bin:/bin");
    env[1] = ft_strdup("HOME=/home/user");
    env[2] = ft_strdup("USER=testuser");
    env[3] = ft_strdup("SHELL=/bin/bash");
    env[4] = ft_strdup("TESTVAR=testvalue");
    env[5] = NULL;

    return (env);
}

static void free_env(char **env)
{
    int i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}

int main(void)
{
    printf("=== TEST BUILTIN ENV ===\n\n");

    // Test 1: env avec environnement de test
    printf("Test 1: Affichage de l'environnement de test\n");
    char **test_env = create_test_env();
    if (test_env)
    {
        builtin_env(test_env);
        printf("\n");

        // Test 2: Vérification qu'on n'affiche pas les variables sans '='
        printf("Test 2: Ajout d'une variable sans valeur (ne devrait pas s'afficher)\n");
        test_env = realloc(test_env, sizeof(char *) * 7);
        test_env[5] = ft_strdup("NOVALUE");
        test_env[6] = NULL;
        builtin_env(test_env);
        printf("\n");

        free_env(test_env);
    }

    // Test 3: env avec l'environnement réel
    printf("Test 3: Affichage de l'environnement réel (premières lignes)\n");
    extern char **environ;
    int i = 0;
    while (environ[i] && i < 5)
    {
        if (ft_strchr(environ[i], '='))
        {
            write(STDOUT, environ[i], ft_strlen(environ[i]));
            write(STDOUT, "\n", 1);
        }
        i++;
    }
    printf("... (tronqué)\n\n");

    return 0;
}
