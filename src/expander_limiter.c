/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_limiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:29:02 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/26 18:18:39 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exp_limiter_prep(t_split_toks *split_tok,
	char *tok, t_list **split_toks)
{
	split_tok->quotes_ranges = 0;
	split_tok->str = ft_strdup(tok);
	if (!split_tok->str)
	{
		free(split_tok);
		return (0);
	}
	*split_toks = ft_lstnew(split_tok);
	if (!*split_toks)
	{
		clear_split_tok(split_tok);
		return (0);
	}
	if (!expander_qtr(tok, *split_toks, 0, 0))
	{
		ft_lstclear(split_toks, clear_split_tok);
		return (0);
	}
	return (1);
}

char	*exp_limiter(char *tok)
{
	t_list			*split_toks;
	t_split_toks	*split_tok;
	char			*res;

	split_tok = malloc(sizeof(t_split_toks));
	if (!split_tok)
		return (0);
	if (!exp_limiter_prep(split_tok, tok, &split_toks))
		return (0);
	if (!exp_rm_qt(split_toks))
		return (0);
	res = split_tok->str;
	ft_lstclear(&split_tok->quotes_ranges, free);
	free(split_tok);
	free(split_toks);
	return (res);
}
