/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:12:32 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/13 22:15:41 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_if_pattern_match(t_list *lst, char *pattern)
{
	char	*tok;

	tok = (char *)lst->content;
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				break ;
			while (*tok && *tok != *pattern)
				tok++;
		}
		if (*tok != *pattern)
			return (0);
		tok++;
		pattern++;
	}
	return (1);
}

void	del_non_matching_entries(t_list **lst_entries, char *pattern)
{
	t_list	*lst_entries_ptr;
	t_list	*lst_next;
	t_list	*lst_prev;

	lst_entries_ptr = *lst_entries;
	while (lst_entries_ptr)
	{
		lst_next = lst_entries_ptr->next;
		lst_prev = lst_entries_ptr->prev;
		if (!check_if_pattern_match(lst_entries_ptr, pattern))
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

void	insert_sorted_entries(t_list *lst_entries_sorted,
	t_list **lst, t_list **main_lst)
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
	lst_next->prev = lst_last;
	*lst = lst_last;
}
