/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scootergui <scootergui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:03 by scootergui        #+#    #+#             */
/*   Updated: 2025/11/24 18:13:20 by scootergui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_newtoken(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	ft_addtoken(t_token **list, t_token *new_token)
{
	t_token	*tmp;

	if (!*list)
		*list = new_token;
	else
	{
		tmp = *list; // testar
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}

t_token	*ft_lexer(char *input)
{
	t_token			*list;
	int				i;
	t_token_type	type;

	list = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		else if (ft_isoperator(input[i]))
		{
			type = get_operator(input, &i);
			ft_addtoken(&list, ft_newtoken(type, strdup("")));
		}
		else
			ft_addtoken(&list, ft_newtoken(WORD, read_word(input, &i)));
	}
	return (list);
}
