/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:42:56 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 19:56:00 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	extract_digits(int *temp, int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i++;
		temp[i] = n % 10;
		n /= 10;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	i;
	int	temp[11];

	if (!n)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	i = extract_digits(temp, n);
	while (i > 0)
	{
		ft_putchar_fd(temp[i] + 0x30, fd);
		i--;
	}
}
