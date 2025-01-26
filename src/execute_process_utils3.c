/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:35 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/26 14:49:40 by abueskander      ###   ########.fr       */
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
