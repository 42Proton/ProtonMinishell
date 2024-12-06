/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:58:44 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/07 01:04:25 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_type_main_conditions(char *token, int previous_type)
{
	int	type;
	
	type = COMMAND;
	if (*token == '(')
		type = OPEN_PARENTHESIS;
	else if (*token == ')')
		type = CLOSE_PARENTHESIS;
	else if (!ft_strcmp(token, "&&"))
		type = AND_OPERATOR;
	else if (!ft_strcmp(token, "||"))
		type = OR_OPERATOR;
	else if (*token == '|')
		type = PIPE;
	else if (previous_type == COMMAND || previous_type == ARGUMENT)
		type = ARGUMENT;
	return (type);
}

int	check_type(char *token, t_token *previous_token)
{
	int	type;
	int	previous_type;

	type = COMMAND;
	previous_type = -1;
	if (previous_token)
		previous_type = previous_token->type;
	if (*token == '\n')
		return (NEWLINE_TOKEN);
	if (check_redirect(token))
		type = get_redirection_type(token);
	if (type != COMMAND)
		return (type);
	type = check_type_main_conditions(token, previous_type);
	if (type != COMMAND)
		return (type);
	if (check_redirect_num(previous_type))
		type = IDENTIFIER;
	return (type);
}
