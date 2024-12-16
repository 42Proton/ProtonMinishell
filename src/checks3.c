/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:31:51 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/16 23:47:23 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_env_sep(char c)
{
	if (c == ' ' || c == '*' || c == '$' || c == '?')
		return (1);
	return (0);
}

int	check_str_wildcard(char *s)
{
	int	mode;

	mode = DEFAULT_MODE;
	while (*s)
	{
		if (check_quotes(*s))
		{
			if (check_expander_default_mode_basic(*s, mode))
				mode = DEFAULT_MODE;
			else if (*s == '\'' && mode == DEFAULT_MODE)
				mode = SINGLE_QUOTE_MODE;
			else if (*s == '"' && mode == DEFAULT_MODE)
				mode = DOUBLE_QUOTE_MODE;
		}
		if (mode == DEFAULT_MODE && *s == '*')
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

int	check_env_end(char *s, t_tok_expander *tok_exp)
{
	if (check_env_sep(s[tok_exp->split_se.end]) && tok_exp->mode == ENV_MODE)
		return (1);
	return (0);
}
