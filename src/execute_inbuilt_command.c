/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_inbuilt_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:30 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/28 23:30:35 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_inbuilt_command(t_minishell *minishell)
{
	char **args;

	args = ft_split(minishell->line_read, ' ');
	if (!args)
		exit_handler(minishell, ERR_MALLOC2);
	if (!ft_strcmp(args[0], "exit"))
	{
		free_array((void **)args);
		exit_handler(minishell, NONE);
	}
	if (!ft_strcmp(args[0], "cd"))
		cd_cmd(minishell, args[1]);
	if (!ft_strcmp(args[0], "pwd"))
		pwd_cmd(minishell);
	if (!ft_strcmp(args[0], "echo"))
		echo_cmd(args);
	if (!ft_strcmp(args[0], "env"))
		env_cmd(minishell);
	free_array((void **)args);
}
