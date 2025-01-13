/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_inbuilt_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:30 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/13 23:54:08 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_inbuilt_command(t_op_ref *op_ref, char *cmd, char **args)
{
	int	status;

	status = EXIT_SUCCESS;
	*op_ref->lec = 0;
	if (!ft_strcmp(cmd, "cd"))
		cd_cmd(op_ref, args);
	if (!ft_strcmp(cmd, "pwd"))
		pwd_cmd(op_ref);
	if (!ft_strcmp(cmd, "echo"))
		status = echo_cmd(args);
	if (!ft_strcmp(cmd, "env"))
		status = env_cmd(op_ref);
	if (!ft_strcmp(cmd, "unset"))
		unset_cmd(op_ref, args);
	if (!ft_strcmp(cmd, "export"))
		export_cmd(op_ref, args);
	// if (!ft_strcmp(cmd, "exit"))
	// 	exit_cmd(op_ref,args);
	if (status == EXIT_FAILURE)
		return (status);
	return (EXIT_SUCCESS);
}
