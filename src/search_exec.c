/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:25:07 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/27 21:36:41 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*chech_cmd_dir(char *cmd, char *dir, char *tmp_ref)
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
	if (!access(tmp2, F_OK))
		return (tmp2);
	free(tmp2);
	return (tmp_ref);
}

static char	*search_exec_path(char **path_split, char *cmd, char *tmp)
{
	size_t	i;
	char	*res;

	i = 0;
	while (path_split[i])
	{
		res = chech_cmd_dir(cmd, path_split[i], tmp);
		if (res && *res)
		{
			free_array((void **)path_split);
			return (res);
		}
		else if (!res)
		{
			free_array((void **)path_split);
			return (0);
		}
		i++;
	}
	free_array((void **)path_split);
	return (tmp);
}

char	*get_exec_path(t_op_ref *op_ref, char *cmd)
{
	char	*path;
	char	**path_split;
	char	*res;
	char	*tmp;

	tmp = ft_strdup("");
	if (!*cmd)
		return (tmp);
	path = ft_getenv(*op_ref->env_lst, "PATH");
	if (!path)
		return (tmp);
	path_split = ft_split(path, ':');
	if (!path_split)
	{
		free(tmp);
		return (0);
	}
	res = search_exec_path(path_split, cmd, tmp);
	if ((res && *res) || !res)
		free(tmp);
	if (res && *res)
		return (res);
	if (!res)
		return (0);
	return (tmp);
}
