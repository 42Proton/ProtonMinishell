/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:37:22 by amsaleh           #+#    #+#             */
/*   Updated: 2024/08/25 15:44:20 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_bzero(void *src, size_t size)
{
	char	*src_cp;
	size_t	i;

	i = 0;
	src_cp = src;
	while (i < size)
	{
		src_cp[i] = '\0';
		i++;
	}
	return (src_cp);
}
