/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:51:55 by abueskander       #+#    #+#             */
/*   Updated: 2024/11/30 23:43:18 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	signal_test(int signum)
{
	if (signum == SIGQUIT)
		return ;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_test;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, signal_test);
}

int	terminals_config(void)
{
	struct termios	term;

	if (tcgetattr(STDERR_FILENO, &term) != 0)
	{
		perror("NO ATTERI");
		return (1);
	}
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
	{
		perror("COULDN'T SET");
		return (1);
	}
	return (0);
}
