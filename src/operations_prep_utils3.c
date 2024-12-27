/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:50:44 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/27 11:50:47 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_redirection_data(t_redirect *redirect, t_list *lst)
{
	redirect->type = op_type_to_redirection(lst);
	redirect->name = ((t_token *)lst->next->content)->token_word;
}
