/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:06:15 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/20 16:56:43 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	inc_split_index(t_split *split_se)
{
	split_se->start++;
	split_se->end++;
}

char	*get_env_safe(t_list *env_lst, char *new_str, t_tok_expander *tok_exp)
{
	char	*res;

	if (!*new_str)
		res = ft_strdup("$");
	else if (*new_str == '?' && !new_str[1])
		res = ft_itoa(tok_exp->lec);
	else
	{
		res = ft_getenv(env_lst, new_str);
		if (!res)
			res = ft_strdup("");
		else
			res = ft_strdup(res);
	}
	free(new_str);
	return (res);
}

char	*expander_join_subtok(t_tok_expander *tok_exp)
{
	char	*res;
	char	*temp;
	t_list	*lst;

	res = ft_strdup("");
	if (!res)
	{
		ft_lstclear(&tok_exp->lst, free);
		return (0);
	}
	lst = tok_exp->lst;
	while (lst)
	{
		temp = ft_strjoin(res, (char *)lst->content);
		if (!temp)
		{
			ft_lstclear(&tok_exp->lst, free);
			return (0);
		}
		free(res);
		res = temp;
		lst = lst->next;
	}
	ft_lstclear(&tok_exp->lst, free);
	return (res);
}

int	expander_add_tok(char *word, t_tok_expander *tok_exp, t_list *env_lst)
{
	char	*new_str;
	t_list	*lst;

	if (!check_expander_if_split(tok_exp))
		return (1);
	new_str = expander_add_tok_helper(word, tok_exp);
	if (!new_str)
		return (0);
	if (check_env_mode(tok_exp))
	{
		new_str = get_env_safe(env_lst, new_str, tok_exp);
		if (!new_str)
			return (0);
	}
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
