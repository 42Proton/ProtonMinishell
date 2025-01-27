/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:11:13 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/20 01:33:31 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = len;
	if (!c)
		return ((char *)str + i);
	while (1)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		if (!i)
			break ;
		i--;
	}
	return (0);
}
