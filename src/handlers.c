/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:56:08 by abueskander       #+#    #+#             */
/*   Updated: 2024/11/28 15:45:48 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_handler(t_minishell *minishell, int error)
{
	print_error(error);
	if (error > ERR_MALLOC)
	{
		rl_clear_history();
		free(minishell->cwd);
		free(minishell->line_read);
		free(minishell);
		if (minishell->env_lst)
			ft_lstclear(&minishell->env_lst, free);
	}
	if (error != NONE)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}