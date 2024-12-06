/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:12 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/06 14:01:10 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parse_line(t_minishell *minishell)
{
	execute_inbuilt_command(minishell);
	add_history(minishell->line_read);
	free(minishell->line_read);
}

static t_minishell	*minishell_prep(void)
{
	t_minishell	*mini;
	extern char	**environ;

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
		mini->line_read = readline("\e[33mminishell 0x90\e[0m> ");
		if (!mini->line_read)
			exit_handler(mini, NONE);
		if (*mini->line_read)
		{
			line_tokenizer(mini);
			validate_tokens(mini);
			parse_line(mini);
			//ft_printf("%s",((t_token *)mini->tokens->content)->token_word);
			//free_token_list(mini->tokens);
		}
	}
}

int	main(void)
{
	t_minishell	*minishell;

	minishell = minishell_prep();
	signal_handler();
	if (terminals_config())
		exit_handler(minishell, ERR_TERM);
	start_shell(minishell);
}
