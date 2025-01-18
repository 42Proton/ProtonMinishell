/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_qtr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:49:08 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/19 00:07:41 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	insert_quotes_range(t_list **quotes_range,
	t_tok_expander *tok_exp, int old_mode)
{
	t_list	*lst;
	t_qr	*qr;

	qr = ft_calloc(1, sizeof(t_qr));
	if (!qr)
		return (0);
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

static size_t	exp_prep_qtr_env(char *str, t_tok_expander *tok_exp,
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

static int	exp_prep_qtr_modes(char *s, size_t i, t_list *split_toks, t_tok_expander *tok_exp)
{
	int				mode;
	t_split_toks	*content;

	mode = tok_exp->mode;
	content = (t_split_toks *)split_toks->content;
	if (tok_exp->mode >= DOUBLE_QUOTE_ENV_MODE)
		return (1);
	if (check_expander_default_mode_basic(s[i], tok_exp->mode))
		tok_exp->mode = DEFAULT_MODE;
	else if (s[i] == '\'' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = SINGLE_QUOTE_MODE;
	else if (s[i] == '"' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = DOUBLE_QUOTE_MODE;
	if (mode == DEFAULT_MODE && tok_exp->mode != DEFAULT_MODE)
		tok_exp->split_se.start = tok_exp->split_se.end;
	else if (mode != DEFAULT_MODE && tok_exp->mode == DEFAULT_MODE)
		if (!insert_quotes_range(&content->quotes_ranges, tok_exp, mode))
			return (0);
	return (1);
}

static void	exp_prep_qtr_next(char **content,
	t_list **split_toks, t_tok_expander *tok_exp)
{
	if (!(*split_toks)->next)
		return ;
	*split_toks = (*split_toks)->next;
	*content = ((t_split_toks *)(*split_toks)->content)->str;
	ft_bzero(&tok_exp->split_se, sizeof(t_split));
	tok_exp->quotes_iter_count = 0;
}

int	expander_prep_qtr(t_list *s_split_toks, t_list **split_toks)
{
	t_list			*lst;
	t_split_toks	*new_split_toks;

	while (s_split_toks)
	{
		new_split_toks = ft_calloc(1, sizeof(t_split_toks));
		if (!new_split_toks)
			return (0);
		new_split_toks->str = (char *)s_split_toks->content;
		lst = ft_lstnew(new_split_toks);
		if (!lst)
		{
			free(new_split_toks);
			return (0);
		}
		ft_lstadd_back(split_toks, lst);
		s_split_toks = s_split_toks->next;
	}
	return (1);
}

static void	exp_qtr_quit_env(t_tok_expander *tok_exp, size_t env_len)
{
	if (tok_exp->mode >= DOUBLE_QUOTE_ENV_MODE && !env_len)
	{
		if (tok_exp->mode == DOUBLE_QUOTE_ENV_MODE)
			tok_exp->mode = DOUBLE_QUOTE_MODE;
		else
			tok_exp->mode = DEFAULT_MODE;
	}
}

int	expander_qtr(char *s, t_list *split_toks, t_op_ref *op_ref)
{
	t_tok_expander	tok_exp;
	char			*content;
	size_t			i;
	size_t			env_len;

	ft_bzero(&tok_exp, sizeof(t_tok_expander));
	content = ((t_split_toks *)split_toks->content)->str;
	i = 0;
	env_len = 0;
	while (s[i] || tok_exp.mode >= DOUBLE_QUOTE_ENV_MODE)
	{
		if (!content[tok_exp.split_se.end])
			exp_prep_qtr_next(&content, &split_toks, &tok_exp);
		exp_qtr_quit_env(&tok_exp, env_len);
		if (!env_len)
			env_len = exp_prep_qtr_env(s, &tok_exp, op_ref, &i);
		if (tok_exp.mode < DOUBLE_QUOTE_ENV_MODE)
			if (!exp_prep_qtr_modes(s, i, split_toks, &tok_exp))
				return (0);
		if (env_len)
			env_len--;
		if (tok_exp.mode < DOUBLE_QUOTE_ENV_MODE && s[i])
			i++;
		tok_exp.split_se.end++;
	}
	return (1);
}
