/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tokenizer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:09:10 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/04 00:23:36 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_sep_tokens(t_minishell *mini,
		t_tokens_split *tokens_split, char *line)
{
	tokens_split->end += check_sep(line + tokens_split->end);
	mini->line_tokenized[tokens_split->token_i] = \
	ft_substr(mini->line_read, tokens_split->start,
			tokens_split->end - tokens_split->start);
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

size_t	token_count_skip_to_end(char *line, size_t i)
{
	while (line[i])
	{
		if (line[i] == ' ' || check_sep(line + i))
			break ;
		if (line[i] == '"' || line[i] == '\'')
			i += skip_quotes(line + i);
		else
			i++;
	}
	return (i);
}

void	split_tokens(t_minishell *mini)
{
	t_tokens_split	tokens_split;
	char			*line;

	ft_bzero(&tokens_split, sizeof(t_tokens_split));
	line = mini->line_read;
	while (line[tokens_split.end])
	{
		tokens_split.start += skip_spaces(line + tokens_split.start);
		tokens_split.end = tokens_split.start;
		while (check_sep(line + tokens_split.end))
			add_sep_tokens(mini, &tokens_split, line);
		tokens_split.start += skip_spaces(line + tokens_split.start);
		tokens_split.end = tokens_split.start;
		if (line[tokens_split.end] && !check_sep(line + tokens_split.end))
		{
			split_skip_to_end(line, &tokens_split);
			mini->line_tokenized[tokens_split.token_i] = \
				ft_substr(mini->line_read, tokens_split.start,
					tokens_split.end - tokens_split.start);
			tokens_split.start = tokens_split.end;
			tokens_split.token_i++;
		}
	}
}
