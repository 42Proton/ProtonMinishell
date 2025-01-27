/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:17:05 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/20 01:04:49 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *str, int c)
{
	char	*res;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(str);
	i = 0;
	while (i < s_len + 1)
	{
		if (str[i] == (char)c)
		{
			res = (char *)str + i;
			return (res);
		}
		i++;
	}
	return (0);
}
