/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:38:34 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/05 02:49:08 by guisanto         ###   ########.fr       */
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

static t_cmd *cmd_new(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (cmd);
	cmd->redirs = NULL;	
	cmd->argv = NULL;
	cmd->next = NULL;
	return cmd;
}

static void cmd_add_back(t_cmd *cmd, char *word)
{
	int i;
	char **new;
	
	i = 0;
	if (cmd->argv)
		while(cmd->argv[i])
			i++;
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	if (cmd->argv)
	{
		while(cmd->argv[i])
		{
			new[i] = cmd->argv[i];
			i++;
		}
	}
	new[i++] = word;
	new[i] = NULL;
	free(cmd->argv);
	cmd->argv = new;
}
t_redir *redir_new(int type, char *file)
{
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return NULL;

	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

static void cmd_add_redir(t_cmd *cmd, t_token *token)
{
	t_redir *r;
	 
	r = redir_new(token->type, token->next->word);
	r->next = cmd->redirs;
	cmd->redirs = r;
}
static t_token *create_token(char *start, int len, t_token_type type)
{
	t_token *new;
	int i;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = malloc(len + 1);
	if (!new->word)
	{
		free(new);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new->word[i] = start[i];
		i++;
	}
	new->word[i] = '\0';
	new->type = type;
	new->next = NULL;
	return (new);
}



static void add_token(t_token **head, t_token *new)
{
	t_token *tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
static t_cmd *parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = cmd_new();
	current = cmds;
	while(tokens)
	{
		if (tokens->type == TOKEN_WORD)
			cmd_add_back(current, tokens->word);
		else if (tokens->type == TOKEN_PIPE)
		{
			current->next = cmd_new();
			current = current->next;
		}
		else
		{
			cmd_add_redir(current, tokens);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (cmds);
}


//estou separando os tokens, palavras e operadores
static t_token *lexer(t_shell *shell, char *line)
{
	t_token *tokens;
	int i;
	int start;

	(void)shell;
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break;
		
        if (line[i] == '|')
        {
            add_token(&tokens, create_token(line + i, 1, TOKEN_PIPE));
			i++;
			continue;
        }
		if (line[i] == '<')
		{
			if (line[i + 1] == '<')//no caso <<
			{
				add_token(&tokens, create_token(line + i, 2, TOKEN_HEREDOC));
				i += 2;
			}
			else
			{
				add_token(&tokens, create_token(line + i, 1, TOKEN_REDIR_IN));
				i++;
			}
			continue;
		}
		if (line[i] == '>')
		{
			if (line[i + 1] == '>')// no caso >>
			{
				add_token(&tokens, create_token(line + i, 2, TOKEN_APPEND));
				i += 2;
			}
			else
			{
				add_token(&tokens, create_token(line + i, 1, TOKEN_REDIR_OUT));
				i++;
			}
			continue;
		}
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<' && line[i] != '>')
			i++;
		add_token(&tokens, create_token(line + start, i - start, TOKEN_WORD));
	}
	
	return (tokens);
}
char *right_path(char *cmd, char **env)
{
	char	**paths;
	char	*tmp;
	char	*full;
	int		i;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (cmd);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}
int builtin_pwd(t_shell *shell)
{
	char cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		shell->exit_status = 1;
		return (1);
	}
	printf("%s\n", cwd);
	shell->exit_status = 0;
	return (0);
}
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
	/*else if (!ft_strncmp(cmd->argv[0], "env", 4))
		builtin_env(shell);
	else if (!ft_strncmp(cmd->argv[0], "cd", 3))
		builtin_cd(shell, cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
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
//             ECHO           //


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