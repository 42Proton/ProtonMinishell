/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:08:49 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/28 17:40:39 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pre_execute_external_cmd(t_op_ref *op_ref,
	t_operation *operation)
{
	char	*cmd_path;

	if (ft_strchr(operation->cmd, '/'))
		cmd_path = ft_strdup(operation->cmd);
	else
		cmd_path = get_exec_path(op_ref, operation->cmd);
	if (!cmd_path)
		return (-1);
	if (!*cmd_path)
	{
		ft_dprintf(STDERR_FILENO,
			"%s: command not found.\n", operation->cmd);
		free(cmd_path);
		*op_ref->lec = 127;
		return (0);
	}
	if (access(cmd_path, X_OK))
	{
		perror(operation->cmd);
		free(cmd_path);
		*op_ref->lec = 126;
		return (0);
	}
	operation->cmd_path = cmd_path;
	return (1);
}

int	execute_cmd(t_op_ref *op_ref,
	t_operation *operation, t_operation *next_op)
{
	pid_t	pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (!pid)
	{
		restore_sigint();
		op_ref->is_child = 1;
		if (ft_setenv(op_ref->env_lst, "_", operation->cmd_path) == -1)
			return (EXIT_FAILURE);
		if (!execute_cmd_redirections(operation, 1))
			return (-1);
		operation->args[0] = operation->cmd;
		env = env_lst_to_2d_arr(op_ref);
		if (!env)
			return (EXIT_FAILURE);
		execve(operation->cmd_path, operation->args, env);
		free_array((void **)env);
		return (-1);
	}
	execute_cmd_end(op_ref, pid, next_op);
	return (EXIT_SUCCESS);
}

int	prep_pipeline(t_operation *operation,
	t_operation *next_op)
{
	if (next_op && next_op->operation_type == OPERATION_PIPE)
	{
		operation->pipe_fds_out = malloc(2 * sizeof(int));
		if (!operation->pipe_fds_out)
		{
			if (operation->pipe_fds_in)
				close(operation->pipe_fds_in[0]);
			return (EXIT_FAILURE);
		}
		if (pipe(operation->pipe_fds_out) == -1)
		{
			if (operation->pipe_fds_in)
				close(operation->pipe_fds_in[0]);
			return (EXIT_FAILURE);
		}
		next_op->pipe_fds_in = operation->pipe_fds_out;
	}
	return (EXIT_SUCCESS);
}

int	execute_process_circuit(t_operation *operation,
	t_op_ref *op_ref)
{
	if (op_ref->circuit_trigger)
	{
		if ((operation->operation_type == OPERATION_AND && !*op_ref->lec)
			|| (operation->operation_type == OPERATION_OR && *op_ref->lec))
			op_ref->circuit_trigger = 0;
		else
			return (1);
	}
	else
	{
		if ((operation->operation_type == OPERATION_AND && *op_ref->lec)
			|| (operation->operation_type == OPERATION_OR && !*op_ref->lec))
		{
			op_ref->circuit_trigger = 1;
			return (1);
		}
	}
	return (0);
}

void	wait_childs(t_op_ref *op_ref)
{
	int		wstatus;
	pid_t	pid;

	pid = wait(&wstatus);
	while (pid != -1)
	{
		if (pid == op_ref->last_pid)
		{
			if (WIFSIGNALED(wstatus))
			{
				*op_ref->lec = 128 + WTERMSIG(wstatus);
				op_ref->signal_term = 1;
			}
			else
				*op_ref->lec = WEXITSTATUS(wstatus);
			op_ref->last_pid = -1;
		}
		pid = wait(&wstatus);
	}
}
