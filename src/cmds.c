/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:10:56 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/08 17:42:10 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_cmd(t_op_ref *op_ref, char **args)
{
	size_t	i;

	i = 1;
	if (!args[i])
	{
		if (chdir(ft_getenv(op_ref->env_lst, "HOME")) == -1)
			perror("minishell: cd");
	}
	else
	{
		i++;
		if (args[i])
			ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		else
			if (chdir(args[i - 1]) == -1)
				perror("minishell: cd");
	}
}

void	pwd_cmd(t_op_ref *op_ref)
{
	char	cwd[PATH_MAX + 1];
	if (getcwd(cwd, PATH_MAX))
		ft_printf("%s\n", cwd);
	else
		perror("minishell: pwd");
}

void	echo_cmd(char **args)
{
	int	newline;

	newline = 1;
	if (args[1])
	{
		if (!ft_strcmp(args[1], "-n"))
		{
			newline = 0;
			args++;
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

void	env_cmd(t_minishell *minishell)
{
	t_list	*lst;
	t_env	*env;

	lst = minishell->env_lst;
	while (lst)
	{
		env = (t_env *)lst->content;
		ft_printf("%s=%s\n", env->name, env->data);
		lst = lst->next;
	}
}

void	unset_cmd(t_minishell *minishell, char *name)
{
	if (!name)
	{
		ft_dprintf(STDERR_FILENO, "unset: not enough arguments\n");
		return ;
	}
	if (!check_env_name(name))
	{
		ft_dprintf(STDERR_FILENO, "unset: %s: invalid parameter name\n", name);
		return ;
	}
	ft_unsetenv(&minishell->env_lst, name);
}
