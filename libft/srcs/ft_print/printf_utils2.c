/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:19:51 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 15:59:13 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	printf_addstr(t_printf *data, char *s)
{
	size_t	len;

	if (!s)
	{
		ft_strncpy(data->res + data->res_i, "(null)", 6);
		data->res_i += 6;
		return ;
	}
	len = ft_strlen(s);
	ft_strncpy(data->res + data->res_i, s, len);
	data->res_i += len;
}

void	printf_addchar(t_printf *data, char c)
{
	*(data->res + data->res_i) = c;
	data->res_i++;
}

void	printf_addhex(t_printf *data, unsigned int n, int mode)
{
	char	res[8];
	char	hex_base[16];
	int		i;

	if (!n)
	{
		printf_addchar(data, '0');
		return ;
	}
	i = 0;
	if (!mode)
		ft_strncpy(hex_base, "0123456789abcdef", 16);
	else
		ft_strncpy(hex_base, "0123456789ABCDEF", 16);
	while (n)
	{
		res[i++] = hex_base[n % 16];
		n /= 16;
	}
	while (--i > -1)
		printf_addchar(data, res[i]);
}

void	process_data(t_printf *data, va_list args)
{
	char	c;

	c = data->fmt[data->end + 1];
	if (c == 's')
		printf_addstr(data, va_arg(args, char *));
	if (c == 'x')
		printf_addhex(data, va_arg(args, unsigned int), 0);
	if (c == 'X')
		printf_addhex(data, va_arg(args, unsigned int), 1);
	if (c == 'c')
		printf_addchar(data, va_arg(args, int));
	if (c == 'd' || c == 'i')
		printf_addnbr(data, va_arg(args, int));
	if (c == 'p')
		printf_addpointer(data, va_arg(args, unsigned long));
	if (c == 'u')
		printf_addunbr(data, va_arg(args, unsigned int));
	if (c == '%')
		printf_addchar(data, '%');
}
