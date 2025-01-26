/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:38:48 by bismail           #+#    #+#             */
/*   Updated: 2025/01/26 17:55:53 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	qr_tok_split(t_tok_expander *tok_exp, t_qr *qr)
{
	if (tok_exp->split_se.start == tok_exp->split_se.end - 1)
	{
		qr->arr[0] = tok_exp->split_se.end - (tok_exp->quotes_iter_count
				+ 1) * 2;
		qr->arr[1] = tok_exp->split_se.end - (tok_exp->quotes_iter_count
				+ 1) * 2;
		qr->is_empty = 1;
	}
	else
	{
		qr->arr[0] = tok_exp->split_se.start - tok_exp->quotes_iter_count
			* 2;
		qr->arr[1] = tok_exp->split_se.end - (tok_exp->quotes_iter_count
				+ 1) * 2;
	}
}

int	insert_quotes_range(t_list **quotes_range,
	t_tok_expander *tok_exp, int old_mode)
{
	t_list	*lst;
	t_qr	*qr;

	qr = ft_calloc(1, sizeof(t_qr));
	if (!qr)
		return (0);
	qr_tok_split(tok_exp, qr);
	if (old_mode == SINGLE_QUOTE_MODE)
		qr->is_sq = 1;
	lst = ft_lstnew(qr);
	if (!lst)
	{
		free(qr);
		return (0);
	}
	ft_lstadd_back(quotes_range, lst);
	tok_exp->quotes_iter_count++;
	return (1);
}

size_t	exp_prep_qtr_env(char *str, t_tok_expander *tok_exp,
	t_op_ref *op_ref, size_t *i)
{
	size_t	res;

	res = 0;
	if (str[*i] == '$' && tok_exp->mode < DOUBLE_QUOTE_ENV_MODE
		&& tok_exp->mode != SINGLE_QUOTE_MODE)
	{
		if (tok_exp->mode < DOUBLE_QUOTE_ENV_MODE)
		{
			if (tok_exp->mode == DOUBLE_QUOTE_MODE)
				tok_exp->mode = DOUBLE_QUOTE_ENV_MODE;
			else
				tok_exp->mode = ENV_MODE;
		}
		if (tok_exp->mode == DOUBLE_QUOTE_ENV_MODE)
			res = get_env_len(str + *i, op_ref, 0);
		else
			res = get_env_len(str + *i, op_ref, 1);
		(*i)++;
		while (str[*i] && !check_env_sep(str[*i]))
			(*i)++;
	}
	return (res);
}

void	expander_loop_helper(t_tok_expander *tok_exp,
		size_t *env_len, size_t *i)
{
	*i = 0;
	ft_bzero(tok_exp, sizeof(t_tok_expander));
	*env_len = 0;
}
