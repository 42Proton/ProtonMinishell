/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coderx64 <coderx64@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 09:56:13 by coderx64          #+#    #+#             */
/*   Updated: 2024/12/27 10:03:44 by coderx64         ###   ########.fr       */
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
