/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_digits_amount.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:37:23 by amsaleh           #+#    #+#             */
/*   Updated: 2024/09/04 16:37:24 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_digits_amount(int n)
{
	int	num;
	int	res;

	num = n;
	res = 0;
	if (num == -2147483648)
		return (10);
	if (num == 0)
		return (1);
	if (num < 0)
		num *= -1;
	while (num > 0)
	{
		num /= 10;
		res++;
	}
	return (res);
}
