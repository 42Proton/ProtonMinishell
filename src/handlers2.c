/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:08:04 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/13 22:08:36 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_token_list(t_list *tokens)
{
	t_list	*prev;

	if (!tokens)
		return ;
	while (tokens)
	{
		free_tokens(tokens->content);
		prev = tokens;
		tokens = tokens->next;
		free(prev);
	}
}
