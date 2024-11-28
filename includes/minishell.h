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
	t_list	*env_lst;
}	t_minishell;

typedef struct s_env
{
	char	*name;
	char	*data;
}	t_env;

enum	e_errors
{
	ERR_MALLOC,
	ERR_MALLOC2,
	NONE
};

void	prep_minishell_env(t_minishell *minishell, char **ev);
char	*ft_getenv(t_minishell *minishell, char *env_name);
int		compare_cmd_name(char *arg1, char *cmd_name);
void	execute_inbuilt_command(t_minishell *minishell);
void	exit_handler(t_minishell *minishell, int error);
void	print_error(int error);
void	cd_cmd(t_minishell *minishell, char *arg2);
void	pwd_cmd(t_minishell *minishell);
void	echo_cmd(char **args);
void	env_cmd(t_minishell *minishell);

#endif