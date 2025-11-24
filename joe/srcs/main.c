/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scootergui <scootergui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:20 by scootergui        #+#    #+#             */
/*   Updated: 2025/11/24 18:13:52 by scootergui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

/*int main(void)
{
	char *line;

	while(1)
	{
		setup_signals();
		line = readline("minishell > ");
		if(!line)
			break;
		if(*line)
			add_history(line);
		printf("Input: %s\n", line); //debug
		free(line);
	}
	return (0);
}*/
int main()
{
    t_token *list = ft_lexer("echo hello | grep hi >> out.txt");

    t_token *tmp = list;
    while (tmp)
    {
        printf("TYPE=%d, VALUE=%s\n", tmp->type, tmp->value);
        tmp = tmp->next;
    }

    free_tokens(list);
}
/*void print_tokens(t_token *list)
{
    while (list)
    {
        printf("TYPE: %d | VALUE: %s\n", list->type, list->value);
        list = list->next;
    }
}
void print_commands(t_cmd *cmd)
{
    int i;
    int n = 1;

    while (cmd)
    {
        printf("\n===== COMMAND %d =====\n", n);
        printf("argv: ");
        if (!cmd->av)
            printf("(null)");
        else
        {
            i = 0;
            while (cmd->av[i])
            {
                printf("[%s] ", cmd->av[i]);
                i++;
            }
        }
        printf("\n");
        printf("infile: ");
        if (cmd->infile)
            printf("%s", cmd->infile);
        else
            printf("STDIN");
        printf("\n");
        printf("outfile: ");
        if (cmd->outfile)
            printf("%s", cmd->outfile);
        else
            printf("STDOUT");
        printf("\n");
        printf("append: %d\n", cmd->append);
        printf("heredoc: %d\n", cmd->heredoc);
        cmd = cmd->next;
        n++;
    }
}
int main()
{
    char input[] = "echo hello | wc >> out.txt";
    t_token *tokens = ft_lexer(input);
	print_tokens(tokens);
    t_cmd *cmds = parse_tokens(tokens);

    print_commands(cmds);
}*/

/*int main(void)
{
    t_token *list = NULL;

    ft_addtoken(&list, ft_newtoken(WORD, strdup("echo")));
    ft_addtoken(&list, ft_newtoken(WORD, strdup("hello")));
    ft_addtoken(&list, ft_newtoken(PIPE, strdup("|")));
    ft_addtoken(&list, ft_newtoken(WORD, strdup("ls")));
    ft_addtoken(&list, ft_newtoken(REDIR_OUT, strdup(">")));
    ft_addtoken(&list, ft_newtoken(WORD, strdup("file.txt")));

    print_tokens(list);

    free_tokens(list);
    return 0;
}*/
