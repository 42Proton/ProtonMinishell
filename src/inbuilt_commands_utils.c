/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:30 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/27 21:23:18 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_inbuilt_command(t_op_ref *op_ref,
	char *cmd, char **args)
{
	int	status;

	status = EXIT_SUCCESS;
	*op_ref->lec = 0;
	if (!ft_strcmp(cmd, "cd"))
		cd_cmd(op_ref, args);
	if (!ft_strcmp(cmd, "pwd"))
		pwd_cmd(op_ref);
	if (!ft_strcmp(cmd, "echo"))
		status = echo_cmd(args);
	if (!ft_strcmp(cmd, "env"))
		status = env_cmd(op_ref);
	if (!ft_strcmp(cmd, "unset"))
		unset_cmd(op_ref, args);
	if (!ft_strcmp(cmd, "export"))
		status = export_cmd(op_ref, args);
	if (!ft_strcmp(cmd, "exit"))
		exit_cmd(op_ref, args);
	return (status);
}

int	builtin_cmd_child(t_operation **operations,
	size_t i, t_op_ref *op_ref)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (!pid)
	{
		op_ref->is_child = 1;
		op_ref->is_exit = 1;
		if (ft_setenv(op_ref->env_lst, "_", operations[i]->cmd) == -1)
			return (EXIT_FAILURE);
		status = builtin_cmd_process(operations, i, op_ref);
		execute_cmd_close_fds(operations[i], 1);
		return (status);
	}
	else
		op_ref->last_pid = pid;
	return (EXIT_SUCCESS);
}
