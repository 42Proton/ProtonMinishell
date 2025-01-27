/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:07:27 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 16:12:50 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <libft.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_printf
{
	size_t		start;
	size_t		end;
	size_t		fmt_len;
	size_t		res_i;
	size_t		res_len;
	const char	*fmt;
	char		*res;
}	t_printf;

int		ft_printf(const char *fmt, ...);
int		ft_dprintf(int fd, const char *fmt, ...);
int		printf_base(int fd, const char *fmt, va_list args);
void	printf_base_calc(t_printf *data, va_list args);
int		printf_nbrlen(int n);
void	printf_addnbr(t_printf *data, int n);
void	printf_addunbr(t_printf *data, unsigned int n);
void	printf_addpointer(t_printf *data, unsigned long n);
void	printf_addstr(t_printf *data, char *s);
void	printf_addchar(t_printf *data, char c);
void	printf_addhex(t_printf *data, unsigned int n, int mode);
void	process_data(t_printf *data, va_list args);

#endif
