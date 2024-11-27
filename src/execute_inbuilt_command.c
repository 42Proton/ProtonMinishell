/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:30 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/27 20:28:03 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



void	execute_inbuilt_command(t_minishell *minishell)
{
	char **args;

	args = ft_split(minishell->line_read, ' ');
	if (!args)
		exit_handler(minishell, ERR_MALLOC2);
	if (compare_cmd_name(args[0], "exit"))
		exit_handler(minishell, NONE);
	if (compare_cmd_name(args[0], "cd"))
		cd_cmd(args[1]);
	if (compare_cmd_name(args[0], "pwd"))
		pwd_cmd(minishell);
	if (compare_cmd_name(args[0], "echo"))
		echo_cmd(args);
	free_array((void **)args);
}
