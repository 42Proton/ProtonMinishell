/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:10:14 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 16:12:26 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		res;

	va_start(args, fmt);
	res = printf_base(STDOUT_FILENO, fmt, args);
	va_end(args);
	return (res);
}
