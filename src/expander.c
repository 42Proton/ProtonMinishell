/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:48:08 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/05 15:12:23 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Written with devil in mind	DON'T READ IT OR TOUCH IT*/

static void	expand_iter_tok(t_minishell *mini, char *s, t_tok_expander *tok_exp)
{
	if (check_env_end(s, tok_exp))
	{
		if (s[tok_exp->split_se.end] == '?' && tok_exp->split_se.end
			- tok_exp->split_se.start == 1)
			tok_exp->split_se.end++;
		expander_add_tok(mini, s, tok_exp, 0);
		if (tok_exp->mode == DOUBLE_QUOTE_ENV_MODE)
			tok_exp->mode = DOUBLE_QUOTE_MODE;
		else
			tok_exp->mode = DEFAULT_MODE;
	}
	else if (check_quotes(s[tok_exp->split_se.end]))
		expander_quotes_condition(mini, s, tok_exp);
	else if (check_expander_env(s[tok_exp->split_se.end], tok_exp->mode))
		exp_env_condition(mini, s, tok_exp);
	else
		tok_exp->split_se.end++;
}

static char	*expand_tok(t_minishell *mini, char *s)
{
	t_tok_expander	*tok_exp;
	char			*res;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	if (!tok_exp)
		exit_handler(mini, ERR_MALLOC_POSTMINI);
	while (s[tok_exp->split_se.end])
		expand_iter_tok(mini, s, tok_exp);
	expander_add_tok(mini, s, tok_exp, 0);
	res = expander_join_subtok(mini, tok_exp, 0);
	free(tok_exp);
	return (res);
}

t_list	*tokens_expander_helper(t_minishell *mini, t_list *tokens)
{
	char	*expanded_str;
	t_list	*quotes_range;
	t_list	*lst;

	quotes_range = 0;
	expanded_str = expand_tok(mini, (char *)tokens->content);
	free(tokens->content);
	expander_pre_wildcards(mini, expanded_str, &quotes_range);
	if (!quotes_range)
	{
		lst = ft_lstnew(0);
		if (!lst)
		{
			free(expanded_str);
			exit_handler(mini, ERR_MALLOC_POSTMINI);
		}
		ft_lstadd_back(&mini->quotes_range_lst, lst);
	}
	else
		ft_lstadd_back(&mini->quotes_range_lst, quotes_range);
	tokens->content = expander_remove_quotes(mini, expanded_str,
			&quotes_range);
	return (quotes_range);
}

void	fill_empty_qr(t_minishell *mini, t_list *old_tokens, t_list *tokens)
{
	size_t	i;
	t_list	*lst;

	i = 0;
	old_tokens = old_tokens->next;
	while (old_tokens != tokens)
	{
		i++;
		old_tokens = old_tokens->next;
	}
	while (i)
	{
		lst = ft_lstnew(0);
		if (!lst)
			exit_handler(mini, ERR_MALLOC_POSTMINI);
		ft_lstadd_back(&mini->quotes_range_lst, lst);
		i--;
	}
}

void	tokens_expander(t_minishell *mini)
{
	t_list	*tokens;
	t_list	*quotes_range;
	t_list	*old_tokens;

	tokens = mini->line_tokens;
	while (tokens)
	{
		quotes_range = tokens_expander_helper(mini, tokens);
		if (check_str_wildcard(tokens->content, quotes_range))
		{
			old_tokens = tokens->prev;
			expand_tok_wildcards(mini, &tokens, &mini->line_tokens,
				quotes_range);
			fill_empty_qr(mini, old_tokens, tokens);
		}
		tokens = tokens->next;
	}
}
