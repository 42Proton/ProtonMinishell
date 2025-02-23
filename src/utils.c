/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:13:04 by amsaleh           #+#    #+#             */
/*   Updated: 2025/02/23 17:54:09 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*get_token_num(t_list *tokens, size_t index)
{
	size_t	i;

	i = 0;
	while (tokens)
	{
		if (i == index)
			return ((t_token *)tokens->content);
		tokens = tokens->next;
		i++;
	}
	return (0);
}

void	line_add_newline(t_minishell *mini)
{
	char	*temp;

	temp = ft_strjoin(mini->line_read, "\n");
	if (!temp)
		exit_handler(mini, ERR_POSTMINI);
	free(mini->line_read);
	mini->line_read = temp;
}

int	get_redirection_type(char *token)
{
	if (!ft_strncmp(token, "<<", 2))
		return (LIMITER_REDIRECTION);
	if (!ft_strncmp(token, ">>", 2))
		return (APPEND_REDIRECTION);
	if (*token == '<')
		return (IN_REDIRECTION);
	if (*token == '>')
		return (OUT_REDIRECTION);
	return (-1);
}

void	cursor_line_back(t_minishell *mini)
{
	char	*up_cap;

	if (mini->is_terminfo_caps_loaded)
	{
		up_cap = tgetstr("up", NULL);
		if (up_cap)
			ft_printf(up_cap);
	}
}

void	start_execution_exits(t_minishell *mini,
	t_exec_status *exec_status)
{
	if (exec_status->status == EXIT_FAILURE)
	{
		mini->last_exit_code = -1;
		exit_handler(mini, ERR_POSTLEXER);
	}
	if (exec_status->is_child || exec_status->is_subshell)
		exit_handler(mini, CHILD_NONE);
	if (exec_status->is_exit)
		exit_handler(mini, NONE);
}
