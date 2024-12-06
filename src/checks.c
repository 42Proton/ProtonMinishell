/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:18:52 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/06 13:40:35 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_sep(char *line)
{
	if (!ft_strncmp(line, "&&", 2))
		return (2);
	if (!ft_strncmp(line, "||", 2))
		return (2);
	if (!ft_strncmp(line, "<<", 2))
		return (2);
	if (!ft_strncmp(line, ">>", 2))
		return (2);
	if (!ft_strncmp(line, "<>", 2))
		return (2);
	if (*line == '|' || *line == '(' || *line == ')')
		return (1);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}
int	check_if_command(char *token,t_list *envs)
{
	char **allpaths;
	char *temp;
	int i;

	i = 0;
	while(envs && ft_strcmp(((t_env *)envs->content)->name,"PATH"))
                envs = envs->next;
	allpaths =  ft_split(((t_env *)envs->content)->data,':');
	if(access(token,X_OK) == 0)
		return (1);
	while (allpaths[i])
	{
		temp = ft_strjoin(allpaths[i],"/");
		free(allpaths[i]);
		allpaths[i] = temp;
		temp = ft_strjoin(allpaths[i],token);
		free(allpaths[i]);
		allpaths[i] = temp;
		if(access(allpaths[i],X_OK) == 0)
			return (1);
		i++;
	}
	free_array((void **)allpaths);
	return (0);
}

int	check_if_environ(char *token,t_list *envs)
{
	while(envs)
	{
		if(ft_strcmp(((t_env *)envs->content)->name,token) == 0)
		return (1);
   		envs = envs->next;
	}
	return(0);
}
int	check_if_builtin(char *token)
{
	if (ft_strncmp(token,"cd",2) == 0)
		return (1);
	if (ft_strcmp(token,"export") == 0)
		return (1);
	if (ft_strcmp(token,"unset") == 0)
		return (1);
	if (ft_strcmp(token, "pwd") == 0)
		return (1);
	if (ft_strcmp(token, "env") == 0)
		return (1);
	return (0);
}
