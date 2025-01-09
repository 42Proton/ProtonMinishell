/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:10:52 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/10 00:53:56 by amsaleh          ###   ########.fr       */
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
			return (0);
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
			return (0);
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
		perror(operation->cmd);
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

int	execute_cmd_redirections(t_operation *operation)
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
	if (operation->pipe_fds_out)
		close(operation->pipe_fds_out[0]);
	if (in_fd != -1 && dup2(in_fd, STDIN_FILENO) == -1)
		return (0);
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1 && dup2(out_fd, STDOUT_FILENO) == -1)
		return (0);
	if (out_fd != -1)
		close(out_fd);
	return (1);
}

void	execute_cmd_close_fds(t_operation *operation)
{
	if (operation->pipe_fds_in)
		close(operation->pipe_fds_in[0]);
	if (operation->pipe_fds_out)
		close(operation->pipe_fds_out[1]);
	if (operation->redirect_in_fd != -1)
		close(operation->redirect_in_fd);
	if (operation->redirect_out_fd != -1)
		close(operation->redirect_out_fd);
}

int	execute_cmd(t_op_ref *op_ref, t_operation *operation, t_operation *next_op)
{
	int		pid;
	int 	wstatus;
	char	**env;

	env = env_lst_to_2d_arr(op_ref);
	if (!env)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (!pid)
	{
		execute_cmd_redirections(operation);
		operation->args[0] = operation->cmd;
		execve(operation->cmd_path, operation->args, env);
		free_array((void **)env);
		execute_cmd_close_fds(operation);
		return (-1);
	}
	free_array((void **)env);
	if (next_op && next_op->operation_type != OPERATION_PIPE)
	{
		wait(&wstatus);
		*op_ref->lec = WEXITSTATUS(wstatus);
	}
	execute_cmd_close_fds(operation);
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

int	execute_process_helper(t_operation **operations, size_t i, t_op_ref *op_ref)
{
	int	status;

	status = execute_expander(op_ref, operations[i]);
	if (status > 0)
	{
		if (prep_pipeline(operations[i], operations[i + 1]))
			return (EXIT_FAILURE);
		create_trunc_out_files(operations[i]);
		process_in_redirects(operations[i]);
		if (operations[i]->cmd)
		{
			if (check_if_builtin(operations[i]->cmd))
			{
				status = builtin_cmd(operations, i, op_ref);
				if (op_ref->is_exit)
					return (status);
			}
			else
			{
				status = pre_execute_external_cmd(op_ref, operations[i]);
				if (status == -1)
					return (EXIT_FAILURE);
				if (status)
					status = execute_cmd(op_ref, operations[i], operations[i + 1]);
				if (status == -1)
					return (EXIT_FAILURE);
			}
		}
		else
			execute_cmd_close_fds(operations[i]);
	}
	return (EXIT_SUCCESS);
}

int	execute_process(t_operation **operations, t_op_ref *op_ref)
{
	size_t	i;
	int		wstatus;
	
	if (!prep_redirections(op_ref, operations))
		return (EXIT_FAILURE);
	i = 0;
	signal_execution();
	while (operations[i])
	{
		if (execute_process_helper(operations, i, op_ref) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (op_ref->is_exit)
			return (EXIT_SUCCESS);
		i++;
	}
	while (wait(&wstatus) != -1)
		*op_ref->lec = WEXITSTATUS(wstatus);
	return (EXIT_SUCCESS);
}
