/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:48:08 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/10 01:18:57 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

static int	check_expander_env(char c, int mode)
{
	if (c == '$' && mode != SINGLE_QUOTE_MODE)
		return (1);
	return (0);
}

static void	inc_split_index(t_split *split_se)
{
	split_se->start += 1;
	split_se->end += 1;
}

static void	expander_clean_exit(t_minishell *mini, t_tok_expander *tok_exp)
{
	ft_lstclear(&tok_exp->lst, free);
	free(tok_exp);
	exit_handler(mini, ERR_MALLOC2);
}

static char	*get_env_safe(t_minishell *mini, char *new_str)
{
	char *res;

	if (!*new_str)
	{
		free(new_str);
		res = ft_strdup("$");
		return (res);
	}
	res = ft_getenv(mini, new_str);
	free(new_str);
	if (!res)
		res = ft_strdup("");
	return (res);	
}

static void	expander_add_tok(t_minishell *mini, char *word, t_tok_expander *tok_exp)
{
	char	*new_str;
	t_split	split_se;
	t_list	*lst;

	if (tok_exp->split_se.start == tok_exp->split_se.end && tok_exp->mode != ENV_MODE)
		return ;
	split_se = tok_exp->split_se;
	new_str = ft_substr(word, split_se.start,
		split_se.end - split_se.start);
	if (!new_str)
		expander_clean_exit(mini, tok_exp);
	if (tok_exp->mode == ENV_MODE)
	{
		new_str = get_env_safe(mini, new_str);
		if (!new_str)
			expander_clean_exit(mini, tok_exp);
	}
	lst = ft_lstnew(new_str);
	if (!lst)
	{
		free(new_str);
		expander_clean_exit(mini, tok_exp);
	}
	ft_lstadd_back(&tok_exp->lst, lst);
	tok_exp->split_se.start = tok_exp->split_se.end;
}

static char	*expander_join_tokens(t_minishell *mini, t_tok_expander *tok_exp)
{
	char	*res;
	t_list	*lst;

	res = ft_strdup("");
	if (!res)
		exit_handler(mini, ERR_MALLOC2);
	lst = tok_exp->lst;
	while (lst)
	{
		res = ft_strjoin(res, (char *)lst->content);
		lst = lst->next;
	}
	return (res);
}

static char	*expand_tok(t_minishell *mini, char *s)
{
	t_tok_expander	*tok_exp;

	tok_exp = ft_calloc(1, sizeof(t_tok_expander));
	if (!tok_exp)
		exit_handler(mini, ERR_MALLOC2);
	while (s[tok_exp->split_se.end])
	{
		if (check_quotes(s[tok_exp->split_se.end]))
		{
			expander_add_tok(mini, s, tok_exp);
			if ((tok_exp->mode == SINGLE_QUOTE_MODE && s[tok_exp->split_se.end] == '\'') || tok_exp->mode == ENV_MODE)
				tok_exp->mode = DEFAULT_MODE;
			if (s[tok_exp->split_se.end] == '\'')
				tok_exp->mode = SINGLE_QUOTE_MODE;
			inc_split_index(&tok_exp->split_se);
		}
		else if (check_expander_env(s[tok_exp->split_se.end], tok_exp->mode))
		{
			expander_add_tok(mini, s, tok_exp);
			tok_exp->mode = ENV_MODE;
			inc_split_index(&tok_exp->split_se);
		}
		else if (s[tok_exp->split_se.end] == ' ' && tok_exp->mode == ENV_MODE)
		{
			expander_add_tok(mini, s, tok_exp);
			tok_exp->mode = DEFAULT_MODE;
		}
		else
			tok_exp->split_se.end++;
	}
	expander_add_tok(mini, s, tok_exp);
	return (expander_join_tokens(mini, tok_exp));
}

void	tokens_expander(t_minishell *mini)
{
	t_list	*tokens;

	tokens = mini->line_tokens;
	while (tokens)
	{
		printf("%s\n", expand_tok(mini, ((t_token *)tokens->content)->token_word));
		tokens = tokens->next;
	}
}
