/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:41:14 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/15 01:19:08 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node_next;
	t_list	*node;

	if (!lst)
		return ;
	node = *lst;
	if (!node || !del)
		return ;
	while (node)
	{
		del(node->content);
		node_next = node->next;
		free(node);
		node = node_next;
	}
	*lst = 0;
}
