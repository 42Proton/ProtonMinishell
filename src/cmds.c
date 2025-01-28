/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:10:56 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/28 15:13:29 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_cmd(t_op_ref *op_ref, char **args)
{
	size_t	i;
	char	*home_ref;

	i = 1;
	if (!args[i])
	{
		home_ref = ft_getenv(*op_ref->env_lst, "HOME");
		if (!home_ref)
		{
			ft_dprintf(STDERR_FILENO, "Proton: cd: HOME not set\n");
			*op_ref->lec = 1;
			return ;
		}
		if (chdir(home_ref) == -1)
		{
			perror("Proton: cd");
			*op_ref->lec = 1;
		}
		return ;
	}
	cmd_cmd_helper(args, i, op_ref);
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

int	check_valid_flag(char *arg)
{
	size_t	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
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
	echo_iteraite_flag(&args, &newline);
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
