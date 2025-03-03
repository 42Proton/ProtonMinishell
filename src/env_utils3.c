/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:19:37 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/27 14:11:45 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_setenv_helper(t_list *lst, char *data)
{
	free(((t_env *)lst->content)->data);
	((t_env *)lst->content)->data = ft_strdup(data);
	if (!((t_env *)lst->content)->data)
		return (0);
	((t_env *)lst->content)->mode = 1;
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
			if (data && !ft_setenv_helper(lst, data))
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

	temp = ft_strjoin2(*res, "export ", STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin2(*res, env->name, STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	if (env->mode)
		if (!sort_print_env_helper2_util(res, env))
			return (0);
	temp = ft_strjoin2(*res, "\n", STRJOIN_FS1);
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
		if (ft_strcmp(env->name, "_"))
		{
			if (!sort_print_env_helper2(res, env))
			{
				free_lst(new_lst);
				return (0);
			}
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
	write(1, res, ft_strlen(res));
	free(res);
	free_lst(new_lst);
	return (EXIT_SUCCESS);
}
