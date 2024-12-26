/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:23 by bismail           #+#    #+#             */
/*   Updated: 2024/12/26 14:55:36 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static ssize_t	separators_counter(t_list *lst)
{
	ssize_t	counter;
	size_t	parenthesis_count;

	parenthesis_count = 0;
	counter = 0;
	while (lst)
	{
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (((t_token *)lst->content)->type >= AND_OPERATOR
				&& ((t_token *)lst->content)->type <= PIPE
				&& !parenthesis_count)
			counter++;
		lst = lst->next;
	}
	return (counter);
}

static ssize_t	separators_counter_subop(t_list *lst)
{
	ssize_t	counter;
	size_t	parenthesis_count;

	parenthesis_count = 1;
	counter = 0;
	lst = lst->next;
	while (parenthesis_count)
	{
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (((t_token *)lst->content)->type >= AND_OPERATOR
				&& ((t_token *)lst->content)->type <= PIPE
				&& parenthesis_count == 1)
			counter++;
		lst = lst->next;
	}
	return (counter);
}

int	prep_op_main_conditions(t_list *lst, size_t *parenthesis_count,
	t_operation **operations, size_t *i)
{
	if (((t_token *)lst->content)->type == OPEN_PARENTHESIS
	&& !*parenthesis_count)
	{
		operations[*i]->operation_type = OPERATION_SUBSHELL;
		if (!add_subop(operations, *i, lst))
			return (0);
		(*parenthesis_count)++;
	}
	if (((t_token *)lst->content)->type >= AND_OPERATOR
		&& ((t_token *)lst->content)->type <= PIPE
		&& !*parenthesis_count)
	{
		(*i)++;
		operations[*i]->operation_type = check_op_type(lst);
	}
	return (1);
}

int	prep_ops_data(t_operation **operations, t_list *lst)
{
	size_t	i;
	size_t	parenthesis_count;

	i = 0;
	parenthesis_count = 0;
	while (lst)
	{
		prep_op_main_conditions(lst, &parenthesis_count,
			operations, &i);
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
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS
		&& parenthesis_count == 1)
		{
			if (!add_subop(operations, i, lst))
				return (0);
			parenthesis_count++;
		}
		if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (((t_token *)lst->content)->type >= AND_OPERATOR
			&& ((t_token *)lst->content)->type <= PIPE
			&& parenthesis_count == 1)
			i++;
		lst = lst->next;
	}
	return (1);
}

t_operation	**operations_prep(t_list *lst, int is_subop)
{
	ssize_t sep_count;
	t_operation **operations;

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
