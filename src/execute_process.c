/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:10:52 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/15 04:27:01 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	prep_redirections_helper2(t_operation *operation, char *line)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(operation->heredoc_buffer, line);
	if (!tmp)
		return (0);
	free(operation->heredoc_buffer);
	operation->heredoc_buffer = tmp;
	tmp2 = ft_strjoin(operation->heredoc_buffer, "\n");
	if (!tmp2)
		return (0);
	free(operation->heredoc_buffer);
	operation->heredoc_buffer = tmp2;
	return (1);
}

int	prep_redirections_helper(t_op_ref *op_ref, t_operation *operation, size_t j)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (j == operation->n_in - 1 && !operation->heredoc_buffer)
		{
			operation->heredoc_buffer = ft_strdup("");
			if (!operation->heredoc_buffer)
				return (0);
		}
		if (line && !ft_strcmp(line, operation->in_redirects[j].name))
			break;
		if (line && j == operation->n_in - 1)
			if (!prep_redirections_helper2(operation, line))
				return (0);
		if (!line)
		{
			print_heredoc_warning(op_ref, operation, j);
			break ;
		}
		free(line);
	}
	return (1);
}

int	prep_redirections(t_op_ref *op_ref, t_operation **operations)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (operations[i])
	{
		j = 0;
		if (operations[i]->operations)
			if (!prep_redirections(op_ref, operations[i]->operations))
				return (0);
		while (j < operations[i]->n_in)
		{
			if (operations[i]->in_redirects[j].type == REDIRECT_LIMITER)
				if (!prep_redirections_helper(op_ref, operations[i], j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	create_trunc_out_files(t_operation *operation)
{
	size_t	i;
	int		fd;
	int		flags;

	i = 0;
	while (i < operation->n_out)
	{
		flags = O_CREAT | O_WRONLY | O_TRUNC;
		if (operation->out_redirects[i].type == REDIRECT_APPEND)
			flags = O_CREAT | O_WRONLY | O_APPEND;
		fd = open(operation->out_redirects[i].name, flags,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			ft_dprintf(STDERR_FILENO, "Proton: %s: %s\n",
				operation->out_redirects[i].name, strerror(errno));
			return (0);
		}
		if (i != operation->n_out - 1)
			close(fd);
		else
			operation->redirect_out_fd = fd;
		i++;
	}
	return (1);
}

int	process_in_redirects_heredoc(t_operation *operation)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	write(pipefd[1], operation->heredoc_buffer,
		ft_strlen(operation->heredoc_buffer));
	close(pipefd[1]);
	return (pipefd[0]);
}

int	process_in_redirects(t_operation *operation)
{
	size_t	i;
	int		fd;

	i = 0;
	while (i < operation->n_in)
	{
		if (operation->in_redirects[i].type == REDIRECT_INFILE)
			fd = open(operation->in_redirects[i].name, O_RDONLY);
		else
			fd = process_in_redirects_heredoc(operation);
		if (fd == -1)
		{
			ft_dprintf(STDERR_FILENO, "Proton: %s: %s\n",
				operation->in_redirects[i].name, strerror(errno));
			return (0);
		}
		if (i != operation->n_in - 1)
			close(fd);
		else
			operation->redirect_in_fd = fd;
		i++;
	}
	return (1);
}

int	pre_execute_external_cmd(t_op_ref *op_ref, t_operation *operation)
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

void	execute_cmd_close_fds(t_operation *operation, int is_ext)
{
	if (operation->pipe_fds_in)
		close(operation->pipe_fds_in[0]);
	if (operation->pipe_fds_out)
	{
		if (is_ext)
			close(operation->pipe_fds_out[0]);
		close(operation->pipe_fds_out[1]);
	}
	if (operation->redirect_in_fd != -1)
		close(operation->redirect_in_fd);
	if (operation->redirect_out_fd != -1)
		close(operation->redirect_out_fd);
}

int	execute_cmd_redirections(t_operation *operation, int is_ext)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	if (operation->pipe_fds_in)
		in_fd = operation->pipe_fds_in[0];
	if (operation->pipe_fds_out)
		out_fd = operation->pipe_fds_out[1];
	if (operation->redirect_in_fd != -1)
		in_fd = operation->redirect_in_fd;
	if (operation->redirect_out_fd != -1)
		out_fd = operation->redirect_out_fd;
	if (in_fd != -1)
		if (dup2(in_fd, STDIN_FILENO) == -1)
			return (0);
	if (out_fd != -1)
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			return (0);
	execute_cmd_close_fds(operation, is_ext);
	return (1);
}

void	restore_sigint()
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, 0);
}

int	execute_cmd(t_op_ref *op_ref, t_operation *operation, t_operation *next_op)
{
	int		pid;
	char	**env;

	env = env_lst_to_2d_arr(op_ref);
	if (!env)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (!pid)
	{
		restore_sigint();
		execute_cmd_redirections(operation, 1);
		operation->args[0] = operation->cmd;
		execve(operation->cmd_path, operation->args, env);
		free_array((void **)env);
		return (-1);
	}
	op_ref->last_pid = pid;
	free_array((void **)env);
	if (next_op && next_op->operation_type != OPERATION_PIPE)
		op_ref->wait_childs = 1;
	execute_cmd_close_fds(operation, 0);
	return (EXIT_SUCCESS);
}

int	prep_pipeline(t_operation *operation, t_operation *next_op)
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

int	execute_process_circuit(t_operation *operation, t_op_ref *op_ref)
{
	if (op_ref->circuit_trigger)
	{
		if ((operation->operation_type == OPERATION_AND && !*op_ref->lec)
			|| (operation->operation_type == OPERATION_OR && *op_ref->lec))
			op_ref->circuit_trigger = 0;
		else
		{
			execute_cmd_close_fds(operation, 0);
			return (1);
		}
	}
	else
	{
		if ((operation->operation_type == OPERATION_AND && *op_ref->lec)
			|| (operation->operation_type == OPERATION_OR && !*op_ref->lec))
		{
			op_ref->circuit_trigger = 1;
			execute_cmd_close_fds(operation, 0);
			return (1);
		}
	}
	return (0);
}

int	subshell_apply_fds(t_operation *op)
{
	int	fds[2];

	ft_memset(fds, -1, sizeof(int) * 2);
	if (op->pipe_fds_in)
		fds[0] = op->pipe_fds_in[0];
	if (op->redirect_in_fd != -1)
		fds[0] = op->redirect_in_fd;
	if (op->pipe_fds_out)
	{
		fds[1] = op->pipe_fds_out[1];
		close(op->pipe_fds_out[0]);
	}
	if (op->redirect_out_fd != -1)
		fds[1] = op->redirect_out_fd;
	if (fds[0] != -1)
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (0);
	if (fds[1] != -1)
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (0);
	return (1);
}

int	execute_subshell(t_operation **ops, size_t i, t_op_ref *op_ref)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (!pid)
	{
		subshell_apply_fds(ops[i]);
		execute_cmd_close_fds(ops[i], 1);
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
	execute_cmd_close_fds(ops[i], 0);
	return (EXIT_SUCCESS);
}

int	execute_process_helper(t_operation **operations, size_t i, t_op_ref *op_ref)
{
	int	status;

	status = execute_expander(op_ref, operations[i]);
	if (!status)
		return (EXIT_SUCCESS);
	if (status == -1)
		return (EXIT_FAILURE);
	if (prep_pipeline(operations[i], operations[i + 1]))
		return (EXIT_FAILURE);
	if (!create_trunc_out_files(operations[i]))
	{
		*op_ref->lec = 1;
		return (EXIT_SUCCESS);
	}
	if (!process_in_redirects(operations[i]))
	{
		*op_ref->lec = 1;
		return (EXIT_SUCCESS);
	}
	if (execute_process_circuit(operations[i], op_ref))
		return (EXIT_SUCCESS);
	if (operations[i]->operations)
	{
		status = execute_subshell(operations, i, op_ref);
		return (status);
	}
	else if (operations[i]->cmd)
	{
		if (check_if_builtin(operations[i]->cmd))
		{
			if (ft_setenv(op_ref->env_lst, "_", operations[i]->cmd) == -1)
				return (EXIT_FAILURE);
			status = builtin_cmd(operations, i, op_ref);
			return (status);
		}
		else
		{
			status = pre_execute_external_cmd(op_ref, operations[i]);
			if (status == -1)
				return (EXIT_FAILURE);
			if (status)
			{
				if (ft_setenv(op_ref->env_lst, "_", operations[i]->cmd_path) == -1)
					return (EXIT_FAILURE);
				status = execute_cmd(op_ref, operations[i], operations[i + 1]);
			}
			if (status == -1)
				return (EXIT_FAILURE);
		}
	}
	else
	{
		ft_unsetenv(op_ref->env_lst, "_");
		execute_cmd_close_fds(operations[i], 0);
	}
	return (EXIT_SUCCESS);
}

void	wait_childs(t_op_ref *op_ref)
{
	int	wstatus;
	int	pid;

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

int	update_underscore_env(t_operation **ops, size_t i, t_op_ref *op_ref)
{
	char	*data;
	size_t	j;

	j = 1;
	if ((ops[i + 1] && ops[i + 1]->operation_type == OPERATION_PIPE)
		|| ops[i]->operation_type == OPERATION_PIPE)
		return (EXIT_SUCCESS);
	if (ops[i]->args[j])
	{
		while (ops[i]->args[j])
			j++;
		data = ops[i]->args[j - 1];
	}
	else
	{
		if (ops[i]->cmd_path)
			data = ops[i]->cmd_path;
		else if (ops[i]->cmd)
			data = ops[i]->cmd;
		else
			return (EXIT_SUCCESS);
	}
	if (ft_setenv(op_ref->env_lst, "_", data) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute_process(t_operation **ops, t_op_ref *op_ref, int is_subshell)
{
	size_t	i;
	
	if (!is_subshell)
	{
		signal_handler(0);
		if (!prep_redirections(op_ref, ops))
			return (EXIT_FAILURE);
	}
	i = 0;
	while (ops[i])
	{
		if (execute_process_helper(ops, i, op_ref) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (op_ref->wait_childs)
			wait_childs(op_ref);
		if (op_ref->signal_term || op_ref->is_exit)
			return (EXIT_SUCCESS);
		if (update_underscore_env(ops, i, op_ref) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	wait_childs(op_ref);
	return (EXIT_SUCCESS);
}
