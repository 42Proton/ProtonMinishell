/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:28:24 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/14 03:19:26 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static unsigned long long	atoull(char *nptr)
{
	
	unsigned long long	res;
	int	sign;

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
	return (1);
}
static int	check_if_str_real(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return EXIT_FAILURE;
		i++;
	}
	return (EXIT_SUCCESS);
}
static int	validate_args(char **args)
{
	int	i;

	(void)args;
	i = 0;
	while (args[++i]);
	if (i > 2)
	{
		ft_dprintf(STDOUT_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (i == 2 && (check_if_str_real(args[1]) || atoull(args[1]) > LLONG_MAX))
	{
		ft_dprintf(STDOUT_FILENO, "minishell: exit: %s: numeric argument required\n",args[1]);
		return (2);
	}

	return 0;
}
void	exit_cmd(t_op_ref *op_ref, char **args)
{
	int	vald;

	vald = validate_args(args);
	if(vald)
		*op_ref->lec = vald;
	else if(args[1])
		*op_ref->lec = atoull(args[1]) % 256;
	else
		*op_ref->lec = 0;
	op_ref->is_exit = 1;
}