/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:08:59 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/27 14:12:34 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tokens_expander_env_iter(char *s,
	t_tok_expander *tok_exp, t_op_ref *op_ref)
{
	if (check_env_end(s, tok_exp))
	{
		if (check_if_special_exp(s, tok_exp))
			tok_exp->split_se.end++;
		if (!expander_add_tok(s, tok_exp, op_ref))
			return (0);
		if (tok_exp->mode == DOUBLE_QUOTE_ENV_MODE)
			tok_exp->mode = DOUBLE_QUOTE_MODE;
		else
			tok_exp->mode = DEFAULT_MODE;
	}
	else if (check_quotes(s[tok_exp->split_se.end]))
	{
		if (!expander_quotes_condition(s, tok_exp, op_ref))
			return (0);
	}
	else if (check_expander_env(s[tok_exp->split_se.end], tok_exp->mode))
	{
		if (!exp_env_condition(s, tok_exp, op_ref))
			return (0);
	}
	else
		tok_exp->split_se.end++;
	return (1);
}

char	*expander_add_tok_helper(char *word, t_tok_expander *tok_exp)
{
	t_split	split_se;
	char	*new_str;
	char	*new_str2;

	split_se = tok_exp->split_se;
	if ((split_se.end - split_se.start > 1 && check_env_mode(tok_exp)) || (
			split_se.end - split_se.start >= 1 && !check_env_mode(tok_exp)))
		new_str = ft_substr(word, split_se.start, split_se.end
				- split_se.start);
	else
		new_str = ft_strdup("");
	if (!new_str)
		return (0);
	if (ft_strlen(new_str) >= 2 && new_str[0] == '$'
		&& check_env_mode(tok_exp))
	{
		new_str2 = ft_strtrim(new_str, "$");
		free(new_str);
		if (!new_str2)
			return (0);
		return (new_str2);
	}
	return (new_str);
}

int	expander_add_quote_tok(char *word, t_tok_expander *tok_exp)
{
	char	*new_str;
	t_split	split_se;
	t_list	*lst;

	split_se = tok_exp->split_se;
	new_str = ft_substr(word, split_se.start, 1);
	if (!new_str)
		return (0);
	lst = ft_lstnew(new_str);
	if (!lst)
	{
		free(new_str);
		return (0);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	return (1);
}

int	expander_quotes_condition(char *s,
	t_tok_expander *tok_exp, t_op_ref *op_ref)
{
	if (!expander_add_tok(s, tok_exp, op_ref))
		return (0);
	if (check_expander_default_mode(s[tok_exp->split_se.end], tok_exp))
		tok_exp->mode = DEFAULT_MODE;
	else if (s[tok_exp->split_se.end] == '\'' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = SINGLE_QUOTE_MODE;
	else if (s[tok_exp->split_se.end] == '"' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = DOUBLE_QUOTE_MODE;
	if (!expander_add_quote_tok(s, tok_exp))
		return (0);
	inc_split_index(&tok_exp->split_se);
	return (1);
}

int	exp_env_condition(char *s, t_tok_expander *tok_exp, t_op_ref *op_ref)
{
	if (!expander_add_tok(s, tok_exp, op_ref))
		return (0);
	if (tok_exp->mode == DOUBLE_QUOTE_MODE)
		tok_exp->mode = DOUBLE_QUOTE_ENV_MODE;
	else
		tok_exp->mode = ENV_MODE;
	tok_exp->split_se.end++;
	return (1);
}
