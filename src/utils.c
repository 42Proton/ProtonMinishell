/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:13:04 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/25 16:42:58 by amsaleh          ###   ########.fr       */
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

void	display_header(t_minishell *mini)
{
	char	*clear_cap;
	char	*line;
	int		fd;

	if (mini->is_terminfo_caps_loaded)
	{
		clear_cap = tgetstr("cl", NULL);
		if (clear_cap)
			ft_putstr_fd(clear_cap, STDOUT_FILENO);
	}
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
	close(fd);
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

void	cursor_line_back(t_minishell *mini)
{
	char	*up_cap;
	char	*ll_cap;

	if (mini->is_terminfo_caps_loaded)
	{
		up_cap = tgetstr("up", NULL);
		if (up_cap)
			ft_putstr_fd(up_cap, STDOUT_FILENO);
		ll_cap = tgetstr("ll", NULL);
		if (ll_cap)
			ft_putstr_fd(ll_cap, STDOUT_FILENO);
	}
}
