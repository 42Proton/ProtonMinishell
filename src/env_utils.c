/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:25:10 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/10 22:42:33 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(t_env *env)
{
	free(env->name);
	free(env->data);
	free(env);
}

void	shell_level(t_minishell *mini, t_list *env_lst)
{
	char	*new_level;
	t_env	*env;

	while (env_lst)
	{
		env = (t_env *)env_lst->content;
		if (!ft_strcmp(env->name, "SHLVL"))
			break;
		env_lst = env_lst->next;
	}
	new_level = ft_itoa(ft_atoi(env->data) + 1);
	if (!new_level)
		exit_handler(mini, ERR_MALLOC_POSTMINI);
	free(env->data);
	env->data = new_level;
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
	return (i);
}

void	prep_minishell_env(t_minishell *mini, char **ev)
{
	t_env	*env;
	t_list	*lst;

	while (*ev)
	{
		env = ft_calloc(1, sizeof(t_env));
		if (!env)
			exit_handler(mini, ERR_MALLOC_POSTMINI);
		if (!parse_env_data(*ev, env))
		{
			free_env(env);
			exit_handler(mini, ERR_MALLOC_POSTMINI);
		}
		lst = ft_lstnew(env);
		if (!lst)
		{
			free_env(env);
			exit_handler(mini, ERR_MALLOC_POSTMINI);
		}
		ft_lstadd_back(&mini->env_lst, lst);
		ev++;
	}
	shell_level(mini, mini->env_lst);
}

char	*ft_getenv(t_list *env_lst, char *env_name)
{
	t_list	*lst;
	t_env	*env;

	lst = env_lst;
	while (lst)
	{
		env = (t_env *)lst->content;
		if (!ft_strcmp(env->name, env_name))
			return (env->data);
		lst = lst->next;
	}
	return (0);
}
