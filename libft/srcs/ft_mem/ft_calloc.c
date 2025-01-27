/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:28:10 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 19:56:21 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(nitems * size);
	if (!res)
		return (0);
	while (i < nitems * size)
	{
		res[i] = 0;
		i++;
	}
	return ((void *)res);
}
