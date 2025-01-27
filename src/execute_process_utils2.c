/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:51:29 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/27 21:22:13 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	execute_subshell(t_operation **ops,
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
		status = subshell_apply_fds(ops[i]);
		execute_cmd_close_fds(ops[i], 1);
		if (!status)
			return (EXIT_FAILURE);
		if (execute_process(ops[i]->operations, op_ref, 1) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		op_ref->is_exit = 1;
		return (EXIT_SUCCESS);
	}
	else
	{
		op_ref->last_pid = pid;
		if (ops[i + 1] && ops[i + 1]->operation_type != OPERATION_PIPE)
			op_ref->wait_childs = 1;
	}
	return (EXIT_SUCCESS);
}

static int	exec_proc_helper_prep(t_operation **ops,
	size_t i, t_op_ref *op_ref)
{
	int	status;

	status = execute_expander(op_ref, ops[i]);
	if (!status)
		return (EXIT_SUCCESS);
	if (status == -1)
		return (EXIT_FAILURE);
	if (prep_pipeline(ops[i], ops[i + 1]))
		return (EXIT_FAILURE);
	if (!create_trunc_out_files(ops[i]))
	{
		*op_ref->lec = 1;
		return (EXIT_SUCCESS);
	}
	if (!process_in_redirects(ops[i]))
	{
		*op_ref->lec = 1;
		return (EXIT_SUCCESS);
	}
	if (execute_process_circuit(ops[i], op_ref))
		return (EXIT_SUCCESS);
	return (2);
}

static int	exec_proc_helper2(t_operation **ops,
	size_t i, t_op_ref *op_ref)
{
	int	status;

	status = pre_execute_external_cmd(op_ref, ops[i]);
	if (status == -1)
		return (EXIT_FAILURE);
	if (status)
		status = execute_cmd(op_ref, ops[i], ops[i + 1]);
	if (status == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	exec_proc_cmd_dir_check(t_operation **ops,
	size_t i, t_op_ref *op_ref)
{
	if (ft_strchr(ops[i]->cmd, '/') && check_if_dir(ops[i]->cmd) == 1)
	{
		*op_ref->lec = 126;
		ft_dprintf(STDERR_FILENO,
			"Proton: %s: Is a directory\n", ops[i]->cmd);
		return (0);
	}
	return (1);
}

int	execute_process_helper(t_operation **ops,
	size_t i, t_op_ref *op_ref)
{
	int	status;

	status = exec_proc_helper_prep(ops, i, op_ref);
	if (status != 2)
		return (status);
	if (ops[i]->operations)
	{
		status = execute_subshell(ops, i, op_ref);
		return (status);
	}
	else if (ops[i]->cmd)
	{
		if (!exec_proc_cmd_dir_check(ops, i, op_ref))
			return (EXIT_SUCCESS);
		if (check_if_builtin(ops[i]->cmd))
		{
			status = builtin_cmd(ops, i, op_ref);
			return (status);
		}
		else
			if (exec_proc_helper2(ops, i, op_ref) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
