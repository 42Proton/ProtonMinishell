/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:15:48 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 15:38:39 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	printf_nbrlen(int n)
{
	size_t	res;

	res = 0;
	if (n == INT_MIN)
		return (11);
	if (!n)
		return (1);
	if (n < 0)
	{
		n *= -1;
		res++;
	}
	while (n > 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

static int	printf_addnbr_helper(t_printf *data, int n)
{
	printf_addchar(data, '-');
	n *= -1;
	return (n);
}

void	printf_addnbr(t_printf *data, int n)
{
	char	res[10];
	int		i;

	if (!n)
	{
		printf_addchar(data, '0');
		return ;
	}
	if (n == INT_MIN)
	{
		ft_strncpy(data->res + data->res_i, "-2147483648", 11);
		data->res_i += 11;
		return ;
	}
	if (n < 0)
		n = printf_addnbr_helper(data, n);
	i = 0;
	while (n)
	{
		res[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (--i > -1)
		printf_addchar(data, res[i]);
}

void	printf_addunbr(t_printf *data, unsigned int n)
{
	char	res[10];
	int		i;

	if (!n)
	{
		printf_addchar(data, '0');
		return ;
	}
	i = 0;
	while (n)
	{
		res[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (--i > -1)
		printf_addchar(data, res[i]);
}

void	printf_addpointer(t_printf *data, unsigned long n)
{
	char	res[16];
	char	hex_base[16];
	int		i;

	if (!n)
	{
		ft_strncpy(data->res + data->res_i, "(nil)", 5);
		data->res_i += 5;
		return ;
	}
	ft_strncpy(data->res + data->res_i, "0x", 2);
	data->res_i += 2;
	ft_strncpy(hex_base, "0123456789abcdef", 16);
	i = 0;
	while (n)
	{
		res[i++] = hex_base[n % 16];
		n /= 16;
	}
	while (--i > -1)
	{
		*(data->res + data->res_i) = res[i];
		data->res_i++;
	}
}
