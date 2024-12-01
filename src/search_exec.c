/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:25:07 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/01 13:16:50 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*chech_cmd_dir(char *cmd, char *dir)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(dir, tmp);
	if (!tmp2)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	if (!access(tmp2, X_OK))
		return (tmp2);
	free(tmp2);
	return (0);
}

char	*get_exec_path(t_minishell *mini, char *cmd)
{
	char	*path;
	char	**path_split;
	char	*res;
	int		i;

	i = -1;
	path = ft_getenv(mini, "PATH");
	if (!path)
		return (0);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (0);
	while (path_split[++i])
	{
		res = chech_cmd_dir(cmd, path_split[i]);
		if (res)
		{
			free_array((void **)path_split);
			return (res);
		}
	}
	free_array((void **)path_split);
	return (0);
}
