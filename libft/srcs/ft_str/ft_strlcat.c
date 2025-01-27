/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:41:38 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 19:55:51 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	if (i >= size)
		return (size + ft_strlen(src));
	while (j < (size - i) - 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (j < (size - i))
		dst[i + j] = 0;
	j = 0;
	while (src[j])
		j++;
	return (i + j);
}
