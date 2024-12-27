/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coderx64 <coderx64@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:54:59 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/27 08:29:19 by coderx64         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(int error)
{
	if (error == ERR_MALLOC_MINI || error == ERR_MALLOC_POSTMINI
		|| error == ERR_MALLOC_POSTLEXER)
		perror("malloc failed");
	if (error == ERR_TERM)
		perror("term fail");
}

void	print_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell 0x90: syntax error near unexpected token '",
		STDERR_FILENO);
	if (token->type == NEWLINE_TOKEN)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(token->token_word, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
