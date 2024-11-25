/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:30 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/25 23:40:15 by amsaleh          ###   ########.fr       */
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

void	echo_cmd(char **args)
{
	int	newline;
	
	newline = 1;
	if (args[1])
	{
		if (ft_strlen(args[1]) == 2)
		{
			if (!ft_strncmp(args[1], "-n", 2))
			{
				newline = 0;
				args++;
			}
		}
	}
	args++;
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		args++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
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
	if (compare_cmd_name(args[0], "echo"))
		echo_cmd(args);
	free_array((void **)args);
}
