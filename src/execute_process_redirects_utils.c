/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_redirects_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:46:11 by amsaleh           #+#    #+#             */
/*   Updated: 2025/02/28 14:59:17 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	create_trunc_out_files(t_operation *op)
{
	size_t	i;
	int		fd;
	int		flags;

	i = 0;
	while (i < op->n_out)
	{
		if (!out_files_check(op, i, &flags))
			return (0);
		fd = open(op->out_redirects[i].name, flags,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			ft_dprintf(STDERR_FILENO, "Proton: %s: %s\n",
				op->out_redirects[i].name, strerror(errno));
			return (0);
		}
		if (i != op->n_out - 1)
			close(fd);
		else
			op->redirect_out_fd = fd;
		i++;
	}
	return (1);
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
