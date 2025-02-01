/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_extra2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:35:21 by bismail           #+#    #+#             */
/*   Updated: 2025/02/01 11:37:35 by amsaleh          ###   ########.fr       */
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
	t_list *temp = *split_toks;
while (temp)
{
	printf("STRING: %s\n", ((t_split_toks *)temp->content)->str);
	t_list *quotes_ranges_temp = ((t_split_toks *)temp->content)->quotes_ranges;
	while (quotes_ranges_temp)
	{
		printf("QR: %ld %ld\n", ((t_qr *)quotes_ranges_temp->content)->arr[0], ((t_qr *)quotes_ranges_temp->content)->arr[1]);
		printf("QR EMPTY: %d\n", ((t_qr *)quotes_ranges_temp->content)->is_empty);
		quotes_ranges_temp = quotes_ranges_temp->next;
	}
	temp = temp->next;
}
	return (1);
}

void	exp_qtr_helper(char **content,
	t_tok_expander *tok_exp, t_list **split_toks, size_t env_len)
{
	if (tok_exp->split_se.end > tok_exp->i_temp2)
		exp_prep_qtr_next(content, split_toks, tok_exp);
	exp_qtr_quit_env(tok_exp, env_len);
}
