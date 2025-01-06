/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:44:36 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/06 09:22:18 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:57:19 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/05 09:59:23 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	get_arr_len(void **arr)
{
	size_t	res;

	res = 0;
	while (arr[res])
		res++;
	return (res);
}

int	expander_update_operation(t_operation *operation, t_list *tokens)
{
	char	**args;
	size_t	lst_size;
	size_t	i;

	operation->cmd = tokens->content;
	tokens = tokens->next;
	lst_size = ft_lstsize(tokens);
	args = ft_calloc(lst_size + 2, sizeof(char *));
	if (!args)
		return (0);
	i = 1;
	args[0] = operation->cmd_path;
	while (i < lst_size + 1)
	{
		args[i] = (char *)tokens->content;
		tokens = tokens->next;
		i++;
	}
	free_array((void **)operation->args);
	operation->args = args;
	return (1);
}

int	execute_expander(int lec, t_list *env_lst, t_operation *operation)
{
	t_list	*tokens;
	char	**args;

	tokens = 0;
	if (operation->cmd)
	{
		token_expander(operation->cmd, &tokens, env_lst, lec);
		args = operation->args;
		args++;
		if (get_arr_len((void **)args) > 0)
		{
			while (*args)
			{
				token_expander(*args, &tokens, env_lst, lec);
				args++;
			}
		}
		expander_update_operation(operation, tokens);
		free_lst(tokens);
	}
	return (1);
}
