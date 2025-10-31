/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:02:20 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 14:48:32 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

static t_minishell *create_test_shell(int exit_status)
{
    t_minishell *shell = malloc(sizeof(t_minishell));
    if (!shell)
        return (NULL);

    shell->exit_status = exit_status;
    shell->line = NULL;
    shell->tokens = NULL;
    shell->cmds = NULL;
    shell->envp = malloc(sizeof(char *) * 3);
    shell->envp[0] = ft_strdup("PATH=/usr/bin:/bin");
    shell->envp[1] = ft_strdup("HOME=/home/user");
    shell->envp[2] = NULL;

    return (shell);
}

static void test_exit_code(char **args, int expected_exit, int shell_status)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Processus enfant
        t_minishell *shell = create_test_shell(shell_status);
        if (!shell)
            exit(1);
        builtin_exit(args, shell);
        // Ne devrait jamais arriver ici
        exit(99);
    }
    else if (pid > 0)
    {
        // Processus parent
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            printf("Code de sortie reçu: %d ", exit_code);
            if (exit_code == expected_exit)
                printf("✓ (attendu: %d)\n", expected_exit);
            else
                printf("✗ (attendu: %d)\n", expected_exit);
        }
    }
}

int main(void)
{
    printf("=== TEST BUILTIN EXIT ===\n\n");
    printf("Note: exit() termine le processus, donc chaque test est dans un fork\n\n");

    // Test 1: exit sans argument (devrait retourner le dernier exit_status)
    printf("Test 1: exit (sans argument, exit_status=0)\n");
    char *args1[] = {"exit", NULL};
    test_exit_code(args1, 0, 0);
    printf("\n");

    // Test 2: exit avec un nombre positif
    printf("Test 2: exit 42\n");
    char *args2[] = {"exit", "42", NULL};
    test_exit_code(args2, 42, 0);
    printf("\n");

    // Test 3: exit avec 0
    printf("Test 3: exit 0\n");
    char *args3[] = {"exit", "0", NULL};
    test_exit_code(args3, 0, 0);
    printf("\n");

    // Test 4: exit avec un nombre négatif
    printf("Test 4: exit -1 (devrait donner 255 car unsigned char)\n");
    char *args4[] = {"exit", "-1", NULL};
    test_exit_code(args4, 255, 0);
    printf("\n");

    // Test 5: exit avec un grand nombre (overflow)
    printf("Test 5: exit 256 (devrait donner 0 car 256 %% 256)\n");
    char *args5[] = {"exit", "256", NULL};
    test_exit_code(args5, 0, 0);
    printf("\n");

    // Test 6: exit avec un argument non numérique
    printf("Test 6: exit abc (devrait donner 2 pour erreur)\n");
    char *args6[] = {"exit", "abc", NULL};
    test_exit_code(args6, 2, 0);
    printf("\n");

    // Test 7: exit avec le dernier exit_status non-zéro
    printf("Test 7: exit (sans argument, exit_status=127)\n");
    char *args7[] = {"exit", NULL};
    test_exit_code(args7, 127, 127);
    printf("\n");

    // Test 8: exit 257 (devrait donner 1)
    printf("Test 8: exit 257 (devrait donner 1 car 257 %% 256)\n");
    char *args8[] = {"exit", "257", NULL};
    test_exit_code(args8, 1, 0);
    printf("\n");

    // Test 9: exit avec argument numérique suivi de texte
    printf("Test 9: exit 42abc (devrait échouer)\n");
    char *args9[] = {"exit", "42abc", NULL};
    test_exit_code(args9, 2, 0);
    printf("\n");

    // Note: Le test "exit avec trop d'arguments" ne peut pas être testé ici
    // car il retourne 1 sans terminer le processus
    printf("Test 10: exit 1 2 (trop d'arguments - ce test doit être fait manuellement)\n");
    printf("car il retourne 1 sans exit()\n\n");

    return 0;
}
