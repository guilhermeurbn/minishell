/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:52:32 by guisanto          #+#    #+#             */
/*   Updated: 2026/01/24 03:04:47 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Quebrar linha em tokens
	•	☐ palavras
	•	☐ pipes
	•	☐ redirecionamentos
	•	☐ respeitar aspas (simples e duplas) */