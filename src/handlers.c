/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:56:08 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/08 14:41:35 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	clear_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->data);
	free(env->name);
	free(env);
}

void	clear_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->token_word);
	free(token);
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
		ft_lstclear(&minishell->env_lst, clear_env);
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
