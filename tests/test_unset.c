/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:02:02 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 14:46:07 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

static char **create_test_env(void)
{
    char **env = malloc(sizeof(char *) * 7);
    if (!env)
        return (NULL);

    env[0] = ft_strdup("PATH=/usr/bin:/bin");
    env[1] = ft_strdup("HOME=/home/user");
    env[2] = ft_strdup("USER=testuser");
    env[3] = ft_strdup("VAR1=value1");
    env[4] = ft_strdup("VAR2=value2");
    env[5] = ft_strdup("VAR3=value3");
    env[6] = NULL;

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
    printf("=== TEST BUILTIN UNSET ===\n\n");
    char **env = create_test_env();

    if (!env)
    {
        printf("Erreur: impossible de créer l'environnement de test\n");
        return (1);
    }

    // Test 1: Affichage de l'environnement initial
    printf("Test 1: Environnement initial\n");
    print_env(env);
    printf("\n");

    // Test 2: unset d'une variable existante
    printf("Test 2: unset VAR1\n");
    char *args2[] = {"unset", "VAR1", NULL};
    builtin_unset(args2, &env);
    printf("Environnement après unset:\n");
    print_env(env);
    printf("\n");

    // Test 3: unset d'une variable inexistante
    printf("Test 3: unset NONEXISTENT (ne devrait rien faire)\n");
    char *args3[] = {"unset", "NONEXISTENT", NULL};
    builtin_unset(args3, &env);
    printf("Environnement après unset (inchangé):\n");
    print_env(env);
    printf("\n");

    // Test 4: unset de plusieurs variables
    printf("Test 4: unset VAR2 VAR3\n");
    char *args4[] = {"unset", "VAR2", "VAR3", NULL};
    builtin_unset(args4, &env);
    printf("Environnement après unset multiple:\n");
    print_env(env);
    printf("\n");

    // Test 5: unset sans argument
    printf("Test 5: unset (sans argument - ne fait rien)\n");
    char *args5[] = {"unset", NULL};
    int ret = builtin_unset(args5, &env);
    printf("Code retour: %d\n", ret);
    print_env(env);
    printf("\n");

    // Test 6: unset avec identifiant invalide
    printf("Test 6: unset 123INVALID (devrait échouer)\n");
    char *args6[] = {"unset", "123INVALID", NULL};
    builtin_unset(args6, &env);
    printf("\n");

    // Test 7: unset avec identifiant invalide mais variable valide après
    printf("Test 7: unset INVALID-VAR PATH (PATH devrait être supprimé)\n");
    char *args7[] = {"unset", "INVALID-VAR", "PATH", NULL};
    builtin_unset(args7, &env);
    printf("Environnement après unset mixte:\n");
    print_env(env);
    printf("\n");

    // Test 8: unset de toutes les variables restantes
    printf("Test 8: unset HOME USER\n");
    char *args8[] = {"unset", "HOME", "USER", NULL};
    builtin_unset(args8, &env);
    printf("Environnement après unset final:\n");
    if (!env[0])
        printf("  (vide)\n");
    else
        print_env(env);
    printf("\n");

    free_env(env);
    return 0;
}
