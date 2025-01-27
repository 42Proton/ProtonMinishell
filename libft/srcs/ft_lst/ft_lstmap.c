/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:07:35 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 19:56:10 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static t_list	*init(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*content;
	t_list	*new_lst;

	if (!lst || !f || !del)
		return (0);
	content = f(lst->content);
	new_lst = ft_lstnew(content);
	if (!new_lst)
	{
		del(content);
		return (0);
	}
	return (new_lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*first_lst;
	void	*content;

	first_lst = init(lst, f, del);
	if (!first_lst)
		return (0);
	node = first_lst;
	while (lst->next)
	{
		lst = lst->next;
		content = f(lst->content);
		node->next = ft_lstnew(content);
		if (!node->next)
		{
			del(content);
			ft_lstclear(&first_lst, del);
			return (0);
		}
		node = node->next;
	}
	return (first_lst);
}
