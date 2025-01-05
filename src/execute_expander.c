/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:57:19 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/05 09:59:23 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_expander_process_c1(t_tok_expander *tok_exp, int lec)
{
	char	*temp;
	t_list	*lst;

	temp = ft_itoa(lec);
	if (!temp)
		return (0);
	lst = ft_lstnew(temp);
	if (!lst)
	{
		free(temp);
		return (0);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	return (1);
}

int	execute_expander_process_c2(t_tok_expander *tok_exp, t_list *env_list)
{
	char	*temp;
	t_list	*lst;

	temp = ft_strdup(ft_getenv(env_list, "_"));
	if (!temp)
		return (0);
	lst = ft_lstnew(temp);
	if (!lst)
	{
		free(temp);
		return (0);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	return (1);
}

int	execute_expander_process_helper2(t_exp_execute *exp_execute, t_tok_expander *tok_exp)
{
	t_split	split_se;
	t_list	*lst;
	char	*temp;

	split_se = tok_exp->split_se;
	if (check_if_index_sqr(split_se.end, exp_execute->qr))
	{
		temp = ft_substr(exp_execute->s, split_se.end, 2);
		if (!temp)
			return (0);
		lst = ft_lstnew(temp);
		if (!lst)
		{
			free(temp);
			return (0);
		}
		ft_lstadd_back(&tok_exp->lst, lst);
		return (1);
	}
	if (!ft_strncmp(exp_execute->s + split_se.end, "$?", 2))
		if (!execute_expander_process_c1(tok_exp, exp_execute->lec))
			return (0);
	if (!ft_strncmp(exp_execute->s + split_se.end, "$_", 2))
		if (!execute_expander_process_c2(tok_exp, exp_execute->env_lst))
			return (0);
	return (1);
}

void	inc_split_index2(t_split *split_se, size_t i)
{
	split_se->start += i;
	split_se->end += i;
}

void	free_execute_expander(t_tok_expander *tok_exp)
{
	ft_lstclear(&tok_exp->lst, free);
	free(tok_exp);
}

static char	*execute_expander_subtok_join(t_tok_expander *tok_exp)
{
	t_list	*lst;
	char	*res;
	char	*temp;

	lst = tok_exp->lst;
	res = ft_strdup("");
	while (lst)
	{
		temp = ft_strjoin(res, (char *)lst->content);
		free(res);
		if (!temp)
		{
			free_execute_expander(tok_exp);
			return (0);
		}
		res = temp;
		lst = lst->next;
	}
	free_execute_expander(tok_exp);
	return (res);
}

static int	execute_expander_process_helper(t_exp_execute *exp_execute, t_tok_expander *tok_exp)
{
	char	*temp;
	t_split	split_se;
	t_list	*lst;
	
	split_se = tok_exp->split_se;
	if (split_se.start != split_se.end)
	{
		temp = ft_substr(exp_execute->s, split_se.start, split_se.end - split_se.start);
		if (!temp)
			return (0);
		lst = ft_lstnew(temp);
		if (!lst)
			free(temp);
		if (!lst)
			return (0);
		ft_lstadd_back(&tok_exp->lst, lst);
		tok_exp->split_se.start = tok_exp->split_se.end;
	}
	if (execute_expander_check(exp_execute->s + tok_exp->split_se.end))
	{
		if (!execute_expander_process_helper2(exp_execute, tok_exp))
			return (0);
		inc_split_index2(&tok_exp->split_se, 2);
	}
	return (1);
}

static char	*execute_expander_process(t_exp_execute *exp_execute)
{
	t_tok_expander	*tok_exp;
	char			*res;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	if (!tok_exp)
		return (0);
	while (exp_execute->s[tok_exp->split_se.end])
	{
		if (execute_expander_check(exp_execute->s + tok_exp->split_se.end))
		{
			if (!execute_expander_process_helper(exp_execute, tok_exp))
			{
				free_execute_expander(tok_exp);
				return (0);
			}
		}
		else
			tok_exp->split_se.end++;
	}
	execute_expander_process_helper(exp_execute, tok_exp);
	res = execute_expander_subtok_join(tok_exp);
	return (res);
}

int	execute_expander_cmd(t_exp_execute *exp_execute, t_operation *operation)
{
	char	*temp;

	if (operation->cmd)
	{
		exp_execute->qr = operation->qrd->cmd_qr;
		exp_execute->s = operation->cmd;
		temp = execute_expander_process(exp_execute);
		if (!temp)
		{
			free(exp_execute);
			return (0);
		}
		operation->cmd = temp;
	}
	return (1);
}

int	execute_expander_args(t_exp_execute *exp_execute, t_operation *operation)
{
	char	**args;
	char	*temp;
	t_list	*args_qr;
	size_t	i;

	args = operation->args;
	args_qr = operation->qrd->args_qr;
	i = 0;
	while (args[i])
	{
		exp_execute->qr = args_qr;
		exp_execute->s = args[i];
		temp = execute_expander_process(exp_execute);
		if (!temp)
		{
			free(exp_execute);
			return (0);
		}
		operation->args[i] = temp;
		i++;
		if (args_qr)
			args_qr = args_qr->next;
	}
	return (1);
}

int	execute_expander(int lec, t_list *env_lst, t_operation *operation)
{
	t_exp_execute	*exp_execute;

	exp_execute = malloc(sizeof(t_exp_execute));
	if (!exp_execute)
		return (0);
	exp_execute->lec = lec;
	exp_execute->env_lst = env_lst;
	if (!execute_expander_cmd(exp_execute, operation))
	{
		free(exp_execute);
		return (0);
	}
	if (!execute_expander_args(exp_execute, operation))
	{
		free(exp_execute);
		return (0);
	}
	free(exp_execute);
	return (1);
}
