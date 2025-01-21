/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:33:27 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/21 15:46:21 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_exp_res_split_qt(char *s, t_tok_expander *tok_exp)
{
	if (check_expander_default_mode(s[tok_exp->split_se.end], tok_exp))
	{
		tok_exp->split_se.end++;
		tok_exp->mode = DEFAULT_MODE;
	}
	else if (s[tok_exp->split_se.end] == '\'' && tok_exp->mode == DEFAULT_MODE)
	{
		tok_exp->split_se.end++;
		tok_exp->mode = SINGLE_QUOTE_MODE;
	}
	else if (s[tok_exp->split_se.end] == '"' && tok_exp->mode == DEFAULT_MODE)
	{
		tok_exp->split_se.end++;
		tok_exp->mode = DOUBLE_QUOTE_MODE;
	}
}

int	tok_exp_rep_split_helper2_util(char *s,
	t_tok_expander *tok_exp, size_t env_len)
{
	if (tok_exp->mode == DEFAULT_MODE)
	{
		if (s[tok_exp->split_se.end] == ' ' && env_len)
		{
			if (!token_exp_res_split_helper3(s, tok_exp, &env_len))
				return (0);
			tok_exp_res_split_push(tok_exp);
		}
		while (s[tok_exp->split_se.end] == ' ' && env_len)
		{
			if (tok_exp->split_se.start == tok_exp->split_se.end)
				inc_split_index(&tok_exp->split_se);
			else
				tok_exp->split_se.end++;
			env_len--;
		}
	}
	return (1);
}

void	tok_exp_res_split_skip_env(char *s,
	t_tok_expander *tok_exp, size_t *env_len)
{
	while (tok_exp->split_se.end <= ft_strlen(s)
		&& s[tok_exp->split_se.end] == ' ' && *env_len)
	{
		(*env_len)--;
		tok_exp->split_se.end++;
	}
}

int	tok_exp_res_split_util(char *exp_str,
	t_tok_expander *tok_exp2, size_t *temp)
{
	tok_exp2->split_se.end = ft_strlen(exp_str);
	if (!token_exp_res_split_helper3(exp_str, tok_exp2, temp))
		return (0);
	tok_exp_res_split_push(tok_exp2);
	return (1);
}
