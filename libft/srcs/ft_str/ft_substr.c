/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:14:40 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 19:56:25 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	l_len;

	i = -1;
	l_len = len;
	if (start >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	if (l_len + start > ft_strlen(s))
		l_len = ft_strlen(s) - start;
	res = ft_calloc((l_len + 1), sizeof(char));
	if (!res)
		return (0);
	while (++i < l_len)
		res[i] = s[start + i];
	return (res);
}
