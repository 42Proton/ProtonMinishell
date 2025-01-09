/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_inbuilt_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:30 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/09 12:22:09 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_inbuilt_command(t_op_ref *op_ref, char *cmd, char **args)
{
	if (!ft_strcmp(cmd, "cd"))
		cd_cmd(op_ref, args);
	if (!ft_strcmp(cmd, "pwd"))
		pwd_cmd();
	if (!ft_strcmp(cmd, "echo"))
		echo_cmd(args);
	if (!ft_strcmp(cmd, "env"))
		env_cmd(op_ref);
	if (!ft_strcmp(cmd, "unset"))
		unset_cmd(op_ref, args);
	// if (!ft_strcmp(cmd, "export"))
	// 	export_cmd(minishell, args[1]);
	return (1);
}
