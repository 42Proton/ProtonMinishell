/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:13:04 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/28 15:20:41 by abueskander      ###   ########.fr       */
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
			tputs(up_cap, 1, putchar);
	}
}

void	start_execution_exits(t_minishell *mini,
	int status, int is_exit, int is_child)
{
	if (status == EXIT_FAILURE)
	{
		mini->last_exit_code = -1;
		exit_handler(mini, ERR_POSTLEXER);
	}
	if (is_exit && is_child)
		exit_handler(mini, CHILD_NONE);
	if (is_exit)
		exit_handler(mini, NONE);
}
