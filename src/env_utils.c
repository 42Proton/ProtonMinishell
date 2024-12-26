/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:25:10 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/26 09:30:21 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(t_env *env)
{
	free(env->name);
	free(env->data);
	free(env);
}

int	parse_env_data(char *data, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (data[i] != '=')
		i++;
	i++;
	env->name = malloc(i * sizeof(char));
	if (!env->name)
		return (0);
	ft_strlcpy(env->name, data, i);
	j = i;
	while (data[j])
		j++;
	if (j == i)
		env->data = ft_strdup("");
	else
		env->data = malloc(((j - i) + 1) * sizeof(char));
	if (!env->data)
		return (0);
	if (j != i)
		ft_strlcpy(env->data, data + i, (j - i) + 1);
	return (1);
}

void	prep_minishell_env(t_minishell *minishell, char **ev)
{
	t_env	*env;
	t_list	*lst;

	while (*ev)
	{
		env = ft_calloc(1, sizeof(t_env));
		if (!env)
			exit_handler(minishell, ERR_MALLOC_POSTMINI);
		if (!parse_env_data(*ev, env))
		{
			free_env(env);
			exit_handler(minishell, ERR_MALLOC_POSTMINI);
		}
		lst = ft_lstnew(env);
		if (!lst)
		{
			free_env(env);
			exit_handler(minishell, ERR_MALLOC_POSTMINI);
		}
		ft_lstadd_back(&minishell->env_lst, lst);
		ev++;
	}
}

char	*ft_getenv(t_minishell *minishell, char *env_name)
{
	t_list	*lst;
	t_env	*env;

	lst = minishell->env_lst;
	while (lst)
	{
		env = (t_env *)lst->content;
		if (!ft_strcmp(env->name, env_name))
			return (env->data);
		lst = lst->next;
	}
	return (0);
}
