/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:18:52 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/13 22:06:15 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_sep(char *line)
{
	if (!ft_strncmp(line, "&&", 2))
		return (2);
	if (!ft_strncmp(line, "||", 2))
		return (2);
	if (!ft_strncmp(line, "<<", 2))
		return (2);
	if (!ft_strncmp(line, ">>", 2))
		return (2);
	if (!ft_strncmp(line, "<>", 2))
		return (2);
	if (*line == '|' || *line == '(' || *line == ')')
		return (1);
	if (*line == '<' || *line == '>' || *line == '\n')
		return (1);
	return (0);
}

int	check_sep_operators_nl(char *line)
{
	if (!ft_strncmp(line, "&&", 2) || !ft_strncmp(line, "||", 2))
		return (1);
	if (*line == '|' || *line == '\n')
		return (1);
	return (0);
}

int	check_redirect(char *token)
{
	if (!ft_strncmp(token, "<<", 2))
		return (1);
	if (!ft_strncmp(token, ">>", 2))
		return (1);
	if (!ft_strncmp(token, "<>", 2))
		return (1);
	if (*token == '<' || *token == '>')
		return (1);
	return (0);
}

int	check_redirect_num(int type)
{
	if (type == IN_REDIRECTION || type == OUT_REDIRECTION)
		return (1);
	if (type == INOUT_REDIRECTION || type == LIMITER_REDIRECTION)
		return (1);
	if (type == APPEND_REDIRECTION)
		return (1);
	return (0);
}

int	check_operator_num(int type)
{
	if (type == AND_OPERATOR || type == OR_OPERATOR)
		return (1);
	if (type == PIPE)
		return (1);
	return (0);
}
