/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:29:59 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/04 00:23:56 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_sep(char *line)
{
	if (!ft_strncmp(line, "&&", 2))
		return (2);
	if (!ft_strncmp(line, "||", 2))
		return (2);
	if (!ft_strncmp(line, "<<", 2))
		return (2);
	if (!ft_strncmp(line, ">>", 2))
		return (2);
	if (*line == '|' || *line == '(' || *line == ')')
		return (1);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}

size_t	skip_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (*(line + i) == ' ')
		i++;
	return (i);
}

static size_t	count_tokens(char *line)
{
	size_t	tokens_count;
	size_t	i;

	tokens_count = 0;
	i = 0;
	while (line[i])
	{
		i += skip_spaces(line + i);
		while (check_sep(line + i))
		{
			i += check_sep(line + i);
			tokens_count++;
		}
		i += skip_spaces(line + i);
		if (line[i] && !check_sep(line + i))
			tokens_count++;
		i = token_count_skip_to_end(line, i);
	}
	return (tokens_count);
}

void	line_tokenizer(t_minishell *mini)
{
	size_t	tokens_count;

	tokens_count = count_tokens(mini->line_read);
	if (!tokens_count)
		return ;
	mini->line_tokenized = ft_calloc(tokens_count + 1, sizeof(void *));
	if (!mini->line_tokenized)
		exit_handler(mini, ERR_MALLOC2);
	split_tokens(mini);
}
