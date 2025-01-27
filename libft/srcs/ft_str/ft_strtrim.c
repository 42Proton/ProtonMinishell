/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:09:33 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/06 14:05:10 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_if_charset_match(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c != set[i])
			i++;
		else
			return (1);
	}
	return (0);
}

static char	*handle_edge_case(void)
{
	char	*res;

	res = malloc(1 * sizeof(char));
	if (!res)
		return (0);
	res[0] = 0;
	return (res);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	start = 0;
	if (!s1[0] || !set[0])
	{
		res = ft_strdup(s1);
		if (!res)
			return (0);
		return (res);
	}
	end = ft_strlen(s1);
	while (get_if_charset_match(s1[start], set))
		start++;
	if (start > end)
	{
		res = handle_edge_case();
		return (res);
	}
	while (get_if_charset_match(s1[end], set))
		end--;
	res = ft_substr(s1, start, (end - start) + 1);
	return (res);
}
