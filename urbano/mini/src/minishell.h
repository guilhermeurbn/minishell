/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:13:40 by guisanto          #+#    #+#             */
/*   Updated: 2026/01/27 03:08:28 by guisanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
#define MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "../library/pipex/pipex.h"


typedef struct s_shell
{
    char **env;
    int exit_status;    
}   t_shell;

typedef enum s_token_type
{
	TOKEN_WORD,//"palavras"
	TOKEN_PIPE,// |
	TOKEN_REDIR_IN,// >
	TOKEN_REDIR_OUT,// <
	TOKEN_APPEND,// >>
	TOKEN_HEREDOC// <<
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type    type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct	s_redir *next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir 		*redirs;
	struct s_cmd 	*next;
}	t_cmd;

#endif
