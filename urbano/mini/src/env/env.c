/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:40:48 by guisanto          #+#    #+#             */
/*   Updated: 2026/02/07 16:41:49 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_env(t_shell *shell)
{
	int i;
	
	i = 0;

	while(shell->env[i])
	{
		if(ft_strchr(shell->env[i], '='))
		{
			ft_putendl_fd(shell->env[i], 1);
		}
		i++;
	}
	shell->exit_status = 0;
	return (0);	
}
void update_env(t_shell *shell, char *key, char *value)
{
	int i;
	int len;
	char *new;
	char **new_env;

	i = 0;
	len = ft_strlen(key);
	
	while(shell->env[i])
	{
		if(!ft_strncmp(shell->env[i], key, len) && shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin_three(key, "=", value);
			return ;
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while(shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new = ft_strjoin_three(key, "=", value);
	new_env[i++] = new;
	new_env[i] = NULL;
	shell->env = new_env;
}