/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:18:52 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/29 02:26:46 by amsaleh          ###   ########.fr       */
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
	if (*line == '|' || *line == '(' || *line == ')')
		return (1);
	if (*line == '<' || *line == '>' || *line == '\n')
		return (1);
	return (0);
}

int	check_sep_operators_nl(t_token *tok)
{
	int	tok_type;
	
	tok_type = tok->type;
	if (tok_type == AND_OPERATOR || tok_type == OR_OPERATOR)
		return (1);
	if (tok_type == PIPE || tok_type == NEWLINE_TOKEN)
		return (1);
	return (0);
}

int	check_redirect(char *token)
{
	if (!ft_strncmp(token, "<<", 2))
		return (1);
	if (!ft_strncmp(token, ">>", 2))
		return (1);
	if (*token == '<' || *token == '>')
		return (1);
	return (0);
}

int	check_redirect_num(int type)
{
	if (type == IN_REDIRECTION || type == OUT_REDIRECTION)
		return (1);
	if (type == APPEND_REDIRECTION || type == LIMITER_REDIRECTION)
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
