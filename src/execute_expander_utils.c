/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_expander_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:49:25 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/30 00:02:02 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_expander_stage2_helper2(t_list **tokens,
	t_operation *op, size_t i)
{
	if (get_lsttok_size(*tokens) != 1)
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

void	exp_s1_update_op_iter(t_list *tokens,
	t_operation *op, char **args)
{
	size_t	i;

	i = 0;
	while (tokens)
	{
		if (tokens->content)
		{
			if (!i)
				op->cmd = tokens->content;
			else
				args[i] = (char *)tokens->content;
			i++;
		}
		tokens = tokens->next;
	}
}
