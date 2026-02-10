/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:53:03 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:33:17 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void cmd_add_redir(t_cmd *cmd, t_token *token)
{
	t_redir *r;
	 
	r = redir_new(token->type, token->next->word);
	r->next = cmd->redirs;
	cmd->redirs = r;
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
t_cmd *parser(t_token *tokens)
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