/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:12:32 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/04 04:58:52 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_if_pattern_match(t_list *lst, char *pattern,
		t_list *quotes_range)
{
	char	*tok;
	size_t	i;

	tok = (char *)lst->content;
	i = 0;
	while (pattern[i])
	{
		if (check_if_wildcard(pattern[i], i, quotes_range))
		{
			while (check_if_wildcard(pattern[i], i, quotes_range))
				i++;
			if (!pattern[i])
				break ;
			while (*tok && *tok != pattern[i])
				tok++;
		}
		if (*tok != pattern[i])
			return (0);
		tok++;
		i++;
	}
	return (1);
}

void	del_non_matching_entries(t_list **lst_entries, char *pattern,
		t_list *quotes_range)
{
	t_list	*lst_entries_ptr;
	t_list	*lst_next;
	t_list	*lst_prev;

	lst_entries_ptr = *lst_entries;
	while (lst_entries_ptr)
	{
		lst_next = lst_entries_ptr->next;
		lst_prev = lst_entries_ptr->prev;
		if (!check_if_pattern_match(lst_entries_ptr, pattern, quotes_range))
		{
			ft_lstdelone(lst_entries_ptr, free);
			if (lst_prev)
				lst_prev->next = lst_next;
			else
				*lst_entries = lst_next;
			if (lst_next)
				lst_next->prev = lst_prev;
		}
		lst_entries_ptr = lst_next;
	}
}

void	insert_sorted_entries(t_list *lst_entries_sorted, t_list **lst,
		t_list **main_lst)
{
	t_list	*lst_prev;
	t_list	*lst_next;
	t_list	*lst_last;

	lst_prev = (*lst)->prev;
	lst_next = (*lst)->next;
	ft_lstdelone(*lst, free);
	if (!lst_prev)
		*main_lst = lst_entries_sorted;
	else
		lst_prev->next = lst_entries_sorted;
	lst_last = ft_lstlast(lst_entries_sorted);
	lst_last->next = lst_next;
	if (lst_next)
		lst_next->prev = lst_last;
	*lst = lst_last;
}
