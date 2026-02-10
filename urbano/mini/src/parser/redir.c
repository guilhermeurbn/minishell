/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:33:56 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:34:29 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
