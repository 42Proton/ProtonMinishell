/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:16 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/28 15:12:52 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	quicksig_handle(t_minishell *mini)
{
	if (!g_signum)
		mini->unclean_mode = 0;
	signal_handler(SIG_UPDATE_SIGNUM);
	if (g_signum)
	{
		mini->last_exit_code = 130;
		free(mini->line_read);
		return (1);
	}
	return (0);
}

int	sort_print_env_helper2_util(char **res, t_env *env)
{
	char	*temp;

	temp = ft_strjoin2(*res, "=", STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin2(*res, "\"", STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin2(*res, env->data, STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin2(*res, "\"", STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	return (1);
}

size_t	get_envlst_size(t_list *env_lst)
{
	size_t	res;

	res = 0;
	while (env_lst)
	{
		if (((t_env *)env_lst->content)->mode)
			res++;
		env_lst = env_lst->next;
	}
	return (res);
}

void	echo_iteraite_flag(char ***args, int *newline)
{
	size_t	i;

	i = 1;
	while ((*args)[i] && !ft_strncmp((*args)[i], "-n", 2))
	{
		if (check_valid_flag((*args)[i]))
		{
			*newline = 0;
			(*args) += 1;
			continue ;
		}
		i++;
	}
}

void	cmd_cmd_helper(char **args, size_t i, t_op_ref *op_ref)
{
	if (args[i + 1])
		ft_dprintf(STDERR_FILENO, "Proton: cd: too many arguments\n");
	if (args[i + 1])
		*op_ref->lec = 1;
	else
	{
		if (chdir(args[i]) == -1)
		{
			perror("Proton: cd");
			*op_ref->lec = 1;
		}
	}
}
