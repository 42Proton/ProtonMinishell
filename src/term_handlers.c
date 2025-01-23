/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:51:55 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/24 00:48:47 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	signal_heredoc(int signum)
{
	g_signum = signum;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

static void	signal_update_signum(int signum)
{
	g_signum = signum;
}

static void	signal_newprompt(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	if (!g_signum)
		write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(int mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (mode == SIG_NEWPROMPT)
		sa.sa_handler = signal_newprompt;
	else if (mode == SIG_HEREDOC)
		sa.sa_handler = signal_heredoc;
	else if (mode == SIG_UPDATE_SIGNUM)
		sa.sa_handler = signal_update_signum;
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
