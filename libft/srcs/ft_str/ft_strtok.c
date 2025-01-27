/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:16:38 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/13 22:21:57 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	check_if_delimiter(char c, char *delimiter)
{
	size_t	i;

	i = -1;
	while (delimiter[++i])
		if (c == delimiter[i])
			return (1);
	return (0);
}

static size_t	skip_delimiters(char *s, char *delimiter)
{
	size_t	res;

	res = 0;
	while (check_if_delimiter(s[res], delimiter))
		res++;
	return (res);
}

static char	*get_next_tok(char **s_save, char *delimiter)
{
	size_t	i;
	char	*res;
	char	*temp;

	res = *s_save;
	temp = res;
	while (*temp)
	{
		if (check_if_delimiter(*temp, delimiter) && temp != res)
		{
			*s_save = temp + 1;
			*temp = 0;
			return (res);
		}
		if (check_if_delimiter(*temp, delimiter) && temp == res)
		{
			i = skip_delimiters(temp, delimiter);
			res += i;
			temp += i;
		}
		if (*temp)
			temp++;
	}
	*s_save = 0;
	return (res);
}

char	*ft_strtok(char *s, char *delimiter)
{
	static char	*s_save;
	char		*res;

	if (!delimiter || (!s && !s_save))
		return (0);
	if (s)
		s_save = s;
	res = get_next_tok(&s_save, delimiter);
	if (!*res)
		return (0);
	return (res);
}
