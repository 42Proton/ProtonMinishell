/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:45:59 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/05 15:10:38 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*lexing_token(t_list *tokens, t_token *prev_token,
		t_list **new_tokens, t_list *qr_lst)
{
	t_token	*token;
	t_list	*lst;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	token->type = check_type(tokens->content, prev_token, *new_tokens, qr_lst);
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
	t_list	*qr_lst;

	tokens = mini->line_tokens;
	new_tokens = 0;
	prev_token = 0;
	qr_lst = mini->quotes_range_lst;
	while (tokens)
	{
		prev_token = lexing_token(tokens, prev_token, &new_tokens, qr_lst);
		if (!prev_token)
		{
			ft_lstclear(&new_tokens, free_tokens);
			exit_handler(mini, ERR_MALLOC_POSTMINI);
		}
		tokens = tokens->next;
		while (qr_lst->content)
			qr_lst = qr_lst->next;
		qr_lst = qr_lst->next;
	}
	free_lst(mini->line_tokens);
	mini->line_tokens = new_tokens;
	if (!validate_tokens(mini))
		return (0);
	return (1);
}
