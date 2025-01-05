/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:36:43 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/05 14:23:42 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_expander_check(char *s)
{
	if (!ft_strncmp(s, "$?", 2) || !ft_strncmp(s, "$_", 2))
		return (1);
	return (0);
}

int	check_if_index_sqr(size_t i, t_list *qr)
{
	size_t	*range;
	int		is_sq;

	while (qr)
	{
		if (qr->content)
		{
			range = ((t_qr *)qr->content)->arr;
			is_sq = ((t_qr *)qr->content)->is_sq;
			if (i >= range[0] && i <= range[1] && is_sq)
				return (1);
		}
		qr = qr->next;
	}
	return (0);
}
