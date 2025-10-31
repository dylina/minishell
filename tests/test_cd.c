/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:01:38 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 12:12:23 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

static char **create_test_env(void)
{
    char cwd[1024];
    char **env = malloc(sizeof(char *) * 5);
    if (!env)
        return (NULL);

    if (getcwd(cwd, sizeof(cwd)))
    {
        char *pwd = ft_strjoin("PWD=", cwd);
        env[0] = pwd;
    }
    else
        env[0] = ft_strdup("PWD=/tmp");

    env[1] = ft_strdup("OLDPWD=/tmp");
    env[2] = ft_strdup("HOME=/tmp");
    env[3] = ft_strdup("USER=testuser");
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

static void print_current_dir(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)))
        printf("Répertoire actuel: %s\n", cwd);
    else
        printf("Erreur getcwd\n");
}

int main(void)
{
    printf("=== TEST BUILTIN CD ===\n\n");
    char **env = create_test_env();

    if (!env)
    {
        printf("Erreur: impossible de créer l'environnement de test\n");
        return (1);
    }

    // Test 1: cd vers un répertoire absolu
    printf("Test 1: cd /tmp\n");
    char *args1[] = {"cd", "/tmp", NULL};
    print_current_dir();
    builtin_cd(args1, &env);
    print_current_dir();
    printf("\n");

    // Test 2: cd vers HOME (sans argument)
    printf("Test 2: cd (vers HOME)\n");
    char *args2[] = {"cd", NULL};
    builtin_cd(args2, &env);
    print_current_dir();
    printf("\n");

    // Test 3: cd vers un répertoire relatif
    printf("Test 3: cd .. (répertoire parent)\n");
    char *args3[] = {"cd", "..", NULL};
    builtin_cd(args3, &env);
    print_current_dir();
    printf("\n");

    // Test 4: cd - (retour au répertoire précédent)
    printf("Test 4: cd - (OLDPWD)\n");
    char *args4[] = {"cd", "-", NULL};
    builtin_cd(args4, &env);
    print_current_dir();
    printf("\n");

    // Test 5: cd vers un répertoire inexistant
    printf("Test 5: cd /repertoire/inexistant (devrait échouer)\n");
    char *args5[] = {"cd", "/repertoire/inexistant", NULL};
    int ret = builtin_cd(args5, &env);
    printf("Code retour: %d\n", ret);
    print_current_dir();
    printf("\n");

    // Test 6: cd avec trop d'arguments
    printf("Test 6: cd /tmp /var (trop d'arguments)\n");
    char *args6[] = {"cd", "/tmp", "/var", NULL};
    ret = builtin_cd(args6, &env);
    printf("Code retour: %d\n", ret);
    printf("\n");

    // Test 7: cd . (répertoire courant)
    printf("Test 7: cd . (répertoire courant)\n");
    char *args7[] = {"cd", ".", NULL};
    builtin_cd(args7, &env);
    print_current_dir();
    printf("\n");

    free_env(env);
    return 0;
}
