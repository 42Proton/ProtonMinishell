/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:28:24 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/15 01:44:52 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static unsigned long long	ft_atoull(char *nptr)
{
	unsigned long long	res;

	res = 0;
	while (*nptr == 32 || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
		res = res * 10 + *(nptr++) - '0';
	return (res);
}

static long long	ft_atoll(char *nptr)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			sign = -1;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
		res = res * 10 + *(nptr++) - '0';
	return (res * sign);
}

static int	check_if_str_real(char *str)
{
	int	i;

	i = 0;
	while (*str == 32 || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str == 48)
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || i > 18)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	get_num_sign(char *str)
{
	while (*str == 32 || (*str >= '\t' && *str <= '\r'))
		str++;
	if (ft_isdigit(*str) || *str == '+')
		return (1);
	return (-1);
}

static int	validate_args(char **args)
{
	int	i;
	int	sign;

	i = 1;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (i == 2)
	{
		sign = get_num_sign(args[1]);
		if (check_if_str_real(args[1])
			|| (sign == 1 && ft_atoull(args[1]) > LLONG_MAX)
			|| (sign == -1 && ft_atoull(args[1]) > LLONG_MAX + 1ULL))
		{
			ft_dprintf(STDERR_FILENO, "minishell: exit: %s: numeric argument required\n",args[1]);
			return (2);
		}
	}
	return (0);
}
void	exit_cmd(t_op_ref *op_ref, char **args)
{
	int	vald;

	vald = validate_args(args);
	if (vald)
		*op_ref->lec = vald;
	else if (args[1])
		*op_ref->lec = ft_atoll(args[1]);
	else
		*op_ref->lec = 0;
	op_ref->is_exit = 1;
}