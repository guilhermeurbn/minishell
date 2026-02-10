/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:58:30 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:36:01 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "echo", 5) ||
    !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "cd", 3) ||
    !ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "export", 7) ||
    !ft_strncmp(cmd, "unset", 6))
    	return (1);
	return (0);
}
void exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		builtin_echo(shell, cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
    	builtin_pwd(shell);
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
		builtin_env(shell);
	else if (!ft_strncmp(cmd->argv[0], "cd", 3))
		builtin_cd(shell, cmd->argv);
	/*else if (!ft_strncmp(cmd->argv[0], "exit", 5))
		builtin_exit(shell, cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		builtin_export(shell, cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		builtin_unset(shell, cmd->argv); */
		
}

static void exec_simple_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t pid;
	int status;
	char *path;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;

	path = right_path(cmd->argv[0], shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		shell->exit_status = 127;
		return ;
	}
	
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
		
	}
	if (pid == 0)
	{
		execve(path, cmd->argv, shell->env);
		perror("execve");
		_exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else
			shell->exit_status = 1;
	}
}