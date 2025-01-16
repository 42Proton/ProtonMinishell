/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:48:08 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/16 18:53:44 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Written with devil in mind	DON'T READ IT OR TOUCH IT*/

static char	*token_expander_env(char *s, t_list *env_lst, int lec)
{
	t_tok_expander	*tok_exp;
	char			*res;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	if (!tok_exp)
		return (0);
	tok_exp->lec = lec;
	while (s[tok_exp->split_se.end])
	{
		if (!tokens_expander_env_iter(s, tok_exp, env_lst))
		{
			exp_clean(tok_exp);
			return (0);
		}
	}
	if (!expander_add_tok(s, tok_exp, env_lst))
	{
		exp_clean(tok_exp);
		return (0);
	}
	res = expander_join_subtok(tok_exp);
	return (res);
}

static int	expander_prep_qtr(char *exp_str, t_list *s_split_toks, t_list **split_toks)
{
	t_tok_expander	*tok_exp;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	ft_bzero(&tok_exp, sizeof(t_tok_expander));
	while (s_split_toks)
	{
		if (!expander_pre_wildcards_iter(s, tok_exp, &old_mode, quotes_range))
		{
		}
	}
	return (1);
}

static char	*expander_remove_quotes(char *s)
{
	t_tok_expander	*tok_exp;
	char			*res;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	if (!tok_exp)
		return (0);
	if (!expander_remove_quotes_iter(s, tok_exp))
	{
		exp_clean(tok_exp);
		free(s);
		return (0);
	}
	if (!exp_rm_quotes_add_tok(s, tok_exp))
	{
		exp_clean(tok_exp);
		free(s);
		return (0);
	}
	res = expander_join_subtok(tok_exp);
	free(s);
	return (res);
}

int	token_expander_helper(char *exp_str, t_list **tokens, t_list *quotes_range)
{
	t_list	*lst;

	if (check_str_wildcard(exp_str, quotes_range))
	{
		if (!expand_tok_wildcards(exp_str, tokens, quotes_range))
			return (0);
		if (!*tokens)
		{
			lst = ft_lstnew(exp_str);
			if (!lst)
				return (0);
			ft_lstadd_back(tokens, lst);
		}
		else
			free(exp_str);
	}
	else
	{
		lst = ft_lstnew(exp_str);
		if (!lst)
			return (0);
		ft_lstadd_back(tokens, lst);
	}
	return (1);
}

int	token_expander(char *s, t_list **tokens, t_op_ref *op_ref)
{
	t_list	*quotes_range;
	t_list	*s_split_toks;
	t_list	*split_toks;
	char	*exp_str;
	char	*exp_str2;

	quotes_range = 0;
	s_split_toks = 0;
	exp_str = token_expander_env(s, *op_ref->env_lst, *op_ref->lec);
	if (!exp_str)
		return (0);
	if (!token_exp_res_split(s, exp_str, &s_split_toks, op_ref))
	{
		ft_lstclear(&s_split_toks, free);
		free(exp_str);
	}
	if (!expander_pre_wildcards(exp_str, s_split_toks, &split_toks))
	{
		ft_lstclear(&s_split_toks, free);
		return (0);
	}
	exp_str2 = expander_remove_quotes(exp_str);
	if (!exp_str2)
	{
		ft_lstclear(&quotes_range, free);
		return (0);
	}
	if (!token_expander_helper(exp_str2, tokens, quotes_range))
	{
		ft_lstclear(&quotes_range, free);
		free(exp_str2);
		ft_lstclear(tokens, free);
		return (0);
	}
	ft_lstclear(&quotes_range, free);
	return (1);
}
