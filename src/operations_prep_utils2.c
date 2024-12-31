/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:50:51 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/31 00:54:41 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	prep_op_main_conditions(t_list *lst, size_t *p_count,
	t_operation **operations, size_t *i)
{
	if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
	{
		if (!*p_count)
			if (!add_subop(operations, *i, lst))
				return (0);
		(*p_count)++;
	}
	if (check_op_type(lst) && !*p_count)
	{
		(*i)++;
		operations[*i]->operation_type = check_op_type(lst);
	}
	return (1);
}

int	prep_subop_main_conditions(t_list *lst, size_t *p_count,
	t_operation **operations, size_t *i)
{
	if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
	{
		if (*p_count == 1)
			if (!add_subop(operations, *i, lst))
				return (0);
		(*p_count)++;
	}
	if (check_op_type(lst) && *p_count == 1)
	{
		(*i)++;
		operations[*i]->operation_type = check_op_type(lst);
	}
	return (1);
}

int	op_prep_redirections(t_operation *operation, t_list *lst)
{
	ssize_t	parenthesis_count;

	parenthesis_count = 0;
	while (check_op_prep_condition(lst, parenthesis_count))
	{
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		else if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (check_in_redirection(lst) && !parenthesis_count)
			operation->n_in++;
		else if (check_out_redirection(lst) && !parenthesis_count)
			operation->n_out++;
		lst = lst->next;
	}
	if (operation->n_in)
		operation->in_redirects = malloc(operation->n_in * sizeof(t_redirect));
	if (operation->n_in && !operation->in_redirects)
		return (0);
	if (operation->n_out)
		operation->out_redirects = malloc(operation->n_out
				* sizeof(t_redirect));
	if (operation->n_out && !operation->out_redirects)
		return (0);
	return (1);
}

void	op_get_redirections(t_operation *operation, t_list *lst)
{
	size_t	i_in;
	size_t	i_out;
	ssize_t	parenthesis_count;

	i_in = 0;
	i_out = 0;
	parenthesis_count = 0;
	while (check_op_prep_condition(lst, parenthesis_count))
	{
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		else if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (check_in_redirection(lst) && !parenthesis_count)
		{
			set_redirection_data(&operation->in_redirects[i_in], lst);
			i_in++;
		}
		else if (check_out_redirection(lst) && !parenthesis_count)
		{
			set_redirection_data(&operation->out_redirects[i_out], lst);
			i_out++;
		}
		lst = lst->next;
	}
}

int	op_data_collector(t_operation **operations, size_t i, t_list *lst)
{
	if (check_op_type(lst))
		lst = lst->next;
	if (!op_prep_redirections(operations[i], lst))
	{
		free_operations(operations);
		return (0);
	}
	op_get_redirections(operations[i], lst);
	if (!op_prep_args(operations[i], lst))
	{
		free_operations(operations);
		return (0);
	}
	if (operations[i]->n_args)
		op_get_args(operations[i], lst);
	return (1);
}
