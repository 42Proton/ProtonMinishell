/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_expander_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:49:25 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/26 10:54:00 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exp_s1_update_op_prep(t_operation *op, t_list **tokens,
	size_t *lst_size, size_t *arr_size)
{
	free(op->cmd);
	op->cmd = (*tokens)->content;
	*tokens = (*tokens)->next;
	*lst_size = ft_lstsize(*tokens);
	*arr_size = get_lsttok_size(*tokens);
}

int	execute_expander_stage2_helper2(t_list **tokens,
	t_operation *op, size_t i)
{
	if (ft_lstsize(*tokens) > 1)
	{
		ft_dprintf(STDERR_FILENO, "%s: ambiguous redirect\n",
			op->in_redirects[i].name);
		return (0);
	}
	if (*(char *)(*tokens)->content)
	{
		free(op->out_redirects[i].name);
		op->out_redirects[i].name = (char *)(*tokens)->content;
	}
	else
		free((*tokens)->content);
	return (1);
}
