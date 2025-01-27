/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:05:07 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 16:12:22 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list	args;
	int		res;

	va_start(args, fmt);
	res = printf_base(fd, fmt, args);
	va_end(args);
	return (res);
}
