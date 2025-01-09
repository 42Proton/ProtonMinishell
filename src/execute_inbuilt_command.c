/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_inbuilt_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:30 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/09 10:06:18 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_inbuilt_command(t_op_ref *op_ref, char **args)
{
	if (!ft_strcmp(args[0], "cd"))
		cd_cmd(op_ref, args);
	if (!ft_strcmp(args[0], "pwd"))
		pwd_cmd();
	if (!ft_strcmp(args[0], "echo"))
		echo_cmd(args);
	if (!ft_strcmp(args[0], "env"))
		env_cmd(op_ref);
	if (!ft_strcmp(args[0], "unset"))
		unset_cmd(op_ref, args);
	// if (!ft_strcmp(args[0], "export"))
	// 	export_cmd(minishell, args[1]);
	return (1);
}
