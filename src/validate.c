/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:23:51 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/29 02:25:19 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static ssize_t	validate_tokens_parenthesis(t_minishell *mini)
{
	t_list	*tokens;
	t_token	*token;
	ssize_t	opened_parenthesis;

	tokens = mini->line_tokens;
	opened_parenthesis = 0;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == OPEN_PARENTHESIS)
			opened_parenthesis++;
		if (token->type == CLOSE_PARENTHESIS)
			opened_parenthesis--;
		if (opened_parenthesis < 0)
			return (token->index);
		tokens = tokens->next;
	}
	return (-1);
}

static ssize_t	pre_validate_tokens_helper(t_token *token, t_token *prev_token)
{
	if (check_operator_num(token->type) && !prev_token)
		return (token->index);
	if (prev_token)
	{
		if (check_sep_operators_nl(prev_token)
			&& check_sep_operators_nl(token))
			return (token->index);
		if (check_redirect_num(prev_token->type)
			&& (check_redirect_num(token->type)
				|| check_sep_operators_nl(token)))
			return (token->index);
		if (prev_token->type == OPEN_PARENTHESIS
			&& token->type == CLOSE_PARENTHESIS)
			return (token->index);
		if (prev_token->type == COMMAND || prev_token->type == ARGUMENT)
			if (token->type == OPEN_PARENTHESIS)
				return (token->index);
	}
	return (-1);
}

static ssize_t	pre_validate_tokens(t_minishell *mini)
{
	t_list	*tokens;
	t_token	*token;
	t_token	*prev_token;
	ssize_t	result;

	prev_token = 0;
	tokens = mini->line_tokens;
	while (tokens)
	{
		token = tokens->content;
		result = pre_validate_tokens_helper(token, prev_token);
		if (result != -1)
			return (result);
		tokens = tokens->next;
		prev_token = token;
	}
	return (-1);
}

int	validate_tokens(t_minishell *mini)
{
	ssize_t	result;

	result = pre_validate_tokens(mini);
	if (result != -1)
	{
		print_syntax_error(get_token_num(mini->line_tokens, result));
		return (0);
	}
	result = validate_tokens_parenthesis(mini);
	if (result != -1)
	{
		print_syntax_error(get_token_num(mini->line_tokens, result));
		return (0);
	}
	return (1);
}
