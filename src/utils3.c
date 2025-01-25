/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:21:45 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/25 17:17:41 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

long long	ft_atoll(char *nptr)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			sign = -1;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
		res = res * 10 + *(nptr++) - '0';
	return (res * sign);
}

void	recover_stdin_bak(t_minishell *mini)
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
