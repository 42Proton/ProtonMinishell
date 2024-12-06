/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:56:08 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/06 13:57:04 by abueskander      ###   ########.fr       */
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

void	free_lst(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}
void	free_tokens(void *tokens)
{
	if(((t_token*)tokens)->token_word)
		free(((t_token *)tokens)->token_word);
	free(tokens);
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
void	free_token_list(t_list	*tokens)
{
	t_list *prev;
	if(!tokens)
		return;
	while(tokens)
	{
		free_tokens(tokens->content);
		prev = tokens;
		tokens = tokens->next;
		free(prev);
	}
}