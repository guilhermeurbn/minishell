/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:29:09 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:33:33 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//estou separando os tokens, palavras e operadores
t_token *lexer(t_shell *shell, char *line)
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