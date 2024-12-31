/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:10:52 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/31 02:43:08 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_process(t_minishell *mini)
{
	if (ft_strchr(mini->operations[0]->cmd, '/'))
	{
		if (check_if_cmd_exist(mini->operations[0]->cmd))
		{
			int pid = fork();
			if (!pid)
			{
				char **env = env_lst_to_2d_arr(mini);
				execve(mini->operations[0]->cmd, mini->operations[0]->args, env);
				free_array((void **)env);
			}
			return (EXIT_SUCCESS);
		}
		perror(mini->operations[0]->cmd);
		return (EXIT_SUCCESS);
	}
	// }else
	// {
	// 	path = search_for_path(mini->operations[0]->cmd);
	// }
	return (EXIT_SUCCESS);
}
