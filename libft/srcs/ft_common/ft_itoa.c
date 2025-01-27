/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:27:46 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 00:23:49 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	number_to_str(int n, int digits_count, char *res)
{
	int	is_minus;

	is_minus = 0;
	if (n < 0)
	{
		*res = '-';
		is_minus = 1;
		n *= -1;
	}
	while (n > 0)
	{
		res[(digits_count - 1) + is_minus] = (n % 10) + 0x30;
		n /= 10;
		digits_count--;
	}
}

static char	*handle_zero_min_value(int n)
{
	char	*res;

	if (!n)
	{
		res = malloc(2 * sizeof(char));
		if (!res)
			return (0);
		ft_strlcpy(res, "0", 2);
		return (res);
	}
	res = malloc(12 * sizeof(char));
	if (!res)
		return (0);
	ft_strlcpy(res, "-2147483648", 12);
	return (res);
}

char	*ft_itoa(int n)
{
	int		i;
	int		is_minus;
	char	*res;

	is_minus = 0;
	i = get_digits_amount(n);
	if (!n || n == -2147483648)
		return (handle_zero_min_value(n));
	if (n < 0)
		is_minus = 1;
	res = malloc((i + is_minus + 1) * sizeof(char));
	if (!res)
		return (0);
	res[i + is_minus] = 0;
	number_to_str(n, i, res);
	return (res);
}
