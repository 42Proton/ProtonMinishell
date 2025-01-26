/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:10:52 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/26 18:12:31 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_underscore_env(t_operation **ops, size_t i, t_op_ref *op_ref)
{
	char	*data;
	size_t	j;

	j = 1;
	if ((ops[i + 1] && ops[i + 1]->operation_type == OPERATION_PIPE)
		|| ops[i]->operation_type == OPERATION_PIPE)
		return (EXIT_SUCCESS);
	if (ops[i]->args && ops[i]->args[j])
	{
		while (ops[i]->args[j])
			j++;
		data = ops[i]->args[j - 1];
	}
	else
	{
		if (ops[i]->cmd_path)
			data = ops[i]->cmd_path;
		else if (ops[i]->cmd)
			data = ops[i]->cmd;
		else
			return (EXIT_SUCCESS);
	}
	if (data && ft_setenv(op_ref->env_lst, "_", data) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute_process_heredoc(t_operation **ops, t_op_ref *op_ref)
{
	signal_handler(SIG_NEWPROMPT);
	if (!prep_heredoc(op_ref, ops))
		return (EXIT_FAILURE);
	signal_handler(SIG_IGNORE);
	if (op_ref->signal_term)
		return (EXIT_SUCCESS);
	close(*op_ref->stdin_bak);
	*op_ref->stdin_bak = 0;
	return (EXIT_SUCCESS);
}

int	exec_proc_iter(t_operation **ops,
	t_op_ref *op_ref, size_t i)
{
	if (execute_process_helper(ops, i, op_ref) == EXIT_FAILURE)
	{
		execute_cmd_close_fds(ops[i], 0);
		return (EXIT_FAILURE);
	}
	if ((ops[i + 1] && ops[i + 1]->operation_type != OPERATION_PIPE)
		&& ops[i]->operation_type != OPERATION_PIPE)
		if (!ops[i]->cmd)
			ft_unsetenv(op_ref->env_lst, "_");
	execute_cmd_close_fds(ops[i], 0);
	if (op_ref->wait_childs)
		wait_childs(op_ref);
	if (op_ref->signal_term || op_ref->is_exit)
	{
		wait_childs(op_ref);
		return (EXIT_SUCCESS);
	}
	if (update_underscore_env(ops, i, op_ref) == EXIT_FAILURE)
	{
		wait_childs(op_ref);
		return (EXIT_FAILURE);
	}
	return (2);
}

int	expand_heredoc_limiters(t_operation **ops)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	while (ops[i])
	{
		j = 0;
		while (j < ops[i]->n_in)
		{
			if (ops[i]->in_redirects->type == REDIRECT_LIMITER)
			{
				res = exp_limiter(ops[i]->in_redirects->name);
				if (!res)
					return (0);
				free(ops[i]->in_redirects->name);
				ops[i]->in_redirects->name = res;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	execute_process(t_operation **ops,
	t_op_ref *op_ref, int is_subshell)
{
	size_t	i;
	int		status;

	if (!is_subshell)
	{
		expand_heredoc_limiters(ops);
		execute_process_heredoc(ops, op_ref);
		if (op_ref->signal_term)
			return (EXIT_SUCCESS);
	}
	else
		signal_handler(SIG_IGNORE);
	i = 0;
	while (ops[i])
	{
		status = exec_proc_iter(ops, op_ref, i);
		if (status != 2)
			return (status);
		i++;
	}
	wait_childs(op_ref);
	return (EXIT_SUCCESS);
}
