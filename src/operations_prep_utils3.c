/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:50:44 by amsaleh           #+#    #+#             */
/*   Updated: 2025/02/01 17:25:14 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_redirection_data(t_operation *operations,
	t_list *lst, size_t *i, int whom)
{
	if (whom == 1)
	{
		operations->in_redirects[*i].type = op_type_to_redirection(lst);
		operations->in_redirects[*i].name = ft_strdup(((
						t_token *)lst->next->content)->token_word);
		if (!operations->in_redirects[*i].name)
			return (0);
	}
	else
	{
		operations->out_redirects[*i].type = op_type_to_redirection(lst);
		operations->out_redirects[*i].name = ft_strdup(((
						t_token *)lst->next->content)->token_word);
		if (!operations->out_redirects[*i].name)
			return (0);
	}
	*(i) += 1;
	return (1);
}

int	op_prep_args(t_operation *operation, t_list *lst)
{
	ssize_t	parenthesis_count;
	size_t	n_args;

	parenthesis_count = 0;
	n_args = 0;
	while (check_op_prep_condition(lst, parenthesis_count))
	{
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		else if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (((t_token *)lst->content)->type == ARGUMENT && !parenthesis_count)
			n_args++;
		lst = lst->next;
	}
	operation->args = ft_calloc(n_args + 2, sizeof(char *));
	if (!operation->args)
		return (0);
	operation->n_args = n_args;
	return (1);
}

int	op_get_args(t_operation *operation, t_list *lst)
{
	ssize_t	parenthesis_count;
	size_t	i;
	t_token	*tok;

	parenthesis_count = 0;
	i = 1;
	while (check_op_prep_condition(lst, parenthesis_count))
	{
		tok = (t_token *)lst->content;
		if (tok->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		else if (tok->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (tok->type == ARGUMENT && !parenthesis_count)
		{
			operation->args[i] = ft_strdup(tok->token_word);
			if (!operation->args[i])
				return (0);
			i++;
		}
		lst = lst->next;
	}
	return (1);
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
	temp->redirect_in_fd = -1;
	temp->redirect_out_fd = -1;
	operations[i] = temp;
	return (1);
}
