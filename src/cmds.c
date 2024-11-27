/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:10:56 by abueskander       #+#    #+#             */
/*   Updated: 2024/11/27 20:27:03 by abueskander      ###   ########.fr       */
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