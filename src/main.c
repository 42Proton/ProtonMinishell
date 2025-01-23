/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:12 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/23 21:33:32 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signum;

static void	start_execution(t_minishell *mini)
{
	int			status;
	int			is_exit;
	t_op_ref	*op_ref;
	t_operation	**operations;

	operations = operations_prep(mini->line_tokens, 0);
	ft_lstclear(&mini->line_tokens, free_tokens);
	if (!operations)
		exit_handler(mini, ERR_MALLOC_POSTLEXER);
	op_ref = op_ref_init(operations, mini);
	if (!g_signum)
		status = execute_process(operations, op_ref, 0);
	free_operations(operations);
	is_exit = op_ref->is_exit;
	free(op_ref);
	if (status == EXIT_FAILURE)
	{
		mini->last_exit_code = -1;
		exit_handler(mini, ERR_MALLOC_POSTLEXER);
	}
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
	return (mini);
}

static void	start_shell_helper(t_minishell *mini)
{
	int	status;

	if (pre_process_check(mini->line_read))
	{
		line_tokenizer(mini);
		if (!mini->line_tokens)
		{
			mini->is_empty = 1;
			return ;
		}
		status = lexical_analysis(mini);
		if (status)
			start_execution(mini);
		else
		{
			ft_lstclear(&mini->line_tokens, free_tokens);
			mini->last_exit_code = 2;
		}
	}
	else
	{
		ft_dprintf(STDERR_FILENO,
			"Proton: syntax error, unclosed quotes/parenthesis\n");
		mini->last_exit_code = 2;
	}
}

static void	recover_stdin_bak(t_minishell *mini)
{
	if (!mini->stdin_bak)
	{
		mini->stdin_bak = dup(STDIN_FILENO);
		if (mini->stdin_bak == -1)
			exit_handler(mini, ERR_MALLOC_POSTMINI);
	}
	else
	{
		if (dup2(mini->stdin_bak, STDIN_FILENO) == -1)
		{
			close(mini->stdin_bak);
			mini->stdin_bak = -1;
			exit_handler(mini, ERR_MALLOC_POSTMINI);
		}
		close(mini->stdin_bak);
		mini->stdin_bak = dup(STDIN_FILENO);
		if (mini->stdin_bak == -1)
			exit_handler(mini, ERR_MALLOC_POSTMINI);
	}
}

static void	start_shell(t_minishell *mini)
{
	display_header(mini);
	while (1)
	{
		g_signum = 0;
		mini->curr_line++;
		recover_stdin_bak(mini);
		signal_handler(SIG_NEWPROMPT);
		mini->line_read = readline("\001\033[35m\002Proton>\001\033[33m\002");
		signal_handler(SIG_UPDATE_SIGNUM);
		if (!mini->line_read)
			exit_handler(mini, NONE);
		if (*mini->line_read && !g_signum)
			start_shell_helper(mini);
		if (!mini->is_empty)
			add_history(mini->line_read);
		free(mini->line_read);
		mini->is_empty = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	g_signum = 0;
	signal_handler(SIG_IGNORE);
	minishell = minishell_prep(env);
	if (terminals_config())
		exit_handler(NULL, ERR_TERM);
	start_shell(minishell);
}
