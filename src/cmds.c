/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:10:56 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/09 12:28:07 by abueskander      ###   ########.fr       */
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
		if (args[i + 1])
			ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		else
			if (chdir(args[i]) == -1)
				perror("minishell: cd");
	}
}

void	pwd_cmd()
{
	char	cwd[PATH_MAX + 1];
	if (getcwd(cwd, PATH_MAX))
		ft_printf("%s\n", cwd);
	else
		perror("minishell: pwd");
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
			temp = ft_strjoin(*res, " ");
		free(*res);
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
	return (EXIT_SUCCESS);
}

int	env_cmd_helper(char **res, t_env *env)
{
	char	*temp;

	temp = ft_strjoin(*res, env->name);
	free(*res);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin(*res, "=");
	free(*res);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin(*res, env->name);
	free(*res);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin(*res, "\n");
	free(*res);
	if (!temp)
		return (0);
	*res = temp;
	return (1);
}

int	env_cmd(t_op_ref *op_ref)
{
	t_list	*lst;
	char	*res;

	lst = op_ref->env_lst;
	res = ft_strdup("");
	if (!res)
		return (EXIT_FAILURE);
	while (lst)
	{
		if (!env_cmd_helper(&res, (t_env *)lst->content))
			return (EXIT_FAILURE);
		lst = lst->next;
	}
	ft_printf("%s", res);
	free(res);
	return (EXIT_SUCCESS);
}

void	unset_cmd(t_op_ref *op_ref, char **args)
{
	args++;
	while (*args)
	{
		ft_unsetenv(&op_ref->env_lst, *args);
		args++;
	}
}
