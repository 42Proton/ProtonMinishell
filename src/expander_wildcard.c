/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:48:15 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/12 02:18:44 by amsaleh          ###   ########.fr       */
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
			break;
		if (dir_entry->d_name[0] == '.' && c != '.')
			continue;
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

static int	sort_dir_entry(t_list *lst_new, t_list *lst_sorted)
{
	int	check;

	check = 0;
	while (lst_sorted)
	{
		lst_sorted = lst_sorted->next;
	}
}

static int	sort_dir_entries(t_list *lst_entries, t_list **lst_entries_sorted)
{
	t_list	*lst_sorted;
	t_list	*lst_entries_ptr;
	t_list	*lst_new;
	
	lst_entries_ptr = lst_entries;
	while (lst_entries_ptr)
	{
		lst_new = ft_lstnew(lst_entries->content);
		if (!lst_new)
		{
			ft_lstclear(&lst_entries, free);
			free_lst(*lst_entries_sorted);
			return (0);
		}
		lst_sorted = *lst_entries_sorted;
		sort_dir_entry(lst_new, lst_sorted);
		lst_entries_ptr = lst_entries_ptr->next;
	}
	return (1);
}

void	expand_tok_wildcards(t_minishell *mini, t_list *lst)
{
	DIR		*dir;
	t_list	*lst_entries;
	t_list	*lst_entries_sorted;
	
	dir = opendir(".");
	if (!dir)
		return ;
	if (!get_dir_entries(dir, *(char *)lst->content, &lst_entries))
		exit_handler(mini, ERR_MALLOC2);
	if (!lst_entries)
		return ;
	if (!sort_dir_entries(lst_entries, &lst_entries_sorted))
		exit_handler(mini, ERR_MALLOC2);
	free_lst(lst_entries);
	return ;
}
