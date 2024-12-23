/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:06:31 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/23 18:27:26 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expander_add_tok_helper(char *word, t_tok_expander *tok_exp)
{
	t_split	split_se;
	char	*new_str;
	char	*new_str2;

	split_se = tok_exp->split_se;
	if (split_se.end - split_se.start == 1)
		new_str = ft_strdup("");
	else
		new_str = ft_substr(word, split_se.start, split_se.end - split_se.start);
	if (!new_str)
		return (0);
	if (ft_strlen(new_str) > 2
	&& new_str[0] == '$' && new_str[1] != '?'
	&& tok_exp->mode != SINGLE_QUOTE_MODE)
	{
		new_str2 = ft_strtrim(new_str, "$");
		if (!new_str2)
			return (0);
		return (new_str2);
	}
	return (new_str);
}

void	exp_rm_quotes_add_tok(t_minishell *mini, char *word,
	t_tok_expander *tok_exp, t_list **quotes_range)
{
	char	*new_str;
	t_list	*lst;
	t_split	split_se;

	if (!check_expander_if_split(tok_exp))
		return ;
	split_se = tok_exp->split_se;
	new_str = ft_substr(word, split_se.start, split_se.end - split_se.start);
	if (!new_str)
		expander_clean_exit(mini, tok_exp, quotes_range);
	lst = ft_lstnew(new_str);
	if (!lst)
	{
		free(new_str);
		expander_clean_exit(mini, tok_exp, quotes_range);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	tok_exp->split_se.start = tok_exp->split_se.end;
}
