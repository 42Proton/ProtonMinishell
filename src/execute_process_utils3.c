/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:35 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/27 15:19:18 by amsaleh          ###   ########.fr       */
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
	if (*(char *)(*tokens)->content)
	{
		free(operation->in_redirects[i].name);
		operation->in_redirects[i].name = (char *)(*tokens)->content;
	}
	else
		free((*tokens)->content);
	free_lst(*tokens);
}
