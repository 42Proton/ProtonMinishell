/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 07:19:29 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/06 08:27:13 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	insert_quotes_range(t_list **quotes_range,
	t_tok_expander *tok_exp, int old_mode)
{
	t_list	*lst;
	t_qr	*qr;

	if (tok_exp->split_se.start == tok_exp->split_se.end - 1)
		tok_exp->quotes_iter_count++;
	if (tok_exp->split_se.start == tok_exp->split_se.end - 1)
		return (1);
	qr = ft_calloc(1, sizeof(t_qr));
	if (!qr)
		return (0);
	qr->arr[0] = tok_exp->split_se.start - tok_exp->quotes_iter_count
		* 2;
	qr->arr[1] = tok_exp->split_se.end - (tok_exp->quotes_iter_count
			+ 1) * 2;
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
		if (!insert_quotes_range(quotes_range, tok_exp, *old_mode))
			return (0);
		tok_exp->split_se.start = tok_exp->split_se.end;
		*old_mode = DEFAULT_MODE;
	}
	return (1);
}

int	expander_pre_wildcards_iter(char *s, t_tok_expander *tok_exp,
		int *old_mode, t_list **quotes_range)
{
	if (check_quotes(s[tok_exp->split_se.end]))
	{
		if (check_expander_default_mode(s[tok_exp->split_se.end], tok_exp))
			tok_exp->mode = DEFAULT_MODE;
		else if (s[tok_exp->split_se.end] == '\''
			&& tok_exp->mode == DEFAULT_MODE)
			tok_exp->mode = SINGLE_QUOTE_MODE;
		else if (s[tok_exp->split_se.end] == '"'
			&& tok_exp->mode == DEFAULT_MODE)
			tok_exp->mode = DOUBLE_QUOTE_MODE;
		if (!expander_pre_wildcards_update(tok_exp, old_mode, quotes_range))
			return (0);
	}
	tok_exp->split_se.end++;
	return (1);
}

int	exp_rm_quotes_add_tok(char *word, t_tok_expander *tok_exp)
{
	char	*new_str;
	t_list	*lst;
	t_split	split_se;

	if (!check_expander_if_split(tok_exp))
		return (1);
	split_se = tok_exp->split_se;
	new_str = ft_substr(word, split_se.start, split_se.end - split_se.start);
	if (!new_str)
		return (0);
	lst = ft_lstnew(new_str);
	if (!lst)
	{
		free(new_str);
		return (0);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	tok_exp->split_se.start = tok_exp->split_se.end;
	return (1);
}

int	exp_pre_wildcards_quotes_condition(char *s, t_tok_expander *tok_exp)
{
	if (!exp_rm_quotes_add_tok(s, tok_exp))
		return (0);
	if (check_expander_default_mode(s[tok_exp->split_se.end], tok_exp))
		tok_exp->mode = DEFAULT_MODE;
	else if (s[tok_exp->split_se.end] == '\'' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = SINGLE_QUOTE_MODE;
	else if (s[tok_exp->split_se.end] == '"' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = DOUBLE_QUOTE_MODE;
	inc_split_index(&tok_exp->split_se);
	return (1);
}
