/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:12 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 16:21:23 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	export_print_error(t_env *env)
{
	ft_dprintf(STDERR_FILENO, "export: not valid in this context: %s\n",
		env->name);
	free_env(env);
}

int	export_cmd(t_minishell *minishell, char *arg2)
{
	t_env	*env;

	if (!arg2)
	{
		sort_print_env(minishell);
		return (1);
	}
	if (!check_export_arg(arg2))
		return (1);
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (0);
	if (!parse_env_data(arg2, env))
	{
		free_env(env);
		return (0);
	}
	if (!check_env_name(env->name))
	{
		export_print_error(env);
		return (1);
	}
	ft_setenv(&minishell->env_lst, env->name, env->data);
	free_env(env);
	return (1);
}
