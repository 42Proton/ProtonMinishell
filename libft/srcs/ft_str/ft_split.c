/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:53:18 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 20:20:01 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	add_word_arr(const char *s, t_split split_se, char **arr, int arr_i)
{
	arr[arr_i] = ft_substr(s, split_se.start, split_se.end - split_se.start);
	if (!arr[arr_i])
	{
		free_array((void **)arr);
		return (0);
	}
	return (1);
}

static int	extract_words(const char *s, char c, char **arr)
{
	t_split	split_se;
	int		arr_i;

	split_se.end = 0;
	arr_i = 0;
	while (s[split_se.end] == c)
		split_se.end++;
	split_se.start = split_se.end;
	while (s[split_se.end])
	{
		if (s[split_se.end] == c)
		{
			if (!add_word_arr(s, split_se, arr, arr_i))
				return (0);
			arr_i++;
			while (s[split_se.end + 1] == c)
				split_se.end++;
			split_se.start = split_se.end + 1;
		}
		split_se.end++;
	}
	if (split_se.start != split_se.end)
		add_word_arr(s, split_se, arr, arr_i);
	return (1);
}

static int	words_count(const char *s, char c)
{
	int	i;

	i = 0;
	if (!*s)
		return (0);
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s == c)
		{
			while (*s == c)
				s++;
			i++;
		}
		else
			s++;
	}
	if (*(s - 1) != c)
		i++;
	return (i);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		count;

	count = words_count(s, c);
	if (!count)
		return (ft_calloc(1, sizeof(char *)));
	res = ft_calloc(words_count(s, c) + 1, sizeof(char *));
	if (!res)
		return (0);
	if (!extract_words(s, c, res))
		return (0);
	return (res);
}
