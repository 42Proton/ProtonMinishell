/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:12 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/09 20:36:16 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parse_line(t_minishell *minishell)
{
	execute_inbuilt_command(minishell);
}

static t_minishell	*minishell_prep(char **environ)
{
	t_minishell	*mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		exit_handler(mini, ERR_MALLOC);
	mini->cwd = malloc(PATH_MAX + 1);
	if (!mini->cwd)
		exit_handler(mini, ERR_MALLOC2);
	if (*environ)
		prep_minishell_env(mini, environ);
	if (tgetent(NULL, ft_getenv(mini, "TERM")) <= 0)
		exit_handler(mini, ERR_TERM);
	return (mini);
}

static void	start_shell(t_minishell *mini)
{
	display_header();
	while (1)
	{
		mini->line_read = readline("\001\033[35m\002minishell 0x90>\001\033[33m\002 ");
		if (!mini->line_read)
			exit_handler(mini, NONE);
		if (*mini->line_read)
		{
			line_add_newline(mini);
			line_tokenizer(mini);
			if (lexical_analysis(mini))
			{
				tokens_expander(mini);
				parse_line(mini);
			}
			add_history(mini->line_read);
			ft_lstclear(&mini->line_tokens, clear_token);
			free(mini->line_read);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell	*minishell;

	minishell = minishell_prep(env);
	signal_handler();
	if (terminals_config())
		exit_handler(minishell, ERR_TERM);
	start_shell(minishell);
}
