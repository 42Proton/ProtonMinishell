/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:35:22 by coderx64          #+#    #+#             */
/*   Updated: 2024/12/26 11:06:13 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_operation	**operations_alloc(ssize_t sep_count)
{
	t_operation	**operations;
	ssize_t		i;

	i = 1;
	operations = ft_calloc(sizeof(void *), sep_count + 2);
	if (!operations)
		return (0);
	if (!add_operation_alloc(operations, 0))
		return (0);
	while (sep_count)
	{
		if (!add_operation_alloc(operations, i))
			return (0);
		sep_count--;
		i++;
	}
	return (operations);
}

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
	operations[i] = temp;
	return (1);
}

void	free_operations(t_operation **operations)
{
	size_t	i;

	i = 0;
	while (operations[i])
	{
		if (operations[i]->operations)
			free_operations(operations[i]->operations);
		free(operations[i]->args);
		free(operations[i]->in_redirects);
		free(operations[i]->out_redirects);
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
