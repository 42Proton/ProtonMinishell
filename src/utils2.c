/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:51:13 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/27 14:13:22 by amsaleh          ###   ########.fr       */
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

	lst_size = get_envlst_size(*op_ref->env_lst);
	res = ft_calloc(lst_size + 1, sizeof(char *));
	if (!res)
		return (0);
	i = 0;
	lst = *op_ref->env_lst;
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
		while (lst && !((t_env *)lst->content)->mode)
			lst = lst->next;
	}
	return (res);
}

char	*ft_strjoin2(char *s1, char *s2, int mode)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (mode == STRJOIN_DEF)
		return (res);
	else if (mode == STRJOIN_FS1)
		free(s1);
	else if (mode == STRJOIN_FS2)
		free(s2);
	else if (mode == STRJOIN_FA)
	{
		free(s1);
		free(s2);
	}
	return (res);
}

unsigned long long	ft_atoull(char *nptr)
{
	unsigned long long	res;

	res = 0;
	while (*nptr == 32 || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
		res = res * 10 + *(nptr++) - '0';
	return (res);
}
