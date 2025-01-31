/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opers_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:27:08 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/31 10:35:01 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

ssize_t	separators_counter(t_list *lst)
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

ssize_t	separators_counter_subop(t_list *lst)
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

t_op_ref	*op_ref_init(t_operation **operations, t_minishell *mini)
{
	t_op_ref	*op_ref;

	op_ref = malloc(sizeof(t_op_ref));
	if (!op_ref)
	{
		free_operations(operations);
		exit_handler(mini, ERR_POSTLEXER);
	}
	op_ref->shell_exec = mini->shell_exec;
	op_ref->lec = &mini->last_exit_code;
	op_ref->stdin_bak = &mini->stdin_bak;
	op_ref->env_lst = &mini->env_lst;
	op_ref->curr_line = &mini->curr_line;
	op_ref->heredoc_line_inc = 0;
	op_ref->wait_childs = 0;
	op_ref->is_exit = 0;
	op_ref->circuit_trigger = 0;
	op_ref->signal_term = 0;
	op_ref->last_pid = -1;
	op_ref->is_child = 0;
	op_ref->is_subshell = 0;
	op_ref->term = &mini->term;
	return (op_ref);
}
