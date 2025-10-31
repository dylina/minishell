/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdapremo <mdapremo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:01:12 by mdapremo          #+#    #+#             */
/*   Updated: 2025/10/30 12:12:10 by mdapremo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exec.h"

int main(void)
{
    printf("=== TEST BUILTIN PWD ===\n\n");

    // Test 1: pwd normal
    printf("Test 1: pwd dans le répertoire courant\n");
    builtin_pwd();
    printf("\n");

    // Test 2: pwd après changement de répertoire
    printf("Test 2: pwd après chdir vers /tmp\n");
    if (chdir("/tmp") == 0)
    {
        builtin_pwd();
    }
    else
    {
        printf("Erreur: impossible de changer vers /tmp\n");
    }
    printf("\n");

    // Test 3: pwd après retour au répertoire home
    printf("Test 3: pwd après retour au home\n");
    char *home = getenv("HOME");
    if (home && chdir(home) == 0)
    {
        builtin_pwd();
    }
    else
    {
        printf("Erreur: impossible de retourner au home\n");
    }
    printf("\n");

    // Test 4: pwd dans /
    printf("Test 4: pwd dans le répertoire racine\n");
    if (chdir("/") == 0)
    {
        builtin_pwd();
    }
    else
    {
        printf("Erreur: impossible de changer vers /\n");
    }
    printf("\n");

    return 0;
}
