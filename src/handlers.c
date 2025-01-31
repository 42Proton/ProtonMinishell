/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:56:08 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/31 20:59:34 by amsaleh          ###   ########.fr       */
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

void	free_tokens(void *tokens)
{
	if (((t_token *)tokens)->token_word)
		free(((t_token *)tokens)->token_word);
	free(tokens);
}

void	clear_split_tok(void *content)
{
	t_split_toks	*split_toks;

	split_toks = (t_split_toks *)content;
	ft_lstclear(&split_toks->quotes_ranges, free);
	free(split_toks->str);
	free(content);
}

void	clear_split_tok2(void *content)
{
	t_split_toks	*split_toks;

	split_toks = (t_split_toks *)content;
	ft_lstclear(&split_toks->quotes_ranges, free);
	free(content);
}

void	exit_handler(t_minishell *mini, int error)
{
	int	lec;

	print_error(error);
	if (error == NONE)
		if (set_term_attr_vquit(&mini->term, 1))
			perror("ioctl");
	if (error > ERR_MINI)
	{
		rl_clear_history();
		free(mini->line_read);
		ft_lstclear(&mini->env_lst, clear_env);
		if (error >= ERR_POSTLEXER)
			ft_lstclear(&mini->line_tokens, free_tokens);
		else
			ft_lstclear(&mini->line_tokens, free);
		if (mini->stdin_bak != -1 && mini->stdin_bak != 0)
			close(mini->stdin_bak);
		lec = mini->last_exit_code;
		free(mini);
	}
	exit(lec);
}
