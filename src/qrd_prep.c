/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qrd_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 02:32:44 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/05 09:25:07 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

void	free_qrd(t_qrd **qrd)
{
	size_t	i;

	i = 0;
	while (qrd[i])
	{
		if (qrd[i]->qrd)
			free_qrd(qrd[i]->qrd);
		ft_lstclear(&qrd[i]->args_qr, free);
		ft_lstclear(&qrd[i]->cmd_qr, free);
		ft_lstclear(&qrd[i]->in_redirects_qr, free);
		ft_lstclear(&qrd[i]->out_redirects_qr, free);
		free(qrd[i]);
		i++;
	}
	free(qrd);
}

static int	qrd_prep_helper(t_qrd **qrd, ssize_t qrd_count)
{
	ssize_t	i;

	i = 0;
	while (i < qrd_count)
	{
		qrd[i] = ft_calloc(1, sizeof(t_qrd));
		if (!qrd[i])
		{
			while (i-- >= 0)
				free(qrd[i]);
			free(qrd);
			return (0);
		}
		i++;
	}
	return (1);
}

static t_qrd	**qrd_prep(t_list *tok)
{
	ssize_t	p_count;
	ssize_t	qrd_count;
	t_qrd	**res;

	p_count = 0;
	qrd_count = 1;
	while (tok && qrd_count > -1)
	{
		if (((t_token *)tok->content)->type == OPEN_PARENTHESIS)
			p_count++;
		else if (((t_token *)tok->content)->type == CLOSE_PARENTHESIS)
			p_count--;
		else if (check_op_type(tok) && !p_count)
			qrd_count++;
		if (p_count < 0)
			break;
		tok = tok->next;
	}
	res = ft_calloc(qrd_count + 1, sizeof(t_qrd *));
	if (!res)
		return (0);
	if (!qrd_prep_helper(res, qrd_count))
		return (0);
	return (res);
}

static int	qrd_process_helper(t_list *tok, t_list **quotes_range_lst,
	t_qrd **qrd, size_t p_count)
{
	t_list	*lst;

	if (p_count)
		return (1);
	if (((t_token *)tok->content)->type == IDENTIFIER)
	{
		while (*quotes_range_lst && (*quotes_range_lst)->content)
		{
			lst = ft_lstnew((*quotes_range_lst)->content);
			if (!lst)
				return (0);
			if (check_in_redirection(tok->prev))
				ft_lstadd_back(&(*qrd)->in_redirects_qr, lst);
			else
				ft_lstadd_back(&(*qrd)->out_redirects_qr, lst);
			*quotes_range_lst = (*quotes_range_lst)->next;
		}
		if (*quotes_range_lst)
			*quotes_range_lst = (*quotes_range_lst)->next;
	}
	if (((t_token *)tok->content)->type == COMMAND
		|| ((t_token *)tok->content)->type == ARGUMENT)
	{
		while (*quotes_range_lst && (*quotes_range_lst)->content)
		{
			lst = ft_lstnew((*quotes_range_lst)->content);
			if (!lst)
				return (0);
			if (((t_token *)tok->content)->type == COMMAND)
			{
				ft_lstadd_back(&(*qrd)->cmd_qr, lst);
				lst = ft_lstnew(0);
				if (!lst)
					return (0);
				ft_lstadd_back(&(*qrd)->args_qr, lst);
			}
			if (((t_token *)tok->content)->type == ARGUMENT)
				ft_lstadd_back(&(*qrd)->args_qr, lst);
			*quotes_range_lst = (*quotes_range_lst)->next;
		}
		lst = ft_lstnew(0);
		ft_lstadd_back(&(*qrd)->args_qr, lst);
	}
	return (1);
}

static int	qrd_process(t_list *tok, t_list *quotes_range_lst, t_qrd **qrd)
{
	ssize_t	p_count;

	p_count = 0;
	while (tok && p_count > -1)
	{
		
		if (((t_token *)tok->content)->type == OPEN_PARENTHESIS)
		{
			(*qrd)->qrd = qrd_setup(tok, quotes_range_lst);
			if (!(*qrd)->qrd)
				return (0);
			p_count++;
		}
		else if (((t_token *)tok->content)->type == CLOSE_PARENTHESIS)
			p_count--;
		else if (check_operator_num(((t_token *)tok->content)->type) && !p_count)
			qrd++;
		if (!qrd_process_helper(tok, &quotes_range_lst, qrd, p_count))
			return (0);
		tok = tok->next;
		if (quotes_range_lst)
			quotes_range_lst = quotes_range_lst->next;
	}
	return (1);
}

t_qrd	**qrd_setup(t_list *tok, t_list *quotes_range_lst)
{
	t_qrd	**qrd;

	if (((t_token *)tok->content)->type == OPEN_PARENTHESIS)
		tok = tok->next;
	qrd = qrd_prep(tok);
	if (!qrd)
		return (0);
	if (!qrd_process(tok, quotes_range_lst, qrd))
	{
		free_qrd(qrd);
		return (0);
	}
	return (qrd);
}
