/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:13:04 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/05 19:55:50 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
