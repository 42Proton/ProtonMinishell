/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:36:43 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/30 14:43:05 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_if_cmd_exist(char *cmd)
{
	if (access(cmd, F_OK) == -1)
		return (0);
	if (access(cmd, X_OK) == -1)
		return (0);
	return (1);
}