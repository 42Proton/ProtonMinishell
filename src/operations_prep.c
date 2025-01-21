/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:23 by bismail           #+#    #+#             */
/*   Updated: 2025/01/21 21:28:42 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	prep_ops_data(t_operation **operations, t_list *lst)
{
	size_t	i;
	size_t	parenthesis_count;

	i = 0;
	parenthesis_count = 0;
	while (lst)
	{
		if (!prep_op_main_conditions(lst, &parenthesis_count,
				operations, &i))
			return (0);
		if (!lst->prev || (check_op_type(lst) && !parenthesis_count))
			if (!op_data_collector(operations, i, lst))
				return (0);
		if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		lst = lst->next;
	}
	return (1);
}

int	prep_subops_data(t_operation **operations, t_list *lst)
{
	size_t	i;
	size_t	parenthesis_count;

	i = 0;
	parenthesis_count = 1;
	lst = lst->next;
	while (parenthesis_count)
	{
		if (!prep_subop_main_conditions(lst, &parenthesis_count,
				operations, &i))
			return (0);
		if ((((t_token *)lst->prev->content)->type == OPEN_PARENTHESIS
				|| check_op_type(lst)) && parenthesis_count == 1)
			if (!op_data_collector(operations, i, lst))
				return (0);
		if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		lst = lst->next;
	}
	return (1);
}

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

t_operation	**operations_prep(t_list *lst, int is_subop)
{
	ssize_t		sep_count;
	t_operation	**operations;

	if (!is_subop)
		sep_count = separators_counter(lst);
	else
		sep_count = separators_counter_subop(lst);
	operations = operations_alloc(sep_count);
	if (!operations)
		return (0);
	if (!get_ops_data(operations, lst, is_subop))
		return (0);
	return (operations);
}
