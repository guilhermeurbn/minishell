/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:30:13 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:33:29 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_token(t_token **head, t_token *new)
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

t_token *create_token(char *start, int len, t_token_type type)
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
