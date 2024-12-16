/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bismail <bismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:23 by bismail           #+#    #+#             */
/*   Updated: 2024/12/16 14:31:20 by bismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	separator_counter(t_list *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		if (((t_token *)lst->content)->type >= AND_OPERATOR
			&& ((t_token *)lst->content)->type <= APPEND_REDIRECTION)
			counter++;
		lst = lst->next;
	}
	return (counter);
}

static t_list	*find_middle_sep(t_list *lst)
{
	int	counter;
	int	target_index;

	counter = separator_counter(lst);
	target_index = -1;
	ft_printf("Counter =  %d\n", counter);
	if (counter != 0)
		target_index = counter / 2 + 1;
	else
		return (NULL);
	while (lst->next)
	{
		if (((t_token *)lst->content)->type >= 2
			&& ((t_token *)lst->content)->type <= 9)
		{
			if (target_index)
				target_index--;
			if (!target_index)
				return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}

int	execute_process(t_list *mini)
{
	t_list	*temp_tok;
	t_list	*middle_sep;

	temp_tok = mini;
	middle_sep = find_middle_sep(temp_tok);
	if (middle_sep)
		ft_printf("%s \n", ((t_token *)middle_sep->content)->token_word);
	else
		ft_printf("NO separator\n");
	if (middle_sep)
	{
		middle_sep->prev->next = NULL;
		execute_process(mini);
		execute_process(middle_sep->next);
	}
	return (1);
}

// The execution process will act as a tree,
// 	as every line parsed will be divided into Segaments.

// 1- We loop across all Tokens to find the middle separator.
// 2- Then we shall get rerun the function from the first Separator until Null and the second Separator until Null.
// 3- Now each command would be divided into 2 halfs,
// 	which will have to do the same function over and over again until.
