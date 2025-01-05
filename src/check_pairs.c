/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pairs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:59:05 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/05 15:12:23 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_counter(int checks[], char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
			checks[PARANTHASES]++;
		else if (line[i] == ')' && checks[PARANTHASES])
			checks[PARANTHASES]--;
		else if (line[i] == '\'')
			checks[SINGLE_Q]++;
		else if (line[i] == '"')
			checks[DOUBLE_Q]++;
		i++;
	}
	if (checks[PARANTHASES])
		return (EXIT_FAILURE);
	if (checks[SINGLE_Q] % 2 == 1)
		return (EXIT_FAILURE);
	if (checks[DOUBLE_Q] % 2 == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_pairs(t_minishell *mini)
{
	int		*checks;

	checks = ft_calloc(3, sizeof(int));
	if (!checks)
		return (EXIT_FAILURE);
	if (check_counter(checks, mini->line_read))
	{
		ft_putstr_fd("synatx error %d", check_counter(checks, mini->line_read));
	}
	free(checks);
	return (EXIT_SUCCESS);
}
