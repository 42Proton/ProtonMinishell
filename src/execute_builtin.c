/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:15:06 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/25 19:48:33 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_cmd_process_prep(int *fds)
{
	fds[0] = dup(STDIN_FILENO);
	if (fds[0] == -1)
		return (0);
	fds[1] = dup(STDOUT_FILENO);
	if (fds[1] == -1)
	{
		close(fds[0]);
		return (0);
	}
	return (1);
}

void	builtin_cmd_close_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

int	builtin_cmd_process_recover(int *fds)
{
	if (dup2(fds[0], STDIN_FILENO) == -1)
	{
		close(STDIN_FILENO);
		builtin_cmd_close_fds(fds);
		return (EXIT_FAILURE);
	}
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		close(STDOUT_FILENO);
		builtin_cmd_close_fds(fds);
		return (EXIT_FAILURE);
	}
	builtin_cmd_close_fds(fds);
	return (EXIT_SUCCESS);
}

int	builtin_cmd_process(t_operation **operations, size_t i, t_op_ref *op_ref)
{
	int	fds[2];
	int	status;

	if (!builtin_cmd_process_prep(fds))
		return (EXIT_FAILURE);
	if (!execute_cmd_redirections(operations[i], 0))
	{
		builtin_cmd_close_fds(fds);
		return (EXIT_FAILURE);
	}
	status = execute_inbuilt_command(op_ref, operations[i]->cmd,
			operations[i]->args);
	if (builtin_cmd_process_recover(fds) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_cmd(t_operation **ops,
	size_t i, t_op_ref *op_ref)
{
	int	status;
	int	is_child;

	status = EXIT_SUCCESS;
	is_child = 0;
	if (ops[i]->operation_type == OPERATION_PIPE
		|| (ops[i + 1]
			&& ops[i + 1]->operation_type == OPERATION_PIPE))
		is_child = 1;
	if (is_child)
		builtin_cmd_child(ops, i, op_ref);
	else
	{
		if (ft_setenv(op_ref->env_lst, "_", ops[i]->cmd) == -1)
			return (EXIT_FAILURE);
		op_ref->last_pid = -1;
		status = builtin_cmd_process(ops, i, op_ref);
	}
	return (status);
}
