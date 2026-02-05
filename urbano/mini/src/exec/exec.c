/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:57:46 by guisanto          #+#    #+#             */
/*   Updated: 2026/01/24 03:05:51 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*  Função principal de execução
	•	☐ decidir builtin vs comando externo
	•	☐ detectar pipes
	•	☐ chamar executor correto */