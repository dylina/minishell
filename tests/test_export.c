/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:01:50 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 14:46:29 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

static char **create_test_env(void)
{
    char **env = malloc(sizeof(char *) * 5);
    if (!env)
        return (NULL);

    env[0] = ft_strdup("PATH=/usr/bin:/bin");
    env[1] = ft_strdup("HOME=/home/user");
    env[2] = ft_strdup("USER=testuser");
    env[3] = ft_strdup("TESTVAR=oldvalue");
    env[4] = NULL;

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

static void print_env(char **env)
{
    int i = 0;
    while (env[i])
    {
        printf("  %s\n", env[i]);
        i++;
    }
}

int main(void)
{
    printf("=== TEST BUILTIN EXPORT ===\n\n");
    char **env = create_test_env();

    if (!env)
    {
        printf("Erreur: impossible de créer l'environnement de test\n");
        return (1);
    }

    // Test 1: export sans argument (liste toutes les variables)
    printf("Test 1: export (sans argument - liste les variables)\n");
    char *args1[] = {"export", NULL};
    builtin_export(args1, &env);
    printf("\n");

    // Test 2: export d'une nouvelle variable
    printf("Test 2: export NEWVAR=newvalue\n");
    char *args2[] = {"export", "NEWVAR=newvalue", NULL};
    builtin_export(args2, &env);
    printf("Environnement après export:\n");
    print_env(env);
    printf("\n");

    // Test 3: modification d'une variable existante
    printf("Test 3: export TESTVAR=newvalue (modification)\n");
    char *args3[] = {"export", "TESTVAR=newvalue", NULL};
    builtin_export(args3, &env);
    printf("Environnement après modification:\n");
    print_env(env);
    printf("\n");

    // Test 4: export d'une variable sans valeur
    printf("Test 4: export NOVALUE (sans =)\n");
    char *args4[] = {"export", "NOVALUE", NULL};
    builtin_export(args4, &env);
    printf("Environnement après export sans valeur:\n");
    print_env(env);
    printf("\n");

    // Test 5: export avec identifiant invalide
    printf("Test 5: export 123INVALID=value (devrait échouer)\n");
    char *args5[] = {"export", "123INVALID=value", NULL};
    builtin_export(args5, &env);
    printf("\n");

    // Test 6: export avec plusieurs variables
    printf("Test 6: export VAR1=val1 VAR2=val2 VAR3=val3\n");
    char *args6[] = {"export", "VAR1=val1", "VAR2=val2", "VAR3=val3", NULL};
    builtin_export(args6, &env);
    printf("Environnement après exports multiples:\n");
    print_env(env);
    printf("\n");

    // Test 7: export avec identifiant contenant des caractères spéciaux
    printf("Test 7: export INVALID-VAR=value (devrait échouer)\n");
    char *args7[] = {"export", "INVALID-VAR=value", NULL};
    builtin_export(args7, &env);
    printf("\n");

    // Test 8: export avec underscore et chiffres (valide)
    printf("Test 8: export _VAR_123=valid\n");
    char *args8[] = {"export", "_VAR_123=valid", NULL};
    builtin_export(args8, &env);
    printf("Environnement après export valide:\n");
    print_env(env);
    printf("\n");

    free_env(env);
    return 0;
}
