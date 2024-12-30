/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:49:21 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/30 13:53:13 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_in_redirection(t_list *lst)
{
	if (((t_token *)lst->content)->type == LIMITER_REDIRECTION
		|| ((t_token *)lst->content)->type == IN_REDIRECTION)
		return (1);
	return (0);
}

int	check_out_redirection(t_list *lst)
{
	if (((t_token *)lst->content)->type == OUT_REDIRECTION
		|| ((t_token *)lst->content)->type == APPEND_REDIRECTION)
		return (1);
	return (0);
}

int	check_op_prep_condition(t_list *lst, ssize_t parenthesis_count)
{
	if (lst && !(check_op_type(lst) && !parenthesis_count)
	&& parenthesis_count >= 0)
		return (1);
	return (0);
}

int	check_tok_prev_cmd(t_list *lst)
{
	t_list	*last;

	last = ft_lstlast(lst);
	while (last)
	{
		if (((t_token *)last->content)->type == COMMAND)
			return (1);
		if (check_op_type(last)
			|| ((t_token *)last->content)->type == OPEN_PARENTHESIS)
			return (0);
		last = last->prev;
	}
	return (0);
}

int	check_if_batata_path(char *cmd)
{
	if (!ft_strncmp(cmd, "../", 3)
		|| !ft_strncmp(cmd, "./", 2)
		|| ft_strchr(cmd, '/'))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}