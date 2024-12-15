/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:33:06 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/15 04:53:31 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_expander_default_mode_basic(char c, int mode)
{
	if ((mode == SINGLE_QUOTE_MODE && c == '\'')
		|| (mode == DOUBLE_QUOTE_MODE && c == '"'))
		return (1);
	return (0);
}

int	check_if_wildcard(char c, size_t i, t_list *quotes_range)
{
	size_t	*range;

	if (c == '*')
	{
		while (quotes_range)
		{
			range = (size_t *)quotes_range->content;
			if (i >= range[0] && i <= range[1])
				return (0);
			quotes_range = quotes_range->next;
		}
		return (1);
	}
	return (0);
}

int	check_quotes_ex_literal(char c, t_tok_expander *tok_exp)
{
	if ((c == '"' && tok_exp->mode == DOUBLE_QUOTE_MODE)
		|| (c == '\'' && tok_exp->mode == SINGLE_QUOTE_MODE)
		|| (check_quotes(c) && tok_exp->mode == DEFAULT_MODE))
		return (1);
	return (0);
}
