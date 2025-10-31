/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:00:57 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 12:12:21 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

int main(void)
{
    printf("=== TEST BUILTIN ECHO ===\n\n");

    // Test 1: echo simple
    printf("Test 1: echo Hello World\n");
    char *args1[] = {"echo", "Hello", "World", NULL};
    builtin_echo(args1);
    printf("\n");

    // Test 2: echo avec -n (pas de newline)
    printf("Test 2: echo -n Hello (sans newline)\n");
    char *args2[] = {"echo", "-n", "Hello", NULL};
    builtin_echo(args2);
    printf(" <-- devrait être sur la même ligne\n\n");

    // Test 3: echo avec -nnn (multiple n)
    printf("Test 3: echo -nnn Multiple n\n");
    char *args3[] = {"echo", "-nnn", "Multiple", "n", NULL};
    builtin_echo(args3);
    printf(" <-- devrait être sur la même ligne\n\n");

    // Test 4: echo avec -n -n (multiple flags)
    printf("Test 4: echo -n -n Multiple flags\n");
    char *args4[] = {"echo", "-n", "-n", "Multiple", "flags", NULL};
    builtin_echo(args4);
    printf(" <-- devrait être sur la même ligne\n\n");

    // Test 5: echo avec -na (flag invalide)
    printf("Test 5: echo -na Invalid flag (devrait afficher -na)\n");
    char *args5[] = {"echo", "-na", "text", NULL};
    builtin_echo(args5);
    printf("\n");

    // Test 6: echo vide
    printf("Test 6: echo (sans arguments)\n");
    char *args6[] = {"echo", NULL};
    builtin_echo(args6);
    printf("\n");

    // Test 7: echo avec chaînes vides
    printf("Test 7: echo avec plusieurs arguments\n");
    char *args7[] = {"echo", "arg1", "arg2", "arg3", "arg4", NULL};
    builtin_echo(args7);
    printf("\n");

    return 0;
}
