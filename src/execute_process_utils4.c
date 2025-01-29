/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:23:50 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/29 11:28:56 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_proc_util(t_op_ref *op_ref, t_operation **ops, size_t i)
{
	int	status;

	status = exec_proc_iter(ops, op_ref, i);
	if ((ops[i]->operation_type == OPERATION_AND && *op_ref->lec)
		|| (ops[i]->operation_type == OPERATION_OR && !*op_ref->lec))
		op_ref->circuit_trigger = 1;
	if (status != 2)
	{
		wait_childs(op_ref);
		return (status);
	}
	if (ops[i + 1] && (ops[i + 1]->operation_type == OPERATION_AND
			|| ops[i + 1]->operation_type == OPERATION_OR))
		wait_childs(op_ref);
	return (status);
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

int	exec_proc_helper_util(t_operation **ops,
	size_t i, t_op_ref *op_ref)
{
	int	status;

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
	return (EXIT_SUCCESS);
}
