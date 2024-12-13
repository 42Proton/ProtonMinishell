/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:48:08 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/13 22:25:09 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_env_end(char *s, t_tok_expander *tok_exp)
{
	if (check_env_sep(s[tok_exp->split_se.end])
		&& tok_exp->mode == ENV_MODE)
		return (1);
	return (0);
}

static void	expand_iter_tok(t_minishell *mini, char *s, t_tok_expander *tok_exp)
{
	if (check_quotes(s[tok_exp->split_se.end]))
	{
		expander_add_tok(mini, s, tok_exp);
		if (check_expander_default_mode(s[tok_exp->split_se.end], tok_exp))
			tok_exp->mode = DEFAULT_MODE;
		if (s[tok_exp->split_se.end] == '\'')
			tok_exp->mode = SINGLE_QUOTE_MODE;
		inc_split_index(&tok_exp->split_se);
	}
	else if (check_env_end(s, tok_exp))
	{
		expander_add_tok(mini, s, tok_exp);
		tok_exp->mode = DEFAULT_MODE;
	}
	else if (check_expander_env(s[tok_exp->split_se.end], tok_exp->mode))
	{
		expander_add_tok(mini, s, tok_exp);
		if (ft_isdigit(s[tok_exp->split_se.end + 1]))
			inc_split_index(&tok_exp->split_se);
		else
			tok_exp->mode = ENV_MODE;
		inc_split_index(&tok_exp->split_se);
	}
	else
		tok_exp->split_se.end++;
}

static char	*expand_tok(t_minishell *mini, char *s)
{
	t_tok_expander	*tok_exp;
	char			*res;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	if (!tok_exp)
		exit_handler(mini, ERR_MALLOC2);
	while (s[tok_exp->split_se.end])
		expand_iter_tok(mini, s, tok_exp);
	expander_add_tok(mini, s, tok_exp);
	res = expander_join_subtok(mini, tok_exp);
	free(tok_exp);
	return (res);
}

void	tokens_expander(t_minishell *mini)
{
	t_list	*tokens;
	char	*expanded_str;

	tokens = mini->line_tokens;
	while (tokens)
	{
		expanded_str = expand_tok(mini, (char *)tokens->content);
		free(tokens->content);
		tokens->content = expanded_str;
		if (check_str_wildcard(expanded_str))
			expand_tok_wildcards(mini, &tokens, &mini->line_tokens);
		tokens = tokens->next;
	}
}
