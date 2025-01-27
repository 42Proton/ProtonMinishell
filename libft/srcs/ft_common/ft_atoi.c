/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:47:04 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 19:56:24 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 0x0D) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signal;
	int	res;

	i = 0;
	signal = 1;
	res = 0;
	while (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
	{
		if (!is_whitespace(str[i]) && !(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signal *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 0x30);
		i++;
	}
	return (res * signal);
}
