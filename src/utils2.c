/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:51:13 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 22:32:37 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	op_type_to_redirection(t_list *lst)
{
	if (((t_token *)lst->content)->type == IN_REDIRECTION)
		return (REDIRECT_INFILE);
	if (((t_token *)lst->content)->type == OUT_REDIRECTION)
		return (REDIRECT_OUTFILE);
	if (((t_token *)lst->content)->type == APPEND_REDIRECTION)
		return (REDIRECT_APPEND);
	if (((t_token *)lst->content)->type == LIMITER_REDIRECTION)
		return (REDIRECT_LIMITER);
	return (-1);
}

static char	*env_join_name_data(t_env *env)
{
	char	*res;
	size_t	len;

	len = ft_strlen(env->name) + ft_strlen(env->data) + 2;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (0);
	ft_strlcat(res, env->name, len);
	ft_strlcat(res, "=", len);
	ft_strlcat(res, env->data, len);
	return (res);
}

char	**env_lst_to_2d_arr(t_op_ref *op_ref)
{
	char	**res;
	size_t	lst_size;
	size_t	i;
	t_list	*lst;

	lst_size = ft_lstsize(op_ref->env_lst);
	res = ft_calloc(lst_size + 1, sizeof(char *));
	if (!res)
		return (0);
	i = 0;
	lst = op_ref->env_lst;
	while (i < lst_size)
	{
		res[i] = env_join_name_data((t_env *)lst->content);
		if (!res[i])
		{
			free_array((void **)res);
			return (0);
		}
		i++;
		lst = lst->next;
	}
	return (res);
}
