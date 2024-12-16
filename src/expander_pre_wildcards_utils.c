/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_pre_wildcards_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 04:51:13 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/15 04:55:14 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	insert_quotes_range(t_list **quotes_range, t_tok_expander *tok_exp)
{
	t_list	*lst;
	size_t	*quotes_range_arr;

	if (tok_exp->split_se.start == tok_exp->split_se.end - 1)
	{
		tok_exp->quotes_iter_count++;
		return (1);
	}
	quotes_range_arr = malloc(2 * sizeof(size_t));
	if (!quotes_range_arr)
		return (0);
	quotes_range_arr[0] = tok_exp->split_se.start - tok_exp->quotes_iter_count
		* 2;
	quotes_range_arr[1] = tok_exp->split_se.end - (tok_exp->quotes_iter_count
			+ 1) * 2;
	lst = ft_lstnew(quotes_range_arr);
	if (!lst)
	{
		free(quotes_range_arr);
		return (0);
	}
	ft_lstadd_back(quotes_range, lst);
	tok_exp->quotes_iter_count++;
	return (1);
}

int	expander_pre_wildcards_update(t_tok_expander *tok_exp, int *old_mode,
		t_list **quotes_range)
{
	if (tok_exp->mode != DEFAULT_MODE && *old_mode == DEFAULT_MODE)
	{
		tok_exp->split_se.start = tok_exp->split_se.end;
		*old_mode = tok_exp->mode;
	}
	else if (tok_exp->mode == DEFAULT_MODE && *old_mode != DEFAULT_MODE)
	{
		if (!insert_quotes_range(quotes_range, tok_exp))
			return (0);
		tok_exp->split_se.start = tok_exp->split_se.end;
		*old_mode = DEFAULT_MODE;
	}
	return (1);
}
