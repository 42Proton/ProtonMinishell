/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:48:08 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/31 22:32:31 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Written with devil in mind	DON'T READ IT OR TOUCH IT*/

static char	*token_expander_env(char *s, t_op_ref *op_ref)
{
	t_tok_expander	tok_exp;
	char			*res;

	ft_bzero(&tok_exp, sizeof(t_tok_expander));
	tok_exp.lec = *op_ref->lec;
	while (s[tok_exp.split_se.end])
	{
		if (!tokens_expander_env_iter(s, &tok_exp, op_ref))
		{
			ft_lstclear(&tok_exp.lst, free);
			return (0);
		}
	}
	if (!expander_add_tok(s, &tok_exp, op_ref))
	{
		ft_lstclear(&tok_exp.lst, free);
		return (0);
	}
	res = expander_join_subtok(&tok_exp);
	return (res);
}

int	token_exp_helper_wildcards(char *exp_str,
		t_list **tokens, t_list *quotes_range)
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

static int	prep_tok_exp(char *s, char *exp_str,
	t_list **split_toks, t_op_ref *op_ref)
{
	t_list	*s_split_toks;

	s_split_toks = 0;
	*split_toks = 0;
	if (!token_exp_res_split(s, exp_str, &s_split_toks, op_ref))
	{
		ft_lstclear(&s_split_toks, free);
		free(exp_str);
		return (0);
	}
	free(exp_str);
	if (!s_split_toks)
		return (2);
	if (!expander_prep_qtr(s_split_toks, split_toks))
	{
		ft_lstclear(&s_split_toks, free);
		ft_lstclear(split_toks, free);
		return (0);
	}
	free_lst(s_split_toks);
	if (!token_expander_helper2(split_toks, op_ref, s))
		return (0);
	return (1);
}

static int	token_exp_helper(char *s, t_list **tokens,
	t_list **split_toks, t_op_ref *op_ref)
{
	char	*exp_str;
	int		status;
	t_list	*lst;

	exp_str = token_expander_env(s, op_ref);
	if (!exp_str)
		return (0);
	status = prep_tok_exp(s, exp_str, split_toks, op_ref);
	if (!status)
		return (0);
	if (status == 2)
	{
		lst = ft_lstnew(0);
		if (!lst)
			return (0);
		ft_lstadd_back(tokens, lst);
		return (2);
	}
	if (!exp_rm_qt(*split_toks))
		return (0);
	return (1);
}

int	token_expander(char *s, t_list **tokens, t_op_ref *op_ref)
{
	t_list			*split_toks;
	t_list			*temp;
	t_list			*res_toks;
	t_split_toks	*split_tok;
	int				status;

	res_toks = 0;
	status = token_exp_helper(s, tokens, &split_toks, op_ref);
	if (status != 1)
		return (status);
	temp = split_toks;
	while (temp)
	{
		split_tok = (t_split_toks *)temp->content;
		if (!token_exp_helper_wildcards(split_tok->str,
				&res_toks, split_tok->quotes_ranges))
			token_expander_helper(split_toks, res_toks, tokens);
		ft_lstadd_back(tokens, res_toks);
		res_toks = 0;
		temp = temp->next;
	}
	ft_lstclear(&split_toks, clear_split_tok2);
	return (1);
}
