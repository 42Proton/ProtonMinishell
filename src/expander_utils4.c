/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 07:40:52 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/06 08:27:30 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expander_remove_quotes_iter(char *s, t_tok_expander *tok_exp)
{
	while (s[tok_exp->split_se.end])
	{
		if (check_quotes_ex_literal(s[tok_exp->split_se.end], tok_exp))
		{
			if (!exp_pre_wildcards_quotes_condition(s, tok_exp))
				return (0);
		}
		else
			tok_exp->split_se.end++;
	}
	return (1);
}
