/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:19:37 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/10 21:06:36 by amsaleh          ###   ########.fr       */
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

int	ft_setenv(t_list **env_lst, char *name, char *data)
{
	t_list	*lst;
	t_env	*env;

	lst = *env_lst;
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
	ft_lstadd_back(env_lst, lst);
	return (0);
}

int	sort_print_env_helper2(char **res, t_env *env)
{
	char	*temp;
	
	temp = ft_strjoin(*res, env->name);
	free(*res);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin(*res, "=");
	free(*res);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin(*res, env->data);
	free(*res);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin(*res, "\n");
	free(*res);
	if (!temp)
		return (0);
	*res = temp;
	return (1);
}

int	sort_print_env_helper(t_list *new_lst, char **res)
{
	t_env	*env;

	while (new_lst)
	{
		env = (t_env *)new_lst->content;
		if (!sort_print_env_helper2(res, env))
		{
			free_lst(new_lst);
			return (0);
		}
		new_lst = new_lst->next;
	}
	free_lst(new_lst);
	return (1);
}

int	sort_print_env(t_list *lst)
{
	t_list	*new_lst;
	char	*res;

	if (!lst)
		return (EXIT_SUCCESS);
	new_lst = ft_lstnew(lst->content);
	if (!new_lst)
		return (EXIT_FAILURE);
	if (!sort_env(lst, &new_lst))
	{
		free_lst(new_lst);
		return (EXIT_FAILURE);
	}
	res = ft_strdup("");
	if (!res)
	{
		free_lst(new_lst);
		return (EXIT_FAILURE);
	}
	if (!sort_print_env_helper(new_lst, &res))
		return (EXIT_FAILURE);
	ft_printf("%s", res);
	free(res);
	return (EXIT_SUCCESS);
}
