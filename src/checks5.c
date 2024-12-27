/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:49:21 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/27 11:49:23 by amsaleh          ###   ########.fr       */
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

int	check_prep_redirect_condition(t_list *lst, ssize_t parenthesis_count)
{
	if (lst && !(check_op_type(lst) && !parenthesis_count)
	&& parenthesis_count >= 0)
		return (1);
	return (0);
}