/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:16 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/26 15:26:30 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	quicksig_handle(t_minishell *mini)
{
	if (!g_signum)
		mini->unclean_mode = 0;
	signal_handler(SIG_UPDATE_SIGNUM);
	if (g_signum)
	{
		mini->last_exit_code = 130;
		free(mini->line_read);
		return (1);
	}
	return (0);
}
