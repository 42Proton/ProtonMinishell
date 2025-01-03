/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:12 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/03 17:50:14 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	print_redirections(t_redirect *redirections, size_t limit)
// {
// 	size_t	i = 0;

// 	while (i < limit)
// 	{
// 		printf("REDIRECT TYPE: %d, IDENTIFIER:%s\n", redirections[i].type, redirections[i].name);
// 		i++;
// 	}
// }

// void	print_args(char **args)
// {
// 	printf("ARGS: ");
// 	if (!args)
// 	{
// 		printf("NONE\n");
// 		return ;
// 	}
// 	while (*args)
// 	{
// 		printf("%s", *args);
// 		if (args[1])
// 			printf(",");
// 		args++;
// 	}
// 	printf("\n");
// }

// void	print_test(t_operation **operations, size_t lvl)
// {
// 	size_t	i = 0;
// 	lvl++;
// 	while (operations[i])
// 	{
// 		printf("LVL:%ld, PTR:%p, TYPE:%d, CMD:%s\n", lvl, operations[i], operations[i]->operation_type, operations[i]->cmd);
// 		printf("IN REDIRECTIONS:\n");
// 		print_redirections(operations[i]->in_redirects, operations[i]->n_in);
// 		printf("OUT REDIRECTIONS:\n");
// 		print_redirections(operations[i]->out_redirects, operations[i]->n_out);
// 		print_args(operations[i]->args);
// 		if (operations[i]->operations)
// 			print_test(operations[i]->operations, lvl);
// 		i++;
// 	}
// }

static void	parse_line(t_minishell *mini)
{
	int	status;

	t_operation **operations = operations_prep(mini->line_tokens, 0);
	if (!operations)
		exit_handler(mini, ERR_MALLOC_POSTLEXER);
	mini->operations = operations;
	status = execute_process(mini);
	free_operations(operations);
	if (status == EXIT_FAILURE)
		exit_handler(mini, ERR_MALLOC_POSTLEXER);
	return ;
}

static t_minishell	*minishell_prep(char **environ)
{
	t_minishell	*mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		exit_handler(mini, ERR_MALLOC_MINI);
	mini->cwd = malloc(PATH_MAX + 1);
	if (!mini->cwd)
		exit_handler(mini, ERR_MALLOC_POSTMINI);
	if (*environ)
		prep_minishell_env(mini, environ);
	if (tgetent(NULL, ft_getenv(mini->env_lst, "TERM")) <= 0)
		exit_handler(mini, ERR_TERM);
	return (mini);
}

static void	start_shell(t_minishell *mini)
{
	display_header();
	while (1)
	{
		signal_handler();
		mini->curr_line++;
		mini->line_read = readline("\001\033[35m\0020x90>\001\033[33m\002 ");
		if (!mini->line_read)
			exit_handler(mini, NONE);
		if (*mini->line_read || check_pairs(mini))
		{				
			line_add_newline(mini);
			line_tokenizer(mini);
			tokens_expander(mini);
			if (lexical_analysis(mini))
			{
				parse_line(mini);
			}
			mini->line_read[ft_strlen(mini->line_read) - 1] = 0;
			add_history(mini->line_read);
			ft_lstclear(&mini->line_tokens, clear_token);
			free(mini->line_read);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	signal_handler();
	minishell = minishell_prep(env);
	if (terminals_config())
		exit_handler(NULL, ERR_TERM);
	start_shell(minishell);
}
