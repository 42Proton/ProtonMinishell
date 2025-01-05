/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:37:07 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/05 15:10:38 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_SOURCE
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <features.h>
# include <libft.h>
# include <linux/limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_env
{
	char					*name;
	char					*data;
}							t_env;

typedef struct s_redirect
{
	int						type;
	char					*name;
}							t_redirect;

typedef struct s_qrd
{
	struct s_qrd	**qrd;
	t_list			*in_redirects_qr;
	t_list			*out_redirects_qr;
	t_list			*cmd_qr;
	t_list			*args_qr;
}	t_qrd;

typedef struct s_exp_execute
{
	int		lec;
	t_list	*env_lst;
	char	*s;
	t_list	*qr;
}	t_exp_execute;

typedef struct s_qr
{
	size_t	arr[2];
	int		is_sq;
}	t_qr;

typedef struct s_operation
{
	int					operation_type;
	struct s_operation	**operations;
	t_redirect			*in_redirects;
	t_redirect			*out_redirects;
	size_t				n_out;
	size_t				n_in;
	size_t				n_args;
	t_qrd				*qrd;
	int					parent_in_fd;
	int					parent_out_fd;
	int					redirect_in_fd;
	int					redirect_out_fd;
	int					*pipe_fds_in;
	int					*pipe_fds_out;
	char				*heredoc_buffer;
	char				*cmd;
	char				*cmd_path;
	char				**args;
	char				**env;
}						t_operation;

typedef struct s_minishell
{
	char					*line_read;
	t_list					*line_tokens;
	t_operation				**operations;
	char					*cwd;
	t_list					*env_lst;
	int						last_exit_code;
	size_t					curr_line;
	t_list					*quotes_range_lst;
}							t_minishell;

typedef struct s_tokens_split
{
	size_t					start;
	size_t					end;
	size_t					token_i;
}							t_tokens_split;

typedef struct s_token
{
	int						index;
	int						type;
	char					*token_word;
}							t_token;

typedef struct s_new_tok_len
{
	size_t					res;
	size_t					i;
}							t_new_tok_len;

typedef struct s_tok_expander
{
	int						mode;
	size_t					quotes_iter_count;
	t_split					split_se;
	t_list					*lst;
}							t_tok_expander;

enum						e_token_type
{
	COMMAND,
	ARGUMENT,
	AND_OPERATOR,
	OR_OPERATOR,
	PIPE,
	IN_REDIRECTION,
	OUT_REDIRECTION,
	LIMITER_REDIRECTION,
	APPEND_REDIRECTION,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	IDENTIFIER,
	NEWLINE_TOKEN
};

enum						e_uncompleted
{
	PARANTHASES,
	SINGLE_Q,
	DOUBLE_Q
};

enum						e_errors
{
	ERR_MALLOC_MINI,
	ERR_MALLOC_POSTMINI,
	ERR_TERM,
	NONE,
	ERR_MALLOC_POSTLEXER,
};

enum						e_redirect
{
	REDIRECT_INFILE,
	REDIRECT_OUTFILE,
	REDIRECT_LIMITER,
	REDIRECT_APPEND
};

enum						e_operation
{
	OPERATION_DEFAULT,
	OPERATION_AND,
	OPERATION_OR,
	OPERATION_PIPE,
};

enum						e_expander_modes
{
	DEFAULT_MODE,
	SINGLE_QUOTE_MODE,
	DOUBLE_QUOTE_MODE,
	DOUBLE_QUOTE_ENV_MODE,
	ENV_MODE
};
int	check_export_arg(char *arg);
int	prep_op_main_conditions(t_list *lst, size_t *p_count,
	t_operation **operations, size_t *i);
t_operation	**operations_alloc(ssize_t sep_count);
void	expander_quotes_condition(t_minishell *mini, char *s,
		t_tok_expander *tok_exp);
void			free_qrd(t_qrd **qrd);
int				check_if_index_sqr(size_t i, t_list *qr);
int				execute_expander(int lec,
					t_list *env_list, t_operation *operation);
t_qrd			**qrd_setup(t_list *tok, t_list *quotes_range_lst);
void			tokens_exp_clean_exit(t_minishell *mini,
					t_list *quotes_range, char *s);
void			signal_execution(void);
int				execute_expander_check(char *s);
int				check_if_dir(char *path);
void			print_heredoc_warning(t_minishell *mini,
					t_operation *operation, size_t j);
char			**env_lst_to_2d_arr(t_minishell *mini);
int				check_if_cmd_exist(char *cmd);
int				execute_process(t_minishell *mini);
int				op_prep_args(t_operation *operation, t_list *lst);
void			op_get_args(t_operation *operation, t_list *lst);
int				check_tok_prev_cmd(t_list *lst);
void			set_redirection_data(t_redirect *redirect, t_list *lst);
int				check_op_prep_condition(t_list *lst, ssize_t parenthesis_count);
int				check_out_redirection(t_list *lst);
int				check_in_redirection(t_list *lst);
int				op_type_to_redirection(t_list *lst);
int				op_data_collector(t_operation **operations,
					size_t i, t_list *lst);
int				prep_subop_main_conditions(t_list *lst, size_t *p_count,
					t_operation **operations, size_t *i);
int				prep_op_main_conditions(t_list *lst, size_t *p_count,
					t_operation **operations, size_t *i);
int				check_op_type(t_list *lst);
void			free_operations(t_operation **operations);
int				prep_ops_data(t_operation **operations, t_list *lst);
int				prep_subops_data(t_operation **operations, t_list *lst);
int				get_ops_data(t_operation **operations,
					t_list *lst, int is_subop);
int				add_subop(t_operation **operations, size_t i, t_list *lst);
int				add_operation_alloc(t_operation **operations, ssize_t i);
t_operation		**operations_alloc(ssize_t sep_count);
t_operation		**operations_prep(t_list *lst, int is_subop);
void			exp_env_condition(t_minishell *mini, char *s,
					t_tok_expander *tok_exp);
int				check_env_mode(t_tok_expander *tok_exp);
void			exp_rm_quotes_add_tok(t_minishell *mini, char *word,
					t_tok_expander *tok_exp, t_list **quotes_range);
char			*expander_add_tok_helper(char *word,
					t_tok_expander *tok_exp);
int				expander_pre_wildcards_update(t_tok_expander *tok_exp,
					int *old_mode, t_list **quotes_range);
int				check_quotes_ex_literal(char c,
					t_tok_expander *tok_exp);
int				check_if_wildcard(char c, size_t i,
					t_list *quotes_range);
char			*expander_remove_quotes(t_minishell *mini, char *s,
					t_list **quotes_range);
int				check_expander_default_mode_basic(char c, int mode);
int				check_env_end(char *s, t_tok_expander *tok_exp);
void			expander_pre_wildcards(t_minishell *mini, char *s,
					t_list **quotes_range);
void			free_tokens(void *tokens);
int				check_expander_if_split(t_tok_expander *tok_exp);
void			expand_tok_wildcards(t_minishell *mini, t_list **lst,
					t_list **main_lst, t_list *quotes_range);
void			del_non_matching_entries(t_list **lst_entries,
					char *pattern, t_list *quotes_range);
void			insert_sorted_entries(t_list *lst_entries_sorted,
					t_list **lst, t_list **main_lst);
int				check_str_wildcard(char *s, t_list *quotes_range);
void			inc_split_index(t_split *split_se);
void			expander_clean_exit(t_minishell *mini,
					t_tok_expander *tok_exp, t_list **quotes_range);
char			*get_env_safe(t_minishell *mini, char *new_str);
void			expander_add_tok(t_minishell *mini, char *word,
					t_tok_expander *tok_exp, t_list **quotes_range);
char			*expander_join_subtok(t_minishell *mini,
					t_tok_expander *tok_exp, t_list **quotes_range);
int				check_env_sep(char c);
int				check_quotes(char c);
int				check_expander_env(char c, int mode);
int				check_expander_default_mode(char c,
					t_tok_expander *tok_exp);
void			tokens_expander(t_minishell *mini);
int				check_type(char *token, t_token *previous_token,
					t_list *lst, t_list *qr_lst);
void			clear_token(void *content);
int				check_sep_operators(t_token *tok);
int				check_operator_num(int type);
void			print_syntax_error(t_token *token);
int				check_redirect_num(int type);
t_token			*get_token_num(t_list *tokens, size_t index);
int				validate_tokens(t_minishell *mini);
void			print_tokens(t_minishell *mini);
int				check_redirect(char *token);
int				get_redirection_type(char *token);
void			line_add_newline(t_minishell *mini);
void			display_header(void);
void			line_tokenizer(t_minishell *mini);
void			add_token(t_minishell *mini,
					t_tokens_split *tokens_split);
int				check_sep(char *line);
size_t			skip_spaces_tabs(char *line);
int				ft_unsetenv(t_list **env_lst, char *name);
int				ft_setenv(t_list **env_lst, char *name, char *data);
int				check_env_name(char *name);
int				parse_env_data(char *data, t_env *env);
int				export_cmd(t_minishell *minishell, char *arg2);
int				sort_env(t_minishell *minishell,
					t_list **sorted_env);
int				sort_print_env(t_minishell *minishell);
char			*ft_getenv(t_list *env_lst, char *env_name);
char			*get_exec_path(t_minishell *minishell, char *cmd);
void			prep_minishell_env(t_minishell *minishell,
					char **ev);
void			execute_inbuilt_command(t_minishell *minishell);
void			exit_handler(t_minishell *minishell, int error);
void			print_error(int error);
void			cd_cmd(t_minishell *minishell, char *arg2);
void			pwd_cmd(t_minishell *minishell);
void			echo_cmd(char **args);
void			env_cmd(t_minishell *minishell);
void			unset_cmd(t_minishell *minishell, char *name);
void			free_env(t_env *env);
void			free_lst(t_list *lst);
t_env			*alloc_env(char *name, char *data);
void			signal_handler(void);
int				terminals_config(void);
void			add_sep_tokens(t_minishell *mini,
					t_tokens_split *tokens_split, char *line);
void			add_token(t_minishell *mini,
					t_tokens_split *tokens_split);
int				lexical_analysis(t_minishell *mini);
int				execute_process(t_minishell *mini);
int				check_pairs(t_minishell *mini);
void			expander_add_quote_tok(t_minishell *mini, char *word,
					t_tok_expander *tok_exp);
#endif