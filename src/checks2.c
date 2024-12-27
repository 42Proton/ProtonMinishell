/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:58:44 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/27 13:12:41 by amsaleh          ###   ########.fr       */
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

int	check_type(char *token, t_token *previous_token, t_list *lst)
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
	if (check_redirect_num(previous_type))
		return (IDENTIFIER);
	type = check_type_main_conditions(token, previous_type);
	if (type != COMMAND)
		return (type);
	if (check_tok_prev_cmd(lst))
		return (ARGUMENT);
	return (type);
}

int	check_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	check_expander_env(char c, int mode)
{
	if (c == '$' && mode != SINGLE_QUOTE_MODE)
		return (1);
	return (0);
}

int	check_expander_default_mode(char c, t_tok_expander *tok_exp)
{
	if ((tok_exp->mode == SINGLE_QUOTE_MODE && c == '\'')
		|| (tok_exp->mode == DOUBLE_QUOTE_MODE && c == '"')
		|| tok_exp->mode == ENV_MODE)
		return (1);
	return (0);
}
