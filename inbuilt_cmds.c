/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:30 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 23:31:07 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_cmd(char *arg2)
{
	if (arg2)
	{
		if (*arg2)
			if (chdir(arg2) == -1)
				perror("minishell: cd");
	}
	else
		if (chdir(getenv("HOME")) == -1)
			perror("minishell: cd");
}

void	pwd_cmd(t_minishell *minishell)
{
	if (getcwd(minishell->cwd, PATH_MAX))
		ft_putendl_fd(minishell->cwd, 1);
	else
		perror("minishell: pwd");
}

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
	free_array((void **)args);
}
