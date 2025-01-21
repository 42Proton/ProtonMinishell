/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 00:56:11 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/21 15:45:38 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tok_exp_res_split_push(t_tok_expander *tok_exp)
{
	char	*res;
	t_list	*lst;

	if (!tok_exp->lst)
		return (1);
	res = expander_join_subtok(tok_exp);
	if (!res)
	{
		ft_lstclear(&tok_exp->lst, free);
		return (0);
	}
	lst = ft_lstnew(res);
	if (!lst)
	{
		free(res);
		ft_lstclear(&tok_exp->lst, free);
		return (0);
	}
	ft_lstadd_back(tok_exp->split_tok, lst);
	return (1);
}

int	token_exp_res_split_helper3(char *s,
	t_tok_expander *tok_exp, size_t *env_len)
{
	t_list	*lst;
	char	*sub_str;

	if (tok_exp->split_se.start == tok_exp->split_se.end)
		return (1);
	sub_str = ft_substr(s, tok_exp->split_se.start,
			tok_exp->split_se.end - tok_exp->split_se.start);
	if (!sub_str)
	{
		ft_lstclear(&tok_exp->lst, free);
		return (0);
	}
	lst = ft_lstnew(sub_str);
	if (!lst)
	{
		free(sub_str);
		ft_lstclear(&tok_exp->lst, free);
		return (0);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	tok_exp_res_split_skip_env(s, tok_exp, env_len);
	tok_exp->split_se.start = tok_exp->split_se.end;
	return (1);
}

static int	token_exp_res_split_helper2(char *s, size_t env_len,
	t_tok_expander *tok_exp)
{
	if (!tok_exp_rep_split_helper2_util(s, tok_exp, env_len))
		return (0);
	while (env_len)
	{
		if (tok_exp->split_se.end <= ft_strlen(s)
			&& s[tok_exp->split_se.end] == ' ' && tok_exp->mode == DEFAULT_MODE)
		{
			if (!token_exp_res_split_helper3(s, tok_exp, &env_len))
				return (0);
			tok_exp_res_split_push(tok_exp);
		}
		else
		{
			tok_exp->split_se.end++;
			env_len--;
		}
	}
	if (!token_exp_res_split_helper3(s, tok_exp, &env_len))
		return (0);
	return (1);
}

static int	token_exp_res_split_helper(char *exp_str, t_tok_expander *tok_exp,
	t_tok_expander *tok_exp2, t_op_ref *op_ref)
{
	size_t	env_len;

	env_len = get_env_len(tok_exp->s_ref + tok_exp->split_se.end, op_ref, 0);
	tok_exp2->split_se.end += tok_exp->split_se.end
		- tok_exp->split_se.start;
	tok_exp2->mode = tok_exp->mode;
	if (env_len)
		if (!token_exp_res_split_helper2(exp_str, env_len, tok_exp2))
			return (0);
	tok_exp->split_se.end++;
	while (tok_exp->s_ref[tok_exp->split_se.end]
		&& !check_env_sep(tok_exp->s_ref[tok_exp->split_se.end]))
		tok_exp->split_se.end++;
	tok_exp->split_se.start = tok_exp->split_se.end;
	return (1);
}

int	token_exp_res_split(char *s, char *exp_str,
	t_list **split_tok, t_op_ref *op_ref)
{
	t_tok_expander	tok_exp;
	t_tok_expander	tok_exp2;
	size_t			temp;

	ft_bzero(&tok_exp, sizeof(t_tok_expander));
	ft_bzero(&tok_exp2, sizeof(t_tok_expander));
	tok_exp2.split_tok = split_tok;
	tok_exp.s_ref = s;
	temp = 0;
	while (s[tok_exp.split_se.end])
	{
		token_exp_res_split_qt(s, &tok_exp);
		if (s[tok_exp.split_se.end] == '$' && tok_exp.mode != SINGLE_QUOTE_MODE)
		{
			if (!token_exp_res_split_helper(exp_str,
					&tok_exp, &tok_exp2, op_ref))
				return (0);
		}
		else if (s[tok_exp.split_se.end])
			tok_exp.split_se.end++;
	}
	if (!tok_exp_res_split_util(exp_str, &tok_exp2, &temp))
		return (0);
	return (1);
}
