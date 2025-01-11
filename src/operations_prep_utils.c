/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:50:36 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/11 23:36:00 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_operation_alloc(t_operation **operations, ssize_t i)
{
	t_operation	*temp;

	temp = ft_calloc(1, sizeof(t_operation));
	if (!temp)
	{
		while (--i > -1)
			free(operations[i]);
		free(operations);
		return (0);
	}
	temp->redirect_in_fd = -1;
	temp->redirect_out_fd = -1;
	temp->parent_in_fd = -1;
	temp->parent_out_fd = -1;
	operations[i] = temp;
	return (1);
}

void	free_operations_args(char **args)
{
	size_t	i;

	if (!args)
		return ;
	i = 1;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_operations_redirects(t_redirect *redirects, size_t n)
{
	size_t	i;

	i = 0;
	if (!redirects)
		return ;
	while (i < n)
	{
		free(redirects[i].name);
		i++;
	}
	free(redirects);
}

void	free_operations(t_operation **operations)
{
	size_t	i;

	i = 0;
	while (operations[i])
	{
		if (operations[i]->operations)
			free_operations(operations[i]->operations);
		free_operations_args(operations[i]->args);
		free(operations[i]->cmd);
		free_operations_redirects(operations[i]->in_redirects,
			operations[i]->n_in);
		free_operations_redirects(operations[i]->out_redirects,
			operations[i]->n_out);
		free(operations[i]->heredoc_buffer);
		free(operations[i]->cmd_path);
		free(operations[i]->pipe_fds_out);
		free(operations[i]);
		i++;
	}
	free(operations);
}

int	add_subop(t_operation **operations, size_t i, t_list *lst)
{
	operations[i]->operations = operations_prep(lst, 1);
	if (!operations[i]->operations)
	{
		free_operations(operations);
		return (0);
	}
	return (1);
}

int	get_ops_data(t_operation **operations, t_list *lst, int is_subop)
{
	if (!is_subop)
	{
		if (!prep_ops_data(operations, lst))
			return (0);
	}
	else
	{
		if (!prep_subops_data(operations, lst))
			return (0);
	}
	return (1);
}
