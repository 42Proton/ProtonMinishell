/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:49:11 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/10 20:57:50 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*alloc_env(char *name, char *data)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (0);
	env->name = ft_strdup(name);
	if (!env->name)
	{
		free_env(env);
		return (0);
	}
	env->data = ft_strdup(data);
	if (!env->data)
	{
		free_env(env);
		return (0);
	}
	return (env);
}

int	ft_unsetenv(t_list **env_lst, char *name)
{
	t_list	*lst;

	if (!name)
		return (-1);
	if (!*name)
		return (-1);
	lst = *env_lst;
	while (lst)
	{
		if (!ft_strcmp(((t_env *)lst->content)->name, name))
		{
			free_env((t_env *)lst->content);
			if (lst->prev)
				lst->prev->next = lst->next;
			else
				*env_lst = lst->next;
			free(lst);
			return (0);
		}
		lst = lst->next;
	}
	return (0);
}

int	check_env_name(char *name)
{
	if (!name)
		return (0);
	if (!*name)
		return (0);
	if (*name != '_' && !ft_isalpha(*name))
		return (0);
	name++;
	while (*name)
	{
		if (*name != '_' && !ft_isalpha(*name) && !ft_isdigit(*name))
			return (0);
		name++;
	}
	return (1);
}

static void	sort_env_helper(t_list **sorted_env, t_list *new_node)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *sorted_env;
	while (tmp && ft_strcmp(((t_env *)new_node->content)->name,
			((t_env *)tmp->content)->name) > 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = new_node;
	new_node->next = tmp;
}

int	sort_env(t_list *lst, t_list **sorted_env)
{
	t_list	*node;
	t_list	*new_node;

	node = lst->next;
	while (node)
	{
		new_node = ft_lstnew(node->content);
		if (!new_node)
			return (0);
		if (ft_strcmp(((t_env *)new_node->content)->name,
				((t_env *)(*sorted_env)->content)->name) <= 0)
			ft_lstadd_front(sorted_env, new_node);
		else
			sort_env_helper(sorted_env, new_node);
		node = node->next;
	}
	return (1);
}
