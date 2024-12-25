/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coderx64 <coderx64@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:35:22 by coderx64          #+#    #+#             */
/*   Updated: 2024/12/25 23:37:02 by coderx64         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_operation	**operations_alloc(ssize_t sep_count)
{
	t_operation	**operations;
	ssize_t		i;

	i = 1;
	operations = ft_calloc(sizeof(void *), sep_count + 2);
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
		return (0);
	}
	operations[i] = temp;
	return (1);
}

int	add_subop(t_operation **operations, size_t i, t_list *lst)
{
	operations[i]->operations = operation_prep(lst, 1);
	if (!operations[i]->operations)
	{
		free_array((void **)operations);
		return (0);
	}
	return (1);
}