/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:44:30 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:45:53 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_echo(t_shell *shell, char **argv)
{
    int i = 1;
    int newline = 1;

    if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
    {
        newline = 0;
        i = 2;
    }

    while (argv[i])
    {
        ft_putstr_fd(argv[i], 1);
        if (argv[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', 1);

    shell->exit_status = 0;
    return (0);
}