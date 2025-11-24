/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scootergui <scootergui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:07:22 by scootergui        #+#    #+#             */
/*   Updated: 2025/11/24 18:13:01 by scootergui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
} t_token_type;

typedef struct s_cmd {
	char	**av;
	char	*infile;
	char	*outfile;
	int		append;
	int		heredoc;
	struct	s_cmd *next;
}t_cmd;

typedef struct s_token {
	char			*value;
	t_token_type	type;
	struct s_token	*next;
} t_token;

//main.c
//void print_tokens(t_token *list);
void print_commands(t_cmd *cmd);


//parsing.c
t_cmd	*new_cmd(void);
void	add_arg(t_cmd *cmd, char *arg);
//t_cmd *parse_tokens(t_token *token);
void	handle_operator(t_cmd	**current, t_token **token);
t_cmd *parse_tokens(t_token *token);

//lexer.c
t_token	*ft_newtoken(t_token_type type, char *value);
void	ft_addtoken(t_token **list, t_token *new_token);
void	free_tokens(t_token *list);
t_token	*ft_lexer(char *input); //testar

//signs.c
void	setup_signals(void);

//utils_lexer.c
int				ft_isspace(int space);
int				ft_isoperator(char c);
t_token_type	get_operator(char *str, int *i);
char			*read_word(char *s, int *i); //Testar

#endif
