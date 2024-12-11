/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:28 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/10 14:55:10 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	inc_split_index(t_split *split_se)
{
	split_se->start += 1;
	split_se->end += 1;
}

void	expander_clean_exit(t_minishell *mini, t_tok_expander *tok_exp)
{
	ft_lstclear(&tok_exp->lst, free);
	free(tok_exp);
	exit_handler(mini, ERR_MALLOC2);
}

char	*get_env_safe(t_minishell *mini, char *new_str)
{
	char *res;

	if (!*new_str)
	{
		free(new_str);
		res = ft_strdup("$");
		return (res);
	}
	res = ft_getenv(mini, new_str);
	free(new_str);
	if (!res)
		res = ft_strdup("");
	else
		res = ft_strdup(res);
	return (res);	
}

void	expander_add_tok(t_minishell *mini,
	char *word, t_tok_expander *tok_exp)
{
	char	*new_str;
	t_split	split_se;
	t_list	*lst;

	if (tok_exp->split_se.start == tok_exp->split_se.end && tok_exp->mode != ENV_MODE)
		return ;
	split_se = tok_exp->split_se;
	new_str = ft_substr(word, split_se.start,
		split_se.end - split_se.start);
	if (!new_str)
		expander_clean_exit(mini, tok_exp);
	if (tok_exp->mode == ENV_MODE)
	{
		new_str = get_env_safe(mini, new_str);
		if (!new_str)
			expander_clean_exit(mini, tok_exp);
	}
	lst = ft_lstnew(new_str);
	if (!lst)
	{
		free(new_str);
		expander_clean_exit(mini, tok_exp);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	tok_exp->split_se.start = tok_exp->split_se.end;
}

char	*expander_join_subtok(t_minishell *mini, t_tok_expander *tok_exp)
{
	char	*res;
	char	*temp;
	t_list	*lst;

	res = ft_strdup("");
	if (!res)
		exit_handler(mini, ERR_MALLOC2);
	lst = tok_exp->lst;
	while (lst)
	{
		temp = ft_strjoin(res, (char *)lst->content);
		free(res);
		res = temp;
		lst = lst->next;
	}
	ft_lstclear(&tok_exp->lst, free);
	return (res);
}