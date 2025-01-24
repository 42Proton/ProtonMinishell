/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:29:59 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/24 20:55:46 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	skip_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (*(line + i) == ' ')
		i++;
	return (i);
}

static void	line_tokenizer_helper(t_minishell *mini,
	char *line, t_tokens_split *tokens_split, int mode)
{
	tokens_split->start += skip_spaces(line + tokens_split->start);
	tokens_split->end = tokens_split->start;
	while (check_sep(line + tokens_split->end) && mode == DEFAULT_MODE)
		if (!add_sep_tokens(mini, tokens_split, line))
			exit_handler(mini, ERR_MALLOC_POSTMINI);
	tokens_split->start += skip_spaces(line + tokens_split->start);
	tokens_split->end = tokens_split->start;
}

void	line_tokenizer(t_minishell *mini)
{
	t_tokens_split	tokens_split;
	char			*line;
	int				mode;

	mode = DEFAULT_MODE;
	ft_bzero(&tokens_split, sizeof(t_tokens_split));
	line = mini->line_read;
	while (line[tokens_split.end])
	{
		line_tokenizer_helper(mini, line, &tokens_split, mode);
		if (check_expander_default_mode_basic(line[tokens_split.end], mode))
			mode = DEFAULT_MODE;
		else if (line[tokens_split.end] == '\'' && mode == SINGLE_QUOTE_MODE)
			mode = SINGLE_QUOTE_MODE;
		else if (line[tokens_split.end] == '"' && mode == DOUBLE_QUOTE_MODE)
			mode = DOUBLE_QUOTE_MODE;
		if (line[tokens_split.end])
			if (!add_token(mini, &tokens_split))
				exit_handler(mini, ERR_MALLOC_POSTMINI);
	}
}
