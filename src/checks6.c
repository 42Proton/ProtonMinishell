/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:36:43 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/03 16:17:09 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_expander_check(char *s)
{
	if (!ft_strncmp(s, "$?", 2) || !ft_strncmp(s, "$_", 2))
		return (1);
	return (0);
}