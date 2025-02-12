/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:54:59 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/28 15:17:22 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(int error)
{
	if (error == ERR_MINI || error == ERR_POSTMINI
		|| error == ERR_POSTLEXER)
		perror("An error occurred");
	if (error == ERR_TERM)
		perror("term fail");
	if (error == NONE)
		write(STDOUT_FILENO, "exit\n\e[0m", 9);
}

void	print_syntax_error(t_token *token)
{
	if (token)
		ft_dprintf(STDERR_FILENO, "Proton: syntax error \
near unexpected token '%s'\n", token->token_word);
	else
		ft_dprintf(STDERR_FILENO, "Proton: syntax error \
near unexpected token 'newline'\n");
}

void	print_heredoc_warning(t_op_ref *op_ref,
	t_operation *operation, size_t j)
{
	ft_dprintf(STDERR_FILENO, "Proton: warning: here-document \
at line %u delimited by end-of-file (wanted `%s')\n", *op_ref->curr_line,
		operation->in_redirects[j].name);
}
