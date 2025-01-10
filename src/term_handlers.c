/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:51:55 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/10 19:13:48 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	signal_newprompt(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_printf("\n");
	rl_redisplay();
}

void	signal_exec(int signum)
{
	(void)signum;
}

void	signal_handler(int newprompt, int ign_sigint)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (newprompt)
		sa.sa_handler = signal_newprompt;
	else if (!ign_sigint)
		sa.sa_handler = signal_exec;
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
