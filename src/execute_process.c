/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:23 by bismail           #+#    #+#             */
/*   Updated: 2024/12/25 15:10:17 by abueskander      ###   ########.fr       */
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
		else if (((t_token *)lst->content)->type >= AND_OPERATOR
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
		else if (((t_token *)lst->content)->type >= AND_OPERATOR
				&& ((t_token *)lst->content)->type <= PIPE
				&& !parenthesis_count)
			counter++;
		lst = lst->next;
	}
	return (counter);
}

static int	add_operation_alloc(t_token *tok, t_operation **operations,
		ssize_t *i)
{
	t_operation	*temp;

	temp = ft_calloc(1, sizeof(t_operation));
	if (!temp)
	{
		while (--(*i) > -1)
			free(operations[*i]);
		return (0);
	}
	operations[*i] = temp;
	(*i)++;
	return (1);
}

static t_operation	**operations_alloc(t_list *lst, ssize_t sep_count)
{
	t_operation	**operations;
	ssize_t		i;

	i = 0;
	operations = ft_calloc(sizeof(void *), sep_count + 1);
	if (!add_operation_alloc((t_token *)lst->content, operations, &i))
		return (0);
	while (sep_count)
	{
		if (!add_operation_alloc((t_token *)lst->content, operations, &i))
			return (0);
		sep_count--;
	}
	return (operations);
}

t_operation	**operation_prep(t_list *lst, int is_subop)
{
	ssize_t sep_count;
	t_operation **operations;

	if (!is_subop)
		sep_count = separators_counter(lst);
	else
		sep_count = separators_counter_subop(lst);
	operations = operations_alloc(lst, sep_count);
	if (!operations)
		return (0);
	return (1);
}