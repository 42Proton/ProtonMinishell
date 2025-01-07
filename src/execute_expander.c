/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:44:36 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/08 00:48:25 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	get_arr_len(void **arr)
{
	size_t	res;

	res = 0;
	while (arr[res])
		res++;
	return (res);
}

int	expander_s1_update_operation(t_operation *operation, t_list *tokens)
{
	char	**args;
	size_t	lst_size;
	size_t	i;

	operation->cmd = tokens->content;
	tokens = tokens->next;
	lst_size = ft_lstsize(tokens);
	args = ft_calloc(lst_size + 2, sizeof(char *));
	if (!args)
		return (-1);
	i = 1;
	while (i < lst_size + 1)
	{
		args[i] = (char *)tokens->content;
		tokens = tokens->next;
		i++;
	}
	free(operation->args);
	operation->args = args;
	return (1);
}

int	execute_expander_stage1(t_op_ref *op_ref, t_operation *operation, t_list **tokens)
{
	char	**args;

	if (operation->cmd)
	{
		if (!token_expander(operation->cmd, tokens, op_ref))
			return (-1);
		args = operation->args;
		args++;
		if (get_arr_len((void **)args) > 0)
		{
			while (*args)
			{
				if (!token_expander(*args, tokens, op_ref))
					return (-1);
				args++;
			}
		}
		if (!expander_s1_update_operation(operation, *tokens))
			return (-1);
		free_lst(*tokens);
	}
	return (1);
}

int	execute_expander_stage2_helper(t_op_ref *op_ref, t_operation *operation, t_list **tokens)
{
	size_t	i;

	i = 0;
	while (i < operation->n_in)
	{
		if (!token_expander(operation->in_redirects[i].name, tokens, op_ref))
			return (-1);
		if (ft_lstsize(*tokens) > 1)
		{
			ft_dprintf(STDERR_FILENO, "%s: ambiguous redirect\n",
				operation->in_redirects[i].name);
			return (0);
		}
		operation->in_redirects[i].name = (char *)(*tokens)->content;
		free_lst(*tokens);
		*tokens = 0;
		i++;
	}
	return (1);
}

int execute_expander_stage2(t_op_ref *op_ref, t_operation *operation, t_list **tokens)
{
	size_t	i;
	int		status;

	i = 0;
	status = execute_expander_stage2_helper(op_ref, operation, tokens);
	if (status <= 0)
		return (status);
	while (i < operation->n_out)
	{
		if (!token_expander(operation->out_redirects[i].name, tokens, op_ref))
			return (-1);
		if (ft_lstsize(*tokens) > 1)
		{
			ft_dprintf(STDERR_FILENO, "%s: ambiguous redirect\n",
				operation->in_redirects[i].name);
			return (0);
		}
		operation->out_redirects[i].name = (char *)(*tokens)->content;
		free_lst(*tokens);
		*tokens = 0;
		i++;
	}
	return (1);
}

int	execute_expander(t_op_ref *op_ref, t_operation *operation)
{
	t_list	*tokens;
	int		status;

	tokens = 0;
	if (execute_expander_stage1(op_ref, operation, &tokens) == -1)
	{
		ft_lstclear(&tokens, free);
		return (-1);
	}
	tokens = 0;
	status = execute_expander_stage2(op_ref, operation, &tokens);
	if (!status || status == -1)
	{
		ft_lstclear(&tokens, free);
		return (status);
	}
	return (1);
}
