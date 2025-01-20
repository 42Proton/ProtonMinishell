/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:05:04 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/20 17:06:34 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	env_cmd_helper(char **res, t_env *env)
{
	char	*temp;

	temp = ft_strjoin2(*res, env->name, STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin2(*res, "=", STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin2(*res, env->data, STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	temp = ft_strjoin2(*res, "\n", STRJOIN_FS1);
	if (!temp)
		return (0);
	*res = temp;
	return (1);
}

int	env_cmd(t_op_ref *op_ref)
{
	t_list	*lst;
	char	*res;

	lst = *op_ref->env_lst;
	res = ft_strdup("");
	if (!res)
		return (EXIT_FAILURE);
	while (lst)
	{
		if (!env_cmd_helper(&res, (t_env *)lst->content))
			return (EXIT_FAILURE);
		lst = lst->next;
	}
	ft_printf("%s", res);
	free(res);
	return (EXIT_SUCCESS);
}

void	unset_cmd(t_op_ref *op_ref, char **args)
{
	args++;
	while (*args)
	{
		ft_unsetenv(op_ref->env_lst, *args);
		args++;
	}
}
