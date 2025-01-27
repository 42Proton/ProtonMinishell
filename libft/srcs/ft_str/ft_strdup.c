/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:41:39 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/20 01:05:02 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*res;

	len = ft_strlen(str);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	ft_strlcpy(res, str, len + 1);
	return (res);
}
