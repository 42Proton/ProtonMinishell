/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:51:55 by abueskander       #+#    #+#             */
/*   Updated: 2025/01/31 10:42:02 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	signal_newprompt(int signum)
{
	if (!g_signum)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
	}
	g_signum = signum;
	close(STDIN_FILENO);
}

static void	signal_update_signum(int signum)
{
	g_signum = signum;
}

void	signal_handler(int mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (mode == SIG_NEWPROMPT)
		sa.sa_handler = signal_newprompt;
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

int	set_term_attr_vquit(struct termios *term, int allow)
{
	char	og_quit;

	if (allow)
	{
		if (tcsetattr(STDERR_FILENO, TCSANOW, term) != 0)
			return (1);
	}
	else
	{
		og_quit = term->c_cc[VQUIT];
		term->c_cc[VQUIT] = _POSIX_VDISABLE;
		if (tcsetattr(STDERR_FILENO, TCSANOW, term) != 0)
		{
			term->c_cc[VQUIT] = og_quit;
			return (1);
		}
		term->c_cc[VQUIT] = og_quit;
	}
	return (0);
}

int	terminals_config(t_minishell *mini)
{
	char	og_quit;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)
		|| !isatty(STDERR_FILENO))
		return (1);
	if (tcgetattr(STDERR_FILENO, &mini->term) != 0)
		return (1);
	og_quit = mini->term.c_cc[VQUIT];
	mini->term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDERR_FILENO, TCSANOW, &mini->term) != 0)
		return (1);
	mini->term.c_cc[VQUIT] = og_quit;
	return (0);
}
