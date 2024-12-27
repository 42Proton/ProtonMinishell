/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coderx64 <coderx64@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:34:03 by coderx64          #+#    #+#             */
/*   Updated: 2024/12/27 11:37:03 by coderx64         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_redirection_data(t_redirect *redirect, t_list *lst)
{
	redirect->type = op_type_to_redirection(lst);
	redirect->name = ((t_token *)lst->next->content)->token_word;
}
