/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pairs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coderx64 <coderx64@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:59:05 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/27 08:30:43 by coderx64         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_counter(int checks[], char *line)
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
	char	*lmao;
	char	*temp;

	checks = ft_calloc(3, sizeof(int));
	if (!checks)
		return (EXIT_FAILURE);
	if (check_counter(checks, mini->line_read))
	{
		lmao = readline(">");
		if (!lmao)
		{
			free(checks);
			exit_handler(mini, NONE);
		}
		temp = ft_strjoin(mini->line_read, lmao);
		free(mini->line_read);
		mini->line_read = temp;
		check_pairs(mini);
		free(lmao);
	}
	free(checks);
	return (EXIT_SUCCESS);
}
