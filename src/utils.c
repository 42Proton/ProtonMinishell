/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:13:04 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/27 11:51:09 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*get_token_num(t_list *tokens, size_t index)
{
	size_t	i;

	i = 0;
	while (tokens)
	{
		if (i == index)
			return ((t_token *)tokens->content);
		tokens = tokens->next;
		i++;
	}
	return (0);
}

void	print_tokens(t_minishell *mini)
{
	t_list	*node;

	node = mini->line_tokens;
	while (node)
	{
		ft_printf("TYPE: %d, CONTENT: %s\n", ((t_token *)node->content)->type,
			((t_token *)node->content)->token_word);
		node = node->next;
	}
}

void	display_header(void)
{
	char	*clear_cmd;
	char	*line;
	int		fd;

	clear_cmd = tgetstr("cl", NULL);
	if (clear_cmd)
		ft_putstr_fd(clear_cmd, STDOUT_FILENO);
	fd = open("header.txt", O_RDONLY);
	if (!fd)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
		line = get_next_line(fd);
	}
}

void	line_add_newline(t_minishell *mini)
{
	char	*temp;

	temp = ft_strjoin(mini->line_read, "\n");
	if (!temp)
		exit_handler(mini, ERR_MALLOC_POSTMINI);
	free(mini->line_read);
	mini->line_read = temp;
}

int	get_redirection_type(char *token)
{
	if (!ft_strncmp(token, "<<", 2))
		return (LIMITER_REDIRECTION);
	if (!ft_strncmp(token, ">>", 2))
		return (APPEND_REDIRECTION);
	if (*token == '<')
		return (IN_REDIRECTION);
	if (*token == '>')
		return (OUT_REDIRECTION);
	return (-1);
}
