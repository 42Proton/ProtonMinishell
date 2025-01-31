/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_qtr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:49:08 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/31 22:06:52 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exp_prep_qtr_modes(char *s, size_t i,
			t_list *split_toks, t_tok_expander *tok_exp)
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

void	exp_prep_qtr_next(char **content,
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

void	exp_qtr_quit_env(t_tok_expander *tok_exp, size_t env_len)
{
	if (tok_exp->mode >= DOUBLE_QUOTE_ENV_MODE && !env_len)
	{
		if (tok_exp->mode == DOUBLE_QUOTE_ENV_MODE)
			tok_exp->mode = DOUBLE_QUOTE_MODE;
		else
			tok_exp->mode = DEFAULT_MODE;
	}
}

int	expander_qtr(char *s, t_list *split_toks,
	t_op_ref *op_ref)
{
	t_tok_expander	tok_exp;
	char			*content;
	size_t			env_len;
	size_t			i;

	tok_exp.split_tok = &split_toks;
	expander_loop_helper(&tok_exp, &env_len, &i, &content);
	while (s[i] || tok_exp.mode >= DOUBLE_QUOTE_ENV_MODE)
	{
		exp_qtr_helper(&content, &tok_exp, &split_toks, env_len);
		if (!env_len)
			env_len = exp_prep_qtr_env(s, &tok_exp, op_ref, &i);
		if (tok_exp.mode < DOUBLE_QUOTE_ENV_MODE)
			if (!exp_prep_qtr_modes(s, i, split_toks, &tok_exp))
				return (0);
		if (env_len)
			env_len--;
		if (tok_exp.mode < DOUBLE_QUOTE_ENV_MODE && s[i])
			i++;
		if (content[tok_exp.split_se.end] && !tok_exp.toggle)
			tok_exp.split_se.end++;
		tok_exp.toggle = 0;
	}
	return (1);
}
