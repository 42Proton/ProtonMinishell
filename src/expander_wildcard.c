/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:48:15 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/06 08:03:32 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	add_dir_entry(char *dir_name, t_list **lst)
{
	char	*temp;
	t_list	*lst_temp;

	temp = ft_strdup(dir_name);
	if (!temp)
		return (0);
	lst_temp = ft_lstnew(temp);
	if (!lst_temp)
	{
		free(temp);
		return (0);
	}
	ft_lstadd_back(lst, lst_temp);
	return (1);
}

static int	get_dir_entries(DIR *dir, char c, t_list **lst_res)
{
	struct dirent	*dir_entry;

	*lst_res = 0;
	while (1)
	{
		dir_entry = readdir(dir);
		if (!dir_entry)
			break ;
		if (dir_entry->d_name[0] == '.' && c != '.')
			continue ;
		if (!add_dir_entry(dir_entry->d_name, lst_res))
		{
			ft_lstclear(lst_res, free);
			closedir(dir);
			return (0);
		}
	}
	closedir(dir);
	return (1);
}

static void	sort_dir_entry(t_list *lst_new, t_list **lst_sorted)
{
	t_list	*lst_prev;
	t_list	*lst_sorted_ptr;

	lst_sorted_ptr = *lst_sorted;
	while (lst_sorted_ptr && ft_strcmp((char *)lst_new->content,
			(char *)lst_sorted_ptr->content) > 0)
	{
		lst_prev = lst_sorted_ptr;
		lst_sorted_ptr = lst_sorted_ptr->next;
	}
	lst_new->prev = lst_prev;
	if (lst_sorted_ptr)
	{
		lst_prev->next = lst_new;
		lst_new->next = lst_sorted_ptr;
	}
	else
		lst_prev->next = lst_new;
}

static int	sort_dir_entries(t_list *lst_entries, t_list **lst_entries_sorted)
{
	t_list	*lst_entries_ptr;
	t_list	*lst_new;

	*lst_entries_sorted = 0;
	lst_entries_ptr = lst_entries;
	while (lst_entries_ptr)
	{
		lst_new = ft_lstnew(lst_entries_ptr->content);
		if (!lst_new)
		{
			ft_lstclear(&lst_entries, free);
			free_lst(*lst_entries_sorted);
			return (0);
		}
		if (!*lst_entries_sorted)
			*lst_entries_sorted = lst_new;
		else if (ft_strcmp((char *)lst_new->content,
				(char *)(*lst_entries_sorted)->content) <= 0)
			ft_lstadd_front(lst_entries_sorted, lst_new);
		else
			sort_dir_entry(lst_new, lst_entries_sorted);
		lst_entries_ptr = lst_entries_ptr->next;
	}
	free_lst(lst_entries);
	return (1);
}

int	expand_tok_wildcards(char *pattern, t_list **main_lst,
		t_list *quotes_range)
{
	DIR		*dir;
	t_list	*lst_entries;
	t_list	*lst_entries_sorted;

	dir = opendir(".");
	if (!dir)
		return (1);
	if (!get_dir_entries(dir, *pattern, &lst_entries))
		return (0);
	if (!lst_entries)
		return (1);
	del_non_matching_entries(&lst_entries, pattern, quotes_range);
	if (!lst_entries)
		return (1);
	if (!sort_dir_entries(lst_entries, &lst_entries_sorted))
		return (0);
	ft_lstadd_back(main_lst, lst_entries_sorted);
	return (1);
}
