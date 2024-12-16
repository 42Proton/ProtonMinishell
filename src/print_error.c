/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:54:59 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/07 01:02:15 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(int error)
{
	if (error == ERR_MALLOC || error == ERR_MALLOC2)
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
