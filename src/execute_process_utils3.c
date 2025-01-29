/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:35 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/29 11:23:23 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	out_files_check(t_operation *op, size_t i, int *flags)
{
	size_t	len;

	*flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (op->out_redirects[i].type == REDIRECT_APPEND)
		*flags = O_CREAT | O_WRONLY | O_APPEND;
	len = ft_strlen(op->out_redirects[i].name);
	if (check_if_dir(op->out_redirects[i].name) == 1
		|| op->out_redirects[i].name[len - 1] == '/')
	{
		ft_dprintf(STDERR_FILENO, "Proton: %s: Is a directory\n",
			op->out_redirects[i].name);
		return (0);
	}
	return (1);
}

void	exec_exp_s2_helper2(t_list **tokens,
	t_operation *operation, size_t i)
{
	if ((*tokens)->content)
	{
		free(operation->in_redirects[i].name);
		operation->in_redirects[i].name = (char *)(*tokens)->content;
	}
	else
		free((*tokens)->content);
	free_lst(*tokens);
}

int	prep_heredoc_helper_util(t_operation *op, char *line)
{
	op->heredoc_buffer = ft_strdup("");
	if (!op->heredoc_buffer)
	{
		free(line);
		return (0);
	}
	return (1);
}

int	prep_heredoc_util(t_op_ref *op_ref,
	t_operation **ops, size_t i, size_t j)
{
	if (ops[i]->in_redirects[j].type == REDIRECT_LIMITER)
	{
		if (!prep_heredoc_helper(op_ref, ops[i], j))
			return (0);
		*op_ref->curr_line += op_ref->heredoc_line_inc;
		op_ref->heredoc_line_inc = 0;
	}
	return (1);
}

void	execute_cmd_end(t_op_ref *op_ref,
	pid_t pid, t_operation *next_op)
{
	op_ref->last_pid = pid;
	if (next_op && next_op->operation_type != OPERATION_PIPE)
		op_ref->wait_childs = 1;
}
