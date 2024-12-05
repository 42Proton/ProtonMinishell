/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:45:59 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/05 23:19:38 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void print_tokens(t_minishell *mini)
{
        t_list  *node;

        node = mini->line_tokens;
        while(node)
        {
                ft_printf("%s hey",node->content);
                node = node->next;
        }
}
static int     check_type(char *token, t_list *envs)
{
        int type;

        type = WORDS;
        if (check_sep(token))
                type = REDIRECTIONS;
        else if (check_if_command(token ,envs))
                type = COMMANDS;
        else if (check_if_environ(token,envs))
                type = ENV;
        return (type);
}
static void     turn_into_struct(t_list *tokens,t_list *envs)
{
        t_list *tok;
        t_token *temp;
        
    
        tok = ft_calloc(1,sizeof(t_list));
        if(!tok)
                return ;
        while(tokens)
        {
                temp = ft_calloc(1,sizeof(t_token));
                temp->type = check_type(tokens->content, envs);
                temp->token_word = ft_strdup(tokens->content);
                ft_lstadd_front(&tok,ft_lstnew((temp)));
                tokens = tokens->next;
                free(temp);
        }
}
void    validate_tokens(t_minishell *mini)
{
        turn_into_struct(mini->line_tokens, mini->env_lst);
}