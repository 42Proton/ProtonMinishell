/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:35:16 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/05 15:12:23 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expander_add_quote_tok(t_minishell *mini, char *word,
		t_tok_expander *tok_exp)
{
	char	*new_str;
	t_split	split_se;
	t_list	*lst;

	split_se = tok_exp->split_se;
	new_str = ft_substr(word, split_se.start, 1);
	if (!new_str)
		expander_clean_exit(mini, tok_exp, 0);
	lst = ft_lstnew(new_str);
	if (!lst)
	{
		free(new_str);
		expander_clean_exit(mini, tok_exp, 0);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
}

void	expander_quotes_condition(t_minishell *mini, char *s,
		t_tok_expander *tok_exp)
{
	expander_add_tok(mini, s, tok_exp, 0);
	if (check_expander_default_mode(s[tok_exp->split_se.end], tok_exp))
		tok_exp->mode = DEFAULT_MODE;
	else if (s[tok_exp->split_se.end] == '\'' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = SINGLE_QUOTE_MODE;
	else if (s[tok_exp->split_se.end] == '"' && tok_exp->mode == DEFAULT_MODE)
		tok_exp->mode = DOUBLE_QUOTE_MODE;
	expander_add_quote_tok(mini, s, tok_exp);
	inc_split_index(&tok_exp->split_se);
}

t_operation	**operations_alloc(ssize_t sep_count)
{
	t_operation	**operations;
	ssize_t		i;

	i = 1;
	operations = ft_calloc(sizeof(void *), sep_count + 2);
	if (!operations)
		return (0);
	if (!add_operation_alloc(operations, 0))
		return (0);
	while (sep_count)
	{
		if (!add_operation_alloc(operations, i))
			return (0);
		sep_count--;
		i++;
	}
	return (operations);
}

int	prep_op_main_conditions(t_list *lst, size_t *p_count,
	t_operation **operations, size_t *i)
{
	if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
	{
		if (!*p_count)
			if (!add_subop(operations, *i, lst))
				return (0);
		(*p_count)++;
	}
	if (check_op_type(lst) && !*p_count)
	{
		(*i)++;
		operations[*i]->operation_type = check_op_type(lst);
	}
	return (1);
}
