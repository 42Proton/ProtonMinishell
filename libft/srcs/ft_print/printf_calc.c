/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:25:50 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 03:28:53 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static size_t	printf_strlen(char *s)
{
	if (!s)
		return (6);
	return (ft_strlen(s));
}

static size_t	printf_hexlen(unsigned int n)
{
	size_t	res;

	res = 0;
	if (!n)
		return (1);
	while (n)
	{
		res++;
		n /= 16;
	}
	return (res);
}

static size_t	printf_pointerlen(unsigned long n)
{
	size_t	res;

	res = 2;
	if (!n)
		return (5);
	while (n)
	{
		res++;
		n /= 16;
	}
	return (res);
}

static size_t	printf_unbrlen(unsigned int n)
{
	size_t	res;

	res = 0;
	if (!n)
		return (1);
	while (n)
	{
		res++;
		n /= 10;
	}
	return (res);
}

void	printf_base_calc(t_printf *data, va_list args)
{
	char	c;

	c = data->fmt[data->end + 1];
	if (c == 's')
		data->res_len += printf_strlen(va_arg(args, char *));
	if (c == 'x' || c == 'X')
		data->res_len += printf_hexlen(va_arg(args, unsigned int));
	if (c == 'c' || c == '%')
	{
		va_arg(args, int);
		data->res_len++;
	}
	if (c == 'd' || c == 'i')
		data->res_len += printf_nbrlen(va_arg(args, int));
	if (c == 'p')
		data->res_len += printf_pointerlen(va_arg(args, unsigned long));
	if (c == 'u')
		data->res_len += printf_unbrlen(va_arg(args, unsigned int));
}
