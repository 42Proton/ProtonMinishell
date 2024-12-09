/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:37:07 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/10 00:26:09 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_SOURCE
# include <signal.h>
# include <features.h>
# include <libft.h>
# include <stdio.h>
# include <errno.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <linux/limits.h>
# include <termios.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>

typedef struct s_minishell
{
	char	*line_read;
	t_list	*line_tokens;
	t_list  *tokens;
	char	*cwd;
	t_list	*env_lst;
	int		last_exit_code;
}	t_minishell;

typedef struct s_env
{
	char	*name;
	char	*data;
}	t_env;

typedef struct s_redirect
{
	int		redirect_type;
	char	*redirect_name;
}	t_redirect;

typedef struct s_operation	t_operation;

struct s_operation
{
	int			operation_type;
	t_operation	**operations;
	t_redirect	*in_redirects;
	t_redirect	out_redirect;
	t_redirect	*truncate_out_redirects;
	char		*cmd;
	char		**args;
};

typedef struct s_tokens_split
{
	size_t	start;
	size_t	end;
	size_t	token_i;
}	t_tokens_split;

typedef struct s_token
{
	int		index;
	int		type;
	char	*token_word;
}	t_token;

typedef struct s_new_tok_len
{
	size_t	res;
	size_t	i;
}	t_new_tok_len;

typedef struct s_tok_expander
{
	int		mode;
	t_split	split_se;
	t_list	*lst;
}	t_tok_expander;

enum	e_token_type
{
	COMMAND,
	ARGUMENT,
	AND_OPERATOR,
	OR_OPERATOR,
	PIPE,
	IN_REDIRECTION,
	OUT_REDIRECTION,
	INOUT_REDIRECTION,
	LIMITER_REDIRECTION,
	APPEND_REDIRECTION,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	IDENTIFIER,
	NEWLINE_TOKEN
};

enum	e_errors
{
	ERR_MALLOC,
	ERR_MALLOC2,
	ERR_TERM,
	NONE
};

enum	e_redirect
{
	REDIRECT_STDIN,
	REDIRECT_STDOUT,
	REDIRECT_INFILE,
	REDIRECT_OUTFILE,
	REDIRECT_LIMITER,
	REDIRECT_APPEND,
	REDIRECT_PIPE
};

enum	e_operation
{
	OPERATION_DEFAULT,
	OPERATION_SUBSHELL,
	OPERATION_AND,
	OPERATION_OR,
	OPERATION_PIPE 
};

enum	expander_modes
{
	DEFAULT_MODE,
	SINGLE_QUOTE_MODE,
	ENV_MODE
};

void	tokens_expander(t_minishell *mini);
int		check_type(char *token, t_token *previous_token);
void	clear_token(void *content);
int		check_sep_operators_nl(char *line);
int		check_operator_num(int type);
void	print_syntax_error(t_token *token);
int		check_redirect_num(int type);
t_token	*get_token_num(t_list *tokens, size_t index);
int		validate_tokens(t_minishell *mini);
void	print_tokens(t_minishell *mini);
int		check_redirect(char *token);
int		get_redirection_type(char *token);
void	line_add_newline(t_minishell *mini);
void	display_header(void);
void	line_tokenizer(t_minishell *mini);
void	add_token(t_minishell *mini, t_tokens_split *tokens_split);
void	add_sep_tokens(t_minishell *mini,
			t_tokens_split *tokens_split, char *line);
int		check_sep(char *line);
size_t	skip_spaces(char *line);
int		ft_unsetenv(t_minishell *minishell, char *name);
int		ft_setenv(t_minishell *minishell, char *name, char *data);
int		check_env_name(char *name);
int		parse_env_data(char *data, t_env *env);
int		export_cmd(t_minishell *minishell, char *arg2);
int		sort_env(t_minishell *minishell, t_list **sorted_env);
int		sort_print_env(t_minishell *minishell);
char	*ft_getenv(t_minishell *minishell, char *env_name);
char	*get_exec_path(t_minishell *minishell, char *cmd);
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
void	signal_handler(void);
int		terminals_config(void);
void	add_sep_tokens(t_minishell *mini,
			t_tokens_split *tokens_split, char *line);
void	add_token(t_minishell *mini, t_tokens_split *tokens_split);
int		lexical_analysis(t_minishell *mini);

#endif
