/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:38:34 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:46:21 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *prompt_read(void)
{
     char *line;
    line = readline("minishell $> ");
        if (line && *line)
            add_history(line);
    return (line);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;
	t_token	*tokens;
	t_cmd	*cmds;
	t_cmd	*cmd;
	//int		i;

	(void)argc;
	(void)argv;
	shell.env = envp;
	shell.exit_status = 0;

	while (1)
	{
		line = prompt_read();
		if (!line)
			break ;

		tokens = lexer(&shell, line);
		cmds = parser(tokens);

		cmd = cmds;
		while (cmd)
		{
			if (is_builtin(cmd->argv[0]))
				exec_builtin(&shell, cmd);
			else
				exec_simple_cmd(&shell, cmd);
			cmd = cmd->next;
		}
		free(line);
	}
	return (shell.exit_status);
}

/* 
1. readline !
2. lexer    !
3. parser   !
4. exec simples !
5. PATH
6. builtins
7. redirecionamentos
8. pipes (pipex)
9. heredoc
10. sinais 
11. Milena
*/