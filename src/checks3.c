/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:31:51 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/13 22:28:07 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_env_sep(char c)
{
	if (c == ' ' || c == '*' || c == '$')
		return (1);
	return (0);
}

int	check_str_wildcard(char *s)
{
	while (*s)
	{
		if (*s == '*')
			return (1);
		s++;
	}
	return (0);
}

int	check_if_builtin(char *token)
{
	if (ft_strncmp(token, "cd", 2) == 0)
		return (1);
	if (ft_strcmp(token, "export") == 0)
		return (1);
	if (ft_strcmp(token, "unset") == 0)
		return (1);
	if (ft_strcmp(token, "pwd") == 0)
		return (1);
	if (ft_strcmp(token, "env") == 0)
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
