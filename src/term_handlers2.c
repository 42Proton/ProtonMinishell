/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_handlers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:00:30 by amsaleh           #+#    #+#             */
/*   Updated: 2025/02/23 17:53:59 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	restore_child_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}

static void	clear_screen(t_minishell *mini)
{
	char	*clear_cap;

	if (mini->is_terminfo_caps_loaded)
	{
		clear_cap = tgetstr("cl", NULL);
		if (clear_cap)
			ft_printf(clear_cap);
	}
}

static int	display_header_helper(int fd)
{
	char	*line;
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		res = ft_strjoin2(res, line, STRJOIN_FA);
		if (!res)
			return (0);
		line = get_next_line(fd);
	}
	write(STDOUT_FILENO, res, ft_strlen(res));
	free(res);
	return (1);
}

void	display_header(t_minishell *mini)
{
	int		fd;
	int		res;

	fd = open("header.txt", O_RDONLY);
	clear_screen(mini);
	if (fd == -1)
		return ;
	res = display_header_helper(fd);
	close(fd);
	if (!res)
		exit_handler(mini, ERR_POSTMINI);
}
