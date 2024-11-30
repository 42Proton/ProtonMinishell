/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:19:37 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/30 21:45:29 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_setenv_helper(t_list *lst, char *data)
{
	free(((t_env *)lst->content)->data);
	((t_env *)lst->content)->data = ft_strdup(data);
	if (!((t_env *)lst->content)->data)
		return (0);
	return (1);
}

int	ft_setenv(t_minishell *minishell, char *name, char *data)
{
	t_list	*lst;
	t_env	*env;

	lst = minishell->env_lst;
	while (lst)
	{
		if (!ft_strcmp(((t_env *)lst->content)->name, name))
		{
			if (!ft_setenv_helper(lst, data))
				return (-1);
			return (0);
		}
		lst = lst->next;
	}
	env = alloc_env(name, data);
	if (!env)
		return (-1);
	lst = ft_lstnew(env);
	if (!lst)
	{
		free_env(env);
		return (-1);
	}
	ft_lstadd_front(&minishell->env_lst, lst);
	return (0);
}

int	sort_print_env(t_minishell *minishell)
{
	t_list	*lst;
	t_list	*temp;
	t_env	*env;

	lst = ft_lstnew(minishell->env_lst->content);
	if (!lst)
		return (0);
	if (!sort_env(minishell, &lst))
	{
		free_lst(lst);
		return (0);
	}
	temp = lst;
	while (temp)
	{
		env = (t_env *)temp->content;
		ft_printf("%s=%s\n", env->name, env->data);
		temp = temp->next;
	}
	free_lst(lst);
	return (1);
}
