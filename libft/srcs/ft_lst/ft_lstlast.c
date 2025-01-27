/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:30:36 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 19:56:11 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	if (!lst || !lst->next)
		return (lst);
	node = lst->next;
	while (node->next)
		node = node->next;
	return (node);
}
