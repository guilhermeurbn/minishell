/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:44:30 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:46:11 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_cd(t_shell *shell, char **argv)
{
	char *dir;
	char cwd[1024];
	
	if(!argv[1])
		dir = getenv("HOME");
	else if (!ft_strcmp(argv[1], "-"))
		dir = getenv("OLDPWD");
	else
		dir = argv[1];
	if (chdir(dir) != 0)
	{
		perror("cd");
		shell->exit_status = 1;
		return (1);
	}
	
	if (getcwd(cwd, sizeof(cwd)))
		update_env(shell, "PWD", cwd);
	shell->exit_status = 0;
	return (0);
}