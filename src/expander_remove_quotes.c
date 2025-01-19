/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_remove_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:30:24 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/19 13:22:57 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exp_add_tok_rm_qt(char *s, t_tok_expander *tok_exp)
{
	char	*sub_s;
	t_split	split_se;
	t_list	*lst;

	split_se = tok_exp->split_se;
	if (split_se.start == split_se.end + 1)
		return (1);
	sub_s = ft_substr(s, split_se.start, (split_se.end - split_se.start) + 1);
	if (!sub_s)
		return (0);
	lst = ft_lstnew(sub_s);
	if (!lst)
	{
		free(sub_s);
		return (0);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	return (1);
}

static int	exp_rm_qt_process_qt_empty(char *s, t_list *quotes_ranges, t_tok_expander *tok_exp)
{
	t_qr	*qr;

	qr = (t_qr *)quotes_ranges->content;
	tok_exp->split_se.end = qr->arr[0] + tok_exp->quotes_iter_count * 2;
	if (qr->arr[0] != tok_exp->split_se.start)
	{
		if (!exp_add_tok_rm_qt(s, tok_exp))
		{
			ft_lstclear(&tok_exp->lst, free);
			return (0);
		}
		tok_exp->split_se.start = tok_exp->split_se.end;
	}
	tok_exp->split_se.start += 3;
	return (1);
}

static int	exp_rm_qt_process_helper(char *s, t_list *quotes_ranges, t_tok_expander *tok_exp)
{
	t_qr	*qr;

	qr = (t_qr *)quotes_ranges->content;
	if (qr->is_empty)
	{
		if (!exp_rm_qt_process_qt_empty(s, quotes_ranges, tok_exp))
			return (0);
		return (1);
	}
	tok_exp->split_se.end = (qr->arr[0] - 1) + tok_exp->quotes_iter_count * 2;
	if (!exp_add_tok_rm_qt(s, tok_exp))
	{
		ft_lstclear(&tok_exp->lst, free);
		return (0);
	}
	tok_exp->split_se.start = (qr->arr[0] + 1) + tok_exp->quotes_iter_count * 2;
	tok_exp->split_se.end = (qr->arr[1] + 1) + tok_exp->quotes_iter_count * 2;
	if (!exp_add_tok_rm_qt(s, tok_exp))
	{
		ft_lstclear(&tok_exp->lst, free);
		return (0);
	}
	tok_exp->split_se.start = tok_exp->split_se.end + 2;
	return (1);
}

char	*expander_join_subtok2(t_tok_expander *tok_exp)
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

static int	exp_rm_qt_process_lt(char *s, t_tok_expander *tok_exp)
{
	if (!s[tok_exp->split_se.start])
		return (1);
	tok_exp->split_se.end = tok_exp->split_se.start;
	while (s[tok_exp->split_se.end])
		tok_exp->split_se.end++;
	if (!exp_add_tok_rm_qt(s, tok_exp))
	{
		ft_lstclear(&tok_exp->lst, free);
		return (0);
	}
	return (1);
}

static int	exp_rm_qt_process(t_split_toks *split_toks)
{
	t_tok_expander	tok_exp;
	char			*s;
	char			*res;
	t_list			*quotes_ranges;

	ft_bzero(&tok_exp, sizeof(t_tok_expander));
	s = split_toks->str;
	quotes_ranges = split_toks->quotes_ranges;
	while (quotes_ranges)
	{
		if (!exp_rm_qt_process_helper(s, quotes_ranges, &tok_exp))
			return (0);
		tok_exp.quotes_iter_count++;
		quotes_ranges = quotes_ranges->next;
	}
	if (!exp_rm_qt_process_lt(s, &tok_exp))
		return (0);
	res = expander_join_subtok2(&tok_exp);
	if (!res)
		return (0);
	free(split_toks->str);
	split_toks->str = res;
	return (1);
}

int	exp_rm_qt(t_list *split_toks)
{
	t_list			*temp;
	t_split_toks	*split_tok;

	temp = split_toks;
	while (temp)
	{
		split_tok = (t_split_toks *)temp->content;
		if (split_tok->quotes_ranges)
		{
			if (!exp_rm_qt_process(split_tok))
			{
				ft_lstclear(&split_toks, clear_split_tok);
				return (0);
			}
		}
		temp = temp->next;
	}
	return (1);
}