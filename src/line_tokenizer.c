/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:29:59 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/31 04:37:45 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	skip_spaces_tabs(char *line)
{
	size_t	i;

	i = 0;
	while (*(line + i) == ' ' || *(line + i) == '\t')
		i++;
	return (i);
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
		tokens_split.start += skip_spaces_tabs(line + tokens_split.start);
		tokens_split.end = tokens_split.start;
		while (check_sep(line + tokens_split.end) && mode == DEFAULT_MODE)
			add_sep_tokens(mini, &tokens_split, line);
		tokens_split.start += skip_spaces_tabs(line + tokens_split.start);
		tokens_split.end = tokens_split.start;
		if (check_expander_default_mode_basic(line[tokens_split.end], mode))
			mode = DEFAULT_MODE;
		else if (line[tokens_split.end] == '\'' && mode == SINGLE_QUOTE_MODE)
			mode = SINGLE_QUOTE_MODE;
		else if (line[tokens_split.end] == '"' && mode == DOUBLE_QUOTE_MODE)
			mode = DOUBLE_QUOTE_MODE;
		if (line[tokens_split.end])
			add_token(mini, &tokens_split);
	}
}
