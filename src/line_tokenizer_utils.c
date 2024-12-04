/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tokenizer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:09:10 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/04 19:14:09 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_sep_tokens(t_minishell *mini,
		t_tokens_split *tokens_split, char *line)
{
	t_list	*lst;
	char	*content;

	tokens_split->end += check_sep(line + tokens_split->end);
	content = ft_substr(mini->line_read, tokens_split->start,
			tokens_split->end - tokens_split->start);
	lst = ft_lstnew(content);
	ft_lstadd_back(&mini->line_tokens, lst);
	tokens_split->start = tokens_split->end;
	tokens_split->token_i++;
}

static size_t	skip_quotes(char *line)
{
	size_t	i;
	char	quote;

	if (!(*line == '"' || *line == '\''))
		return (0);
	i = 1;
	quote = *line;
	while (*(line + i) && *(line + i) != quote)
		i++;
	if (*(line + i) == quote)
		i++;
	return (i);
}

static void	split_skip_to_end(char *line, t_tokens_split *tokens_split)
{
	while (line[tokens_split->end])
	{
		if (line[tokens_split->end] == ' '
			|| check_sep(line + tokens_split->end))
			break ;
		if (line[tokens_split->end] == '"' || line[tokens_split->end] == '\'')
			tokens_split->end += skip_quotes(line + tokens_split->end);
		else
			tokens_split->end++;
	}
}

static void	add_token(t_minishell *mini, t_tokens_split *tokens_split)
{
	t_list	*lst;
	char	*content;

	split_skip_to_end(mini->line_read, tokens_split);
	content = ft_substr(mini->line_read, tokens_split->start,
			tokens_split->end - tokens_split->start);
	lst = ft_lstnew(content);
	ft_lstadd_back(&mini->line_tokens, lst);
	tokens_split->start = tokens_split->end;
	tokens_split->token_i++;
}
