/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:47:43 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/20 01:25:56 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*gnl_strjoin(char *s1, char *s2, int n)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (n >= 1)
		free(s1);
	if (n >= 2)
		free(s2);
	return (res);
}
