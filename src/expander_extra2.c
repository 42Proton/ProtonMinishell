/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_extra2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bismail <bismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:35:21 by bismail           #+#    #+#             */
/*   Updated: 2025/01/22 15:52:29 by bismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	token_expander_helper(t_list *split_toks, t_list *res_toks,
		t_list **tokens)
{
	ft_lstclear(&split_toks, clear_split_tok);
	ft_lstclear(&res_toks, free);
	free_lst(*tokens);
	return (0);
}

int	token_expander_helper2(t_list **split_toks, t_op_ref *op_ref, char *s)
{
	if (!expander_qtr(s, *split_toks, op_ref))
	{
		ft_lstclear(split_toks, clear_split_tok);
		return (0);
	}
	return (1);
}
