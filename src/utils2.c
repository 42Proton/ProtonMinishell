/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:51:13 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/27 11:51:15 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	op_type_to_redirection(t_list *lst)
{
	if (((t_token *)lst->content)->type == IN_REDIRECTION)
		return (REDIRECT_INFILE);
	if (((t_token *)lst->content)->type == OUT_REDIRECTION)
		return (REDIRECT_OUTFILE);
	if (((t_token *)lst->content)->type == APPEND_REDIRECTION)
		return (REDIRECT_APPEND);
	if (((t_token *)lst->content)->type == LIMITER_REDIRECTION)
		return (REDIRECT_LIMITER);
	return (-1);
}
