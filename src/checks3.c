/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:31:51 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/24 18:03:08 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_env_sep(char c)
{
	if ((c >= 0x20 && c <= 0x2F) || (c >= 0x3A && c <= 0x40)
		|| (c >= 0x5B && c <= 0x5E) || (c == 0x60)
		|| (c >= 0x7B && c <= 0x7E))
		return (1);
	return (0);
}

int	check_str_wildcard(char *s, t_list *quotes_range)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
		{
			if (check_if_wildcard(s[i], i, quotes_range))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_builtin(char *token)
{
	if (!ft_strcmp(token, "exit"))
		return (1);
	if (!ft_strcmp(token, "cd"))
		return (1);
	if (!ft_strcmp(token, "export"))
		return (1);
	if (!ft_strcmp(token, "unset"))
		return (1);
	if (!ft_strcmp(token, "pwd"))
		return (1);
	if (!ft_strcmp(token, "env"))
		return (1);
	if (!ft_strcmp(token, "echo"))
		return (1);
	return (0);
}

int	check_expander_if_split(t_tok_expander *tok_exp)
{
	if (tok_exp->split_se.start == tok_exp->split_se.end
		&& tok_exp->mode != ENV_MODE)
		return (0);
	return (1);
}

int	check_env_end(char *s, t_tok_expander *tok_exp)
{
	if ((check_env_sep(s[tok_exp->split_se.end])) && check_env_mode(tok_exp))
		return (1);
	return (0);
}
