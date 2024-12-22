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

static ssize_t	separator_counter(t_list *lst)
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
static t_operation **operations_collecter(t_list *lst, ssize_t sep_count)
{
	t_operation  **operations;
	t_operation *temp;
	ssize_t		i;

	i = 0;
	operations = ft_calloc(sizeof(void *), sep_count + 1);
	temp = malloc(sizeof(t_operation));
	temp->operation_type = switch_operations(-1);
	operations[i] = temp;
	i++;
	while(lst && i <= sep_count)
	{
		if (((t_token *)lst->content)->type >= AND_OPERATOR
		&& ((t_token *)lst->content)->type <= PIPE)
		{
			temp = malloc(sizeof(t_operation));
			
			temp->operation_type = switch_operations(((t_token *)lst->content)->type);
			operations[i] = temp;
			i++;
		}
		lst = lst->next;
	}
	return (operations);
}

int	execute_process(t_minishell *mini)
{
	ssize_t	sep_count;
	t_operation 	**operations; 
	//t_redirect	*redirections;
	sep_count =  separator_counter(mini->line_tokens);
	operations = operations_collecter(mini->line_tokens,sep_count);
	if (!operations)
		return (EXIT_FAILURE);
	printf("%ld %d\n",sep_count, operations[0]->operation_type);
	printf("%ld %d\n",sep_count, operations[1]->operation_type);
	//redirections = redirections_collecter(mini, operations);
	return (EXIT_SUCCESS);
}

// The execution process will act as a tree,
// 	as every line parsed will be divided into Segaments.

// 1- We loop across all Tokens to find the middle separator.
// 2- Then we shall get rerun the function from the first Separator until Null and the second Separator until Null.
// 3- Now each command would be divided into 2 halfs,
// 	which will have to do the same function over and over again until.