/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_pre_wildcards.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:55:10 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/05 15:12:23 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	expander_pre_wildcards_iter(char *s, t_tok_expander *tok_exp,
		int *old_mode, t_list **quotes_range)
{
	while (s[tok_exp->split_se.end])
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
	}
	return (1);
}

static void	exp_pre_wildcards_quotes_condition(t_minishell *mini, char *s,
		t_tok_expander *tok_exp, t_list **quotes_range)
{
	exp_rm_quotes_add_tok(mini, s, tok_exp, quotes_range);
	if (check_expander_default_mode(s[tok_exp->split_se.end], tok_exp))
		tok_exp->mode = DEFAULT_MODE;
	else if (s[tok_exp->split_se.end] == '\'' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = SINGLE_QUOTE_MODE;
	else if (s[tok_exp->split_se.end] == '"' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = DOUBLE_QUOTE_MODE;
	inc_split_index(&tok_exp->split_se);
}

char	*expander_remove_quotes(t_minishell *mini, char *s,
		t_list **quotes_range)
{
	t_tok_expander	*tok_exp;
	char			*res;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	if (!tok_exp)
		return (0);
	while (s[tok_exp->split_se.end])
	{
		if (check_quotes_ex_literal(s[tok_exp->split_se.end], tok_exp))
			exp_pre_wildcards_quotes_condition(mini, s, tok_exp, quotes_range);
		else
			tok_exp->split_se.end++;
	}
	exp_rm_quotes_add_tok(mini, s, tok_exp, quotes_range);
	free(s);
	res = expander_join_subtok(mini, tok_exp, quotes_range);
	free(tok_exp);
	return (res);
}

void	check_lst_free(t_list *lst, t_list **quotes_range,
		t_tok_expander *tok_exp, t_minishell *mini)
{
	if (!lst)
	{
		ft_lstclear(quotes_range, free);
		free(tok_exp);
		exit_handler(mini, ERR_MALLOC_POSTMINI);
	}
	ft_lstadd_back(quotes_range, lst);
	free(tok_exp);
}

void	expander_pre_wildcards(t_minishell *mini, char *s,
		t_list **quotes_range)
{
	t_tok_expander	*tok_exp;
	t_list			*lst;
	int				old_mode;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	if (!tok_exp)
	{
		free(s);
		exit_handler(mini, ERR_MALLOC_POSTMINI);
	}
	old_mode = DEFAULT_MODE;
	if (!expander_pre_wildcards_iter(s, tok_exp, &old_mode, quotes_range))
	{
		free(s);
		ft_lstclear(quotes_range, free);
		free(tok_exp);
		exit_handler(mini, ERR_MALLOC_POSTMINI);
	}
	lst = ft_lstnew(0);
	if (!lst)
		free(s);
	check_lst_free(lst, quotes_range, tok_exp, mini);
}
