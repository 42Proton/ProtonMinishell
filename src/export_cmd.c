/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:12 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/26 11:58:50 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	export_print_error(char *arg)
{
	ft_dprintf(STDERR_FILENO, "export: '%s': not a valid identifier\n",
		arg);
}

int	export_cmd_helper(t_op_ref *op_ref, char *arg)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (-1);
	if (!parse_env_data(arg, env))
	{
		free_env(env);
		return (-1);
	}
	if (!check_env_name(env->name))
	{
		export_print_error(arg);
		free_env(env);
		return (0);
	}
	if (ft_setenv(op_ref->env_lst, env->name, env->data) == -1)
	{
		free_env(env);
		return (-1);
	}
	free_env(env);
	return (1);
}

int	export_cmd(t_op_ref *op_ref, char **args)
{
	int	status;

	args++;
	if (!*args)
	{
		if (!sort_print_env(*op_ref->env_lst))
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	while (*args)
	{
		status = export_cmd_helper(op_ref, *args);
		if (status == -1)
		{
			perror("export");
			return (EXIT_FAILURE);
		}
		if (status == 0)
		{
			*op_ref->lec = 1;
			return (EXIT_SUCCESS);
		}
		args++;
	}
	return (EXIT_SUCCESS);
}
