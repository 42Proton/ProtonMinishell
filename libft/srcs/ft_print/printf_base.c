/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:49:24 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 16:26:17 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	get_start_end(t_printf *data)
{
	int	i;

	i = data->start;
	while (data->fmt[i])
	{
		if (data->fmt[i] == '%')
		{
			data->end = i;
			return ;
		}
		i++;
	}
	data->end = i;
}

static int	prep_printf_base(t_printf *data, va_list args)
{
	va_list	args_cpy;

	va_copy(args_cpy, args);
	while (data->end < data->fmt_len)
	{
		data->start = data->end;
		get_start_end(data);
		data->res_len += data->end - data->start;
		if (data->fmt[data->end] == '%')
			printf_base_calc(data, args_cpy);
		data->end += 2;
	}
	data->res = malloc(data->res_len + 1);
	if (!data->res)
		return (-1);
	data->res[data->res_len] = 0;
	va_end(args_cpy);
	return (1);
}

static void	printf_base_iter(t_printf *data, va_list args)
{
	while (data->end < data->fmt_len)
	{
		data->start = data->end;
		get_start_end(data);
		if (data->end != data->start)
		{
			ft_strncpy(data->res + data->res_i,
				data->fmt + data->start, data->end - data->start);
			data->res_i += data->end - data->start;
		}
		if (data->fmt[data->end] == '%')
			process_data(data, args);
		data->end += 2;
	}
}

static int	printf_safe_return(size_t len)
{
	int	res;

	res = (int)len;
	if (res < 0)
	{
		if (res == INT_MIN)
			res++;
		res *= -1;
	}
	return (res);
}

int	printf_base(int fd, const char *fmt, va_list args)
{
	t_printf	data;
	int			res;

	ft_bzero(&data, sizeof(t_printf));
	data.fmt_len = ft_strlen(fmt);
	data.fmt = fmt;
	if (!prep_printf_base(&data, args))
		return (-1);
	data.end = 0;
	data.start = 0;
	printf_base_iter(&data, args);
	res = write(fd, data.res, data.res_len);
	free(data.res);
	if (res)
		return (res);
	return (printf_safe_return(data.res_len));
}
