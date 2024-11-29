/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:37:07 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/30 02:24:53 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <linux/limits.h>

typedef struct s_minishell
{
	char	*line_read;
	char	*cwd;
	t_list	*env_lst;
	int		last_exit_code;
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

int		ft_unsetenv(t_minishell *minishell, char *name);
int		ft_setenv(t_minishell *minishell, char *name, char *data);
int		check_env_name(char *name);
int		parse_env_data(char *data, t_env *env);
int		export_cmd(t_minishell *minishell, char *arg2);
int		sort_env(t_minishell *minishell, t_list **sorted_env);
int		sort_print_env(t_minishell *minishell);
char	*ft_getenv(t_minishell *minishell, char *env_name);
void	prep_minishell_env(t_minishell *minishell, char **ev);
void	execute_inbuilt_command(t_minishell *minishell);
void	exit_handler(t_minishell *minishell, int error);
void	print_error(int error);
void	cd_cmd(t_minishell *minishell, char *arg2);
void	pwd_cmd(t_minishell *minishell);
void	echo_cmd(char **args);
void	env_cmd(t_minishell *minishell);
void	unset_cmd(t_minishell *minishell, char *name);
void	free_env(t_env *env);
void	free_lst(t_list	*lst);
t_env	*alloc_env(char *name, char *data);

#endif