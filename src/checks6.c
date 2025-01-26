/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:32:46 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/26 19:07:58 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pre_process_check_conditions(char c, t_pre_process *data)
{
	if (c == '\'')
	{
		if (data->mode == DEFAULT_MODE)
			data->mode = SINGLE_QUOTE_MODE;
		else if (data->mode == SINGLE_QUOTE_MODE)
			data->mode = DEFAULT_MODE;
	}
	if (c == '"')
	{
		if (data->mode == DEFAULT_MODE)
			data->mode = DOUBLE_QUOTE_MODE;
		else if (data->mode == DOUBLE_QUOTE_MODE)
			data->mode = DEFAULT_MODE;
	}
	if (c == '(' && data->mode == DEFAULT_MODE)
		data->parenthesis_count++;
	if (c == ')' && data->mode == DEFAULT_MODE)
		data->parenthesis_count--;
}

int	pre_process_check(char *s)
{
	t_pre_process	data;

	data.mode = 0;
	data.parenthesis_count = 1;
	while (*s)
	{
		pre_process_check_conditions(*s, &data);
		if (!data.parenthesis_count)
			return (0);
		s++;
	}
	if (data.mode != DEFAULT_MODE || data.parenthesis_count > 1)
		return (0);
	return (1);
}

int	check_if_special_exp(char *s, t_tok_expander *tok_exp)
{
	if ((s[tok_exp->split_se.end] == '?'
			|| ft_isdigit(s[tok_exp->split_se.end]))
		&& tok_exp->split_se.end - tok_exp->split_se.start == 1)
		return (1);
	return (0);
}
