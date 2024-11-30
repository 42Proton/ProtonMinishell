/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:12 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/30 17:14:26 by abueskander      ###   ########.fr       */
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
	t_minishell	*minishell;
	extern char	**environ;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		exit_handler(minishell, ERR_MALLOC);
	minishell->cwd = malloc(PATH_MAX);
	if (!minishell->cwd)
		exit_handler(minishell, ERR_MALLOC2);
	if (*environ)
		prep_minishell_env(minishell, environ);
	minishell->last_exit_code = 0;
	return (minishell);
}



int	main(void)
{
	t_minishell	*minishell;

	minishell = minishell_prep();
	signal_handler();
	terminals_config();
	while (1)
	{
		minishell->line_read = readline("\e[33mminishell 0x90\e[0m> ");
		if (!minishell->line_read)
			exit_handler(minishell, NONE);
		if (*minishell->line_read)
			parse_line(minishell);
	}
}