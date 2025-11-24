/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scootergui <scootergui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:31 by scootergui        #+#    #+#             */
/*   Updated: 2025/11/24 18:08:33 by scootergui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void signal_handler(int sign)
{
	(void)sign;
	write(1, "\nminishell> ", 12);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
