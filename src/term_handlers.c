/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:51:55 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/22 00:10:14 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int rl_dummy_event(void)
{ 
	return (0);
}

static void	signal_heredoc(int signum)
{
	g_signum = signum;
	rl_done = 1;
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
}

static void	signal_newprompt(int signum)
{
	g_signum = signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	signal_handler(int mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (mode == 1)
		sa.sa_handler = signal_newprompt;
	else if (mode == 2)
		sa.sa_handler = signal_heredoc;
	else
		sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

int	terminals_config(void)
{
	struct termios	term;

	if (!isatty(STDIN_FILENO))
		return (1);
	if (tcgetattr(STDERR_FILENO, &term) != 0)
		return (1);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		return (1);
	return (0);
}
