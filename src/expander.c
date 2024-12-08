/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:48:08 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/08 20:10:13 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef struct s_new_tok_len
{
	size_t	res;
	size_t	i;
}	t_new_tok_len;

static t_new_tok_len count_new_tok_size(char *tok_str, t_new_tok_len tok_data)
{
	
	return (tok_data);
}

static size_t	count_new_token_size(t_token *token)
{
	char			*tok_str;
	t_new_tok_len	tok_data;

	tok_str = token->token_word;
	ft_bzero(&tok_data, sizeof(t_new_tok_len));
	while (tok_str[tok_data.i])
	{
		if (tok_str[tok_data.i] == '"' || tok_str[tok_data.i] == '\''
			|| tok_str[tok_data.i] == '$')
			tok_data = count_new_tok_size(tok_str, tok_data);
		tok_data.res++;
		tok_data.i++;
	}
	return (tok_data.res);
}

void	tokens_expander(t_minishell *mini)
{
	t_list	*tokens;
	t_token	*token;

	tokens = mini->line_tokens;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		token->token_word;
		tokens = tokens->next;
	}
}
