/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:27:11 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/24 16:57:01 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	prep_heredoc_join_res(t_operation *operation, char *line)
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

static int	prep_heredoc_helper2(char *line, t_op_ref *op_ref,
	t_operation *operation, size_t j)
{
	if (line && !ft_strcmp(line, operation->in_redirects[j].name))
	{
		free(line);
		return (2);
	}
	if (line && j == operation->n_in - 1)
	{
		if (!prep_heredoc_join_res(operation, line))
		{
			free(line);
			return (0);
		}
	}
	if (!line)
	{
		print_heredoc_warning(op_ref, operation, j);
		return (2);
	}
	free(line);
	return (1);
}

int	prep_heredoc_helper(t_op_ref *op_ref, t_operation *operation, size_t j)
{
	char	*line;
	int		status;

	while (1)
	{
		line = readline("> ");
		if (g_signum == SIGINT)
		{
			op_ref->signal_term = 1;
			return (1);
		}
		if (j == operation->n_in - 1 && !operation->heredoc_buffer)
		{
			operation->heredoc_buffer = ft_strdup("");
			if (!operation->heredoc_buffer)
			{
				free(line);
				return (0);
			}
		}
		status = prep_heredoc_helper2(line, op_ref, operation, j);
		if (status != 1)
			break ;
	}
	return (status);
}

int	prep_heredoc(t_op_ref *op_ref, t_operation **operations)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (operations[i])
	{
		j = 0;
		if (operations[i]->operations)
			if (!prep_heredoc(op_ref, operations[i]->operations))
				return (0);
		if (op_ref->signal_term)
			return (1);
		while (j < operations[i]->n_in)
		{
			if (operations[i]->in_redirects[j].type == REDIRECT_LIMITER)
				if (!prep_heredoc_helper(op_ref, operations[i], j))
					return (0);
			if (op_ref->signal_term)
				return (1);
			j++;
		}
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
