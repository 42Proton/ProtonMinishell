/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 00:57:07 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/24 18:09:58 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_strlen_trunc_spaces(char *s)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
		{
			i++;
			res++;
		}
	}
	return (res);
}

static size_t	get_env_len_helper(char *s, t_op_ref *op_ref, int trunc_spaces)
{
	size_t	i;
	size_t	res;
	char	temp;
	char	*env_str;

	temp = '\0';
	if (check_env_sep(*s))
		return (0);
	i = 0;
	while (s[i] && !check_env_sep(s[i]))
		i++;
	if (s[i])
	{
		temp = s[i];
		s[i] = '\0';
	}
	env_str = ft_getenv(*(op_ref->env_lst), s);
	s[i] = temp;
	if (!env_str)
		return (0);
	if (!trunc_spaces)
		res = ft_strlen(env_str);
	else
		res = ft_strlen_trunc_spaces(env_str);
	return (res);
}

size_t	get_env_len(char *s, t_op_ref *op_ref, int trunc_spaces)
{
	char	*env_str;
	size_t	res;

	s++;
	if (*s == '?' || *s == '_')
	{
		if (*s == '?')
			res = get_digits_amount(*(op_ref->lec));
		else
		{
			env_str = ft_getenv(*(op_ref->env_lst), "_");
			if (env_str)
				res = ft_strlen(env_str);
			else
				return (0);
		}
		return (res);
	}
	res = get_env_len_helper(s, op_ref, trunc_spaces);
	return (res);
}
