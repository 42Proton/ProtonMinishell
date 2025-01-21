/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:10:56 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/21 12:16:06 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_cmd(t_op_ref *op_ref, char **args)
{
	size_t	i;

	i = 1;
	if (!args[i])
	{
		if (chdir(ft_getenv(*op_ref->env_lst, "HOME")) == -1)
		{
			perror("Proton: cd");
			*op_ref->lec = 1;
		}
		return ;
	}
	if (args[i + 1])
		ft_dprintf(STDERR_FILENO, "Proton: cd: too many arguments\n");
	if (args[i + 1])
		*op_ref->lec = 1;
	else
	{
		if (chdir(args[i]) == -1)
		{
			perror("Proton: cd");
			*op_ref->lec = 1;
		}
	}
	return ;
}

void	pwd_cmd(t_op_ref *op_ref)
{
	char	cwd[PATH_MAX + 1];

	if (getcwd(cwd, PATH_MAX))
		ft_printf("%s\n", cwd);
	else
	{
		perror("Proton: pwd");
		*op_ref->lec = 1;
	}
}

int	echo_cmd_helper(char **res, char **args)
{
	char	*temp;
	size_t	i;

	i = 0;
	while (args[i])
	{
		temp = ft_strjoin(*res, args[i]);
		free(*res);
		if (!temp)
			return (0);
		*res = temp;
		if (args[i + 1])
		{
			temp = ft_strjoin(*res, " ");
			free(*res);
		}
		if (!temp)
			return (0);
		*res = temp;
		args++;
	}
	return (1);
}

int	echo_cmd(char **args)
{
	int		newline;
	char	*res;

	newline = 1;
	res = ft_strdup("");
	if (!res)
		return (EXIT_FAILURE);
	if (args[1])
	{
		if (!ft_strncmp(args[1], "-n", 2))
		{
			newline = 0;
			args++;
		}
	}
	args++;
	if (!echo_cmd_helper(&res, args))
		return (EXIT_FAILURE);
	if (newline)
		ft_printf("%s\n", res);
	else
		ft_printf("%s", res);
	free(res);
	return (EXIT_SUCCESS);
}
