/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:14:24 by amsaleh           #+#    #+#             */
/*   Updated: 2024/10/14 16:10:02 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dest, void *src, size_t size)
{
	unsigned char	*dest_temp;
	unsigned char	*src_temp;
	size_t			i;

	i = 0;
	src_temp = src;
	dest_temp = dest;
	if (dest == src)
		return (dest);
	while (i < size)
	{
		*dest_temp = *src_temp;
		src_temp++;
		dest_temp++;
		i++;
	}
	return (dest);
}
