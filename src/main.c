/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:12 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/10 00:55:05 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	start_execution(t_minishell *mini)
{
	int			status;
	int			is_exit;
	t_op_ref	*op_ref;
	
	t_operation **operations = operations_prep(mini->line_tokens, 0);
	ft_lstclear(&mini->line_tokens, free_tokens);
	if (!operations)
		exit_handler(mini, ERR_MALLOC_POSTLEXER);
	op_ref = malloc(sizeof(t_op_ref));
	if (!op_ref)
	{
		free_operations(operations);
		exit_handler(mini, ERR_MALLOC_POSTLEXER);
	}
	op_ref->lec = &mini->last_exit_code;
	op_ref->env_lst = mini->env_lst;
	op_ref->curr_line = mini->curr_line;
	op_ref->wait_childs = 0;
	op_ref->is_exit = 0;
	status = execute_process(operations, op_ref);
	free_operations(operations);
	is_exit = op_ref->is_exit;
	free(op_ref);
	if (status == EXIT_FAILURE)
		exit_handler(mini, ERR_MALLOC_POSTLEXER);
	if (is_exit)
		exit_handler(mini, NONE);
}

static t_minishell	*minishell_prep(char **environ)
{
	t_minishell	*mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		exit_handler(mini, ERR_MALLOC_MINI);
	if (*environ)
		prep_minishell_env(mini, environ);
	if (tgetent(NULL, ft_getenv(mini->env_lst, "TERM")) <= 0)
		exit_handler(mini, ERR_TERM);
	return (mini);
}

static void	start_shell_helper(t_minishell *mini)
{
	int status;

	if (pre_process_check(mini->line_read))
	{
		line_tokenizer(mini);
		status = lexical_analysis(mini);
		if (status)
			start_execution(mini);
		else
			mini->last_exit_code = 2;
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "Proton: syntax error, unclosed quotes/parenthesis\n");
		mini->last_exit_code = 2;
	}
	add_history(mini->line_read);
	free(mini->line_read);
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
		if (*mini->line_read)
			start_shell_helper(mini);
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
