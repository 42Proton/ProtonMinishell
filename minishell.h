#ifndef MINISHELL_H
# define MINISHELL_H

#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <dirent.h>
#include <linux/limits.h>

typedef struct s_minishell
{
	char	*line_read;
	char	*cwd;
}	t_minishell;

enum	e_errors
{
	ERR_MALLOC,
	ERR_MALLOC2,
	NONE
};

int		compare_cmd_name(char *arg1, char *cmd_name);
void	execute_inbuilt_command(t_minishell *minishell);
void	exit_handler(t_minishell *minishell, int error);

#endif