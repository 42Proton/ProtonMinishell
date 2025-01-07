/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:12 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 16:25:24 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	start_execution(t_minishell *mini)
{
	int		status;
	
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
		mini->line_read = readline("\001\033[35m\002ProtonShell>\001\033[33m\002");
		if (!mini->line_read)
			exit_handler(mini, NONE);
		if (*mini->line_read || check_pairs(mini))
		{
			line_tokenizer(mini);
			if (lexical_analysis(mini))
				start_execution(mini);
			add_history(mini->line_read);
			free_lst(mini->line_tokens);
			mini->line_tokens = 0;
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
