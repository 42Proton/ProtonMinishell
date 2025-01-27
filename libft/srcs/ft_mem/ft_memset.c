/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:24:55 by amsaleh           #+#    #+#             */
/*   Updated: 2024/10/14 16:09:11 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset(void *src, int c, size_t size)
{
	unsigned char	*src_cp;
	size_t			i;

	i = 0;
	src_cp = src;
	while (i < size)
	{
		src_cp[i] = c;
		i++;
	}
	return (src_cp);
}
