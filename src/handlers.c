/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:56:08 by abueskander       #+#    #+#             */
/*   Updated: 2024/11/28 18:56:58 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_lstclear_env(t_list **lst, void (*del)(void *))
{
	t_list	*node_next;
	t_list	*node;
	t_env	*env;

	node = *lst;
	if (!node || !del)
		return ;
	while (node)
	{
		env = (t_env *)node->content;
		del(env->data);
		del(env->name);
		del(node->content);
		node_next = node->next;
		del(node);
		node = node_next;
	}
	*lst = 0;
}

void	exit_handler(t_minishell *minishell, int error)
{
	print_error(error);
	if (error > ERR_MALLOC)
	{
		rl_clear_history();
		free(minishell->cwd);
		free(minishell->line_read);
		ft_lstclear_env(&minishell->env_lst, free);
		free(minishell);
	}
	if (error != NONE)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
