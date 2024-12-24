/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coderx64 <coderx64@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:23 by bismail           #+#    #+#             */
/*   Updated: 2024/12/25 01:20:03 by coderx64         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static t_list	*find_middle_sep(t_list *lst)
// {
// 	int	counter;
// 	int	target_index;

// 	counter = separator_counter(lst);
// 	target_index = -1;
// 	ft_printf("Counter =  %d\n", counter);
// 	if (counter != 0)
// 		target_index = counter / 2 + 1;
// 	else
// 		return (NULL);
// 	while (lst->next)
// 	{
// 		if (((t_token *)lst->content)->type >= 2
// 			&& ((t_token *)lst->content)->type <= 9)
// 		{
// 			if (target_index)
// 				target_index--;
// 			if (!target_index)
// 				return (lst);
// 		}
// 		lst = lst->next;
// 	}
// 	return (NULL);
// }

// int	execute_process(t_minishell *mini)
// {
// 	t_list	*temp_tok;
// 	t_list	*middle_sep;

// 	temp_tok = mini;
// 	middle_sep = find_middle_sep(temp_tok);
// 	if (middle_sep)
// 		ft_printf("%s \n", ((t_token *)middle_sep->content)->token_word);
// 	else
// 		ft_printf("NO separator\n");
// 	if (middle_sep)
// 	{
// 		middle_sep->prev->next = NULL;
// 		execute_process(mini);
// 		execute_process(middle_sep->next);
// 	}
// 	return (1);
// }

// The execution process will act as a tree,
// 	as every line parsed will be divided into Segaments.

// 1- We loop across all Tokens to find the middle separator.
// 2- Then we shall get rerun the function from the first Separator until Null and the second Separator until Null.
// 3- Now each command would be divided into 2 halfs,
// 	which will have to do the same function over and over again until.

static ssize_t	main_separators_counter(t_list *lst)
{
	ssize_t	counter;
	size_t	parenthesis_count;

	parenthesis_count = 0;
	counter = 0;
	while (lst)
	{
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		else if (((t_token *)lst->content)->type >= AND_OPERATOR
			&& ((t_token *)lst->content)->type <= PIPE && !parenthesis_count)
			counter++;
		lst = lst->next;
	}
	return (counter);
}

static int	switch_operations(int	oper_type)
{
	if (oper_type == PIPE)
		return (OPERATION_PIPE);
	if (oper_type == AND_OPERATOR)
		return (OPERATION_AND);
	if (oper_type == OR_OPERATOR)
		return (OPERATION_OR);
	return (OPERATION_DEFAULT);
}

static int	add_operation_alloc(t_operation	**operations, ssize_t *i)
{
	t_operation *temp;
	
	temp = malloc(sizeof(t_operation));
	if (!temp)
	{
		while (--(*i) > -1)
			free(operations[*i]);
		return (0);
	}
	temp->operation_type = switch_operations(-1);
	operations[*i] = temp;
	(*i)++;
	return (1);
}

static t_operation **main_operations_alloc(t_list *lst, ssize_t sep_count)
{
	t_operation  **operations;
	ssize_t		i;

	i = 0;
	operations = ft_calloc(sizeof(void *), sep_count + 1);
	if (!add_operation_alloc(operations, &i))
		return (0);
	while (lst)
	{
		if (((t_token *)lst->content)->type >= AND_OPERATOR
		&& ((t_token *)lst->content)->type <= PIPE)
			if (!add_operation_alloc(operations, &i))
				return (0);
		lst = lst->next;
	}
	return (operations);
}

int	execute_process(t_minishell *mini)
{
	ssize_t		sep_count;
	t_operation	**operations; 
	
	sep_count = main_separators_counter(mini->line_tokens);
	operations = main_operations_alloc(mini->line_tokens, sep_count);
	if (!operations)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
