/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:45:59 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/06 22:59:04 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*lexing_token(t_list *tokens,
	t_token *prev_token, t_list **new_tokens)
{
	t_token	*token;
	t_list	*lst;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	token->type = check_type(tokens->content, prev_token);
	token->token_word = tokens->content;
	if (prev_token)
		token->index = prev_token->index + 1;
	lst = ft_lstnew(token);
	if (!lst)
	{
		free(token);
		return (0);
	}
	ft_lstadd_back(new_tokens, lst);
	return (token);
}

int	lexical_analysis(t_minishell *mini)
{
	t_list	*tokens;
	t_list	*new_tokens;
	t_token	*prev_token;

	tokens = mini->line_tokens;
	new_tokens = 0;
	prev_token = 0;
	while (tokens)
	{
		prev_token = lexing_token(tokens, prev_token, &new_tokens);
		if (!prev_token)
		{
			ft_lstclear(&new_tokens, free);
			exit_handler(mini, ERR_MALLOC2);
		}
		tokens = tokens->next;
	}
	free_lst(mini->line_tokens);
	mini->line_tokens = new_tokens;
	if (!validate_tokens(mini))
		return (0);
	print_tokens(mini);
	return (1);
}
