/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scootergui <scootergui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:12:48 by scootergui        #+#    #+#             */
/*   Updated: 2026/01/21 14:44:01 by scootergui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		count;
	int		i;
	char	**new_av;

	count = 0;
	if (cmd->av)
		while (cmd->av[count])
			count++;
	new_av = malloc(sizeof(char *) * (count + 2));

	i = 0;
	while (i < count)
	{
		new_av[i] = cmd->av[i];
		i++;
	}
	new_av[count] = strdup(arg);
	new_av[count + 1] = NULL;
	free (cmd->av);
	cmd->av = new_av;
}
void	handle_operator(t_cmd	**current, t_token **token)
{
	if((*token)->type == REDIR_IN)
	{
		*token = (*token)->next;
		(*current)->infile = strdup((*token)->value);
	}
	else if((*token)->type == HEREDOC)
	{
		*token = (*token)->next;
		(*current)->heredoc = 1;
		(*current)->infile = strdup((*token)->value);
	}
	else if((*token)->type == REDIR_OUT)
	{
		*token = (*token)->next;
		(*current)->outfile = strdup((*token)->value);
		(*current)->append = 0;
	}
	else if ((*token)->type == APPEND)
	{
		*token = (*token)->next;
		(*current)->outfile = strdup((*token)->value);
		(*current)->append = 1;
	}
	else if ((*token)->type == PIPE)
	{
		(*current)->next = new_cmd();
	*current = (*current)->next;
	}
}

t_cmd	*parse_tokens(t_token *token)
{
	t_cmd *cmd_list;
	t_cmd *current;

	cmd_list = new_cmd();
	if(!cmd_list)
		return (NULL);
	current = cmd_list;
	while (token)
	{
		if (token->type == WORD)
			add_arg(current, token->value);
		else
			handle_operator(&current, &token);
		token = token->next;
	}
	return (cmd_list);
}
