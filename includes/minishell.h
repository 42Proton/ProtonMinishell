/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:37:07 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/29 11:31:28 by amsaleh          ###   ########.fr       */
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

extern int	g_signum;

typedef struct s_env
{
	char					*name;
	char					*data;
	int						mode;
}							t_env;

typedef struct s_redirect
{
	int						type;
	char					*name;
}							t_redirect;

typedef struct s_qr
{
	size_t	arr[2];
	int		is_sq;
	int		is_empty;
}	t_qr;

typedef struct s_split_toks
{
	t_list	*quotes_ranges;
	char	*str;
}	t_split_toks;

typedef struct s_op_ref
{
	int			*lec;
	int			*stdin_bak;
	int			wait_childs;
	int			is_exit;
	int			last_pid;
	int			circuit_trigger;
	int			signal_term;
	int			is_child;
	u_int32_t	*curr_line;
	u_int32_t	heredoc_line_inc;
	t_list		**env_lst;
	char		*shell_exec;
}	t_op_ref;

typedef struct s_pre_process
{
	size_t	parenthesis_count;
	int		mode;
}	t_pre_process;

typedef struct s_operation
{
	int					operation_type;
	struct s_operation	**operations;
	t_redirect			*in_redirects;
	t_redirect			*out_redirects;
	size_t				n_out;
	size_t				n_in;
	size_t				n_args;
	int					redirect_in_fd;
	int					redirect_out_fd;
	int					*pipe_fds_in;
	int					*pipe_fds_out;
	char				*heredoc_buffer;
	char				*cmd;
	char				*cmd_path;
	char				**args;
}						t_operation;

typedef struct s_minishell
{
	char					*line_read;
	t_list					*line_tokens;
	t_list					*env_lst;
	int						last_exit_code;
	u_int32_t				curr_line;
	int						is_empty;
	int						stdin_bak;
	int						unclean_mode;
	int						is_terminfo_caps_loaded;
	char					*shell_exec;
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
	char					*s_ref;
	int						mode;
	size_t					quotes_iter_count;
	t_split					split_se;
	t_list					*lst;
	t_list					**split_tok;
	int						lec;
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
	IDENTIFIER
};

enum						e_errors
{
	ERR_MINI,
	ERR_POSTMINI,
	ERR_TERM,
	NONE,
	CHILD_NONE,
	ERR_POSTLEXER,
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

enum						e_strjoin
{
	STRJOIN_DEF,
	STRJOIN_FS1,
	STRJOIN_FS2,
	STRJOIN_FA
};

enum						e_signal_modes
{
	SIG_IGNORE,
	SIG_NEWPROMPT,
	SIG_UPDATE_SIGNUM
};

int					exec_proc_iter(t_operation **ops,
						t_op_ref *op_ref, size_t i);
int					exec_proc_helper_util(t_operation **ops,
						size_t i, t_op_ref *op_ref);
int					exec_proc_util(t_op_ref *op_ref,
						t_operation **ops, size_t i);
int					exec_circuit_check(t_op_ref *op_ref, t_operation *op);
void				cmd_cmd_helper(char **args, size_t i, t_op_ref *op_ref);
int					check_valid_flag(char *arg);
void				echo_iteraite_flag(char ***args, int *newline);
void				execute_cmd_end(t_op_ref *op_ref,
						pid_t pid, t_operation *next_op);
void				start_execution_exits(t_minishell *mini,
						int status, int is_exit, int is_child);
int					prep_heredoc_helper(t_op_ref *op_ref,
						t_operation *operation, size_t j);
int					prep_heredoc_util(t_op_ref *op_ref,
						t_operation **ops, size_t i, size_t j);
int					prep_heredoc_helper_util(t_operation *op, char *line);
void				exec_exp_s2_helper2(t_list **tokens,
						t_operation *operation, size_t i);
size_t				get_envlst_size(t_list *env_lst);
int					sort_print_env_helper2_util(char **res, t_env *env);
int					check_if_special_exp(char *s, t_tok_expander *tok_exp);
char				*exp_limiter(char *tok);
int					quicksig_handle(t_minishell *mini);
int					out_files_check(t_operation *op, size_t i, int *flags);
int					execute_expander_stage2_helper2(t_list **tokens,
						t_operation *op, size_t i);
void				exp_s1_update_op_prep(t_operation *op, t_list **tokens,
						size_t *lst_size, size_t *arr_size);
size_t				get_lsttok_size(t_list *tok);
size_t				get_arr_len(void **arr);
void				start_shell_sighandle(t_minishell *mini);
void				cursor_line_back(t_minishell *mini);
int					builtin_cmd_process(t_operation **operations,
						size_t i, t_op_ref *op_ref);
int					builtin_cmd_child(t_operation **operations,
						size_t i, t_op_ref *op_ref);
void				recover_stdin_bak(t_minishell *mini);
int					execute_process_helper(t_operation **ops,
						size_t i, t_op_ref *op_ref);
void				wait_childs(t_op_ref *op_ref);
int					execute_process_circuit(t_operation *operation,
						t_op_ref *op_ref);
int					prep_pipeline(t_operation *operation,
						t_operation *next_op);
int					execute_cmd(t_op_ref *op_ref,
						t_operation *operation, t_operation *next_op);
int					pre_execute_external_cmd(t_op_ref *op_ref,
						t_operation *operation);
void				restore_sigint(void);
int					subshell_apply_fds(t_operation *op);
void				execute_cmd_close_fds(t_operation *operation, int is_ext);
int					execute_cmd_redirections(t_operation *operation,
						int is_ext);
int					create_trunc_out_files(t_operation *operation);
int					process_in_redirects(t_operation *operation);
int					process_in_redirects_heredoc(t_operation *operation);
int					prep_heredoc(t_op_ref *op_ref, t_operation **operations);
int					token_expander_helper2(t_list **split_toks,
						t_op_ref *op_ref, char *s);
int					token_expander_helper(t_list *split_toks, t_list *res_toks,
						t_list **tokens);
void				expander_loop_helper(t_tok_expander *tok_exp,
						size_t *env_len, size_t *i);
size_t				exp_prep_qtr_env(char *str, t_tok_expander *tok_exp,
						t_op_ref *op_ref, size_t *i);
int					insert_quotes_range(t_list **quotes_range,
						t_tok_expander *tok_exp, int old_mode);
t_op_ref			*op_ref_init(t_operation **operations, t_minishell *mini);
ssize_t				separators_counter(t_list *lst);
ssize_t				separators_counter_subop(t_list *lst);
int					tok_exp_res_split_util(char *exp_str,
						t_tok_expander *tok_exp2, size_t *temp);
int					token_exp_res_split_helper3(char *s,
						t_tok_expander *tok_exp, size_t *env_len);
int					tok_exp_res_split_push(t_tok_expander *tok_exp);
void				tok_exp_res_split_skip_env(char *s,
						t_tok_expander *tok_exp, size_t *env_len);
int					tok_exp_rep_split_helper2_util(char *s,
						t_tok_expander *tok_exp, size_t env_len);
void				token_exp_res_split_qt(char *s, t_tok_expander *tok_exp);
unsigned long long	ft_atoull(char *nptr);
long long			ft_atoll(char *nptr);
int					exp_add_tok_rm_qt(char *s, t_tok_expander *tok_exp);
char				*ft_strjoin2(char *s1, char *s2, int mode);
void				clear_split_tok(void *content);
void				clear_split_tok2(void *content);
int					exp_rm_qt(t_list *split_toks);
int					expander_qtr(char *s, t_list *split_toks,
						t_op_ref *op_ref, int env_mode);
int					expander_prep_qtr(t_list *s_split_toks,
						t_list **split_toks);
int					token_exp_res_split(char *s, char *exp_str,
						t_list **split_tok, t_op_ref *op_ref);
size_t				get_env_len(char *s, t_op_ref *op_ref, int trunc_spaces);
void				exit_cmd(t_op_ref *op_ref, char **args);
int					builtin_cmd(t_operation **operations,
						size_t i, t_op_ref *op_ref);
int					check_if_builtin(char *token);
int					pre_process_check(char *s);
int					tokens_expander_env_iter(char *s,
						t_tok_expander *tok_exp, t_op_ref *op_ref);
int					prep_op_main_conditions(t_list *lst, size_t *p_count,
						t_operation **operations, size_t *i);
t_operation			**operations_alloc(ssize_t sep_count);
int					expander_quotes_condition(char *s,
						t_tok_expander *tok_exp, t_op_ref *op_ref);
int					execute_expander(t_op_ref *op_ref, t_operation *operation);
int					check_if_dir(char *path);
void				print_heredoc_warning(t_op_ref *op_ref,
						t_operation *operation, size_t j);
char				**env_lst_to_2d_arr(t_op_ref *op_ref);
int					execute_process(t_operation **ops,
						t_op_ref *op_ref, int is_subshell);
int					op_prep_args(t_operation *operation, t_list *lst);
int					op_get_args(t_operation *operation, t_list *lst);
int					check_tok_prev_cmd(t_list *lst);
int					set_redirection_data(t_operation *operations,
						t_list *lst, size_t *i, int whom);
int					check_op_prep_condition(t_list *lst,
						ssize_t parenthesis_count);
int					check_out_redirection(t_list *lst);
int					check_in_redirection(t_list *lst);
int					op_type_to_redirection(t_list *lst);
int					op_data_collector(t_operation **operations,
						size_t i, t_list *lst);
int					prep_subop_main_conditions(t_list *lst, size_t *p_count,
						t_operation **operations, size_t *i);
int					check_op_type(t_list *lst);
void				free_operations(t_operation **operations);
int					prep_ops_data(t_operation **operations, t_list *lst);
int					prep_subops_data(t_operation **operations, t_list *lst);
int					get_ops_data(t_operation **operations,
						t_list *lst, int is_subop);
int					add_subop(t_operation **operations, size_t i, t_list *lst);
int					add_operation_alloc(t_operation **operations, ssize_t i);
t_operation			**operations_alloc(ssize_t sep_count);
t_operation			**operations_prep(t_list *lst, int is_subop);
int					exp_env_condition(char *s,
						t_tok_expander *tok_exp, t_op_ref *op_ref);
int					check_env_mode(t_tok_expander *tok_exp);
char				*expander_add_tok_helper(char *word,
						t_tok_expander *tok_exp);
int					check_quotes_ex_literal(char c,
						t_tok_expander *tok_exp);
int					check_if_wildcard(char c, size_t i,
						t_list *quotes_range);
int					check_expander_default_mode_basic(char c, int mode);
int					check_env_end(char *s, t_tok_expander *tok_exp);
void				free_tokens(void *tokens);
int					check_expander_if_split(t_tok_expander *tok_exp);
int					expand_tok_wildcards(char *pattern, t_list **main_lst,
						t_list *quotes_range);
void				del_non_matching_entries(t_list **lst_entries,
						char *pattern, t_list *quotes_range);
int					check_str_wildcard(char *s, t_list *quotes_range);
void				inc_split_index(t_split *split_se);
char				*get_env_safe(t_op_ref *op_ref,
						char *new_str, t_tok_expander *tok_exp);
int					expander_add_tok(char *word,
						t_tok_expander *tok_exp, t_op_ref *op_ref);
char				*expander_join_subtok(t_tok_expander *tok_exp);
int					check_env_sep(char c);
int					check_quotes(char c);
int					check_expander_env(char c, int mode);
int					check_expander_default_mode(char c,
						t_tok_expander *tok_exp);
int					token_expander(char *s, t_list **tokens, t_op_ref *op_ref);
int					check_type(char *token, t_token *previous_token,
						t_list *lst);
int					check_sep_operators(t_token *tok);
int					check_operator_num(int type);
void				print_syntax_error(t_token *token);
int					check_redirect_num(int type);
t_token				*get_token_num(t_list *tokens, size_t index);
int					validate_tokens(t_minishell *mini);
void				print_tokens(t_minishell *mini);
int					check_redirect(char *token);
int					get_redirection_type(char *token);
void				line_add_newline(t_minishell *mini);
void				line_tokenizer(t_minishell *mini);
int					check_sep(char *line);
int					ft_unsetenv(t_list **env_lst, char *name);
int					ft_setenv(t_list **env_lst, char *name, char *data);
int					check_env_name(char *name);
int					parse_env_data(char *data, t_env *env);
int					export_cmd(t_op_ref *op_ref, char **args);
int					sort_env(t_list *lst, t_list **sorted_env);
int					sort_print_env(t_list *lst);
char				*ft_getenv(t_list *env_lst, char *env_name);
char				*get_exec_path(t_op_ref *op_ref, char *cmd);
void				prep_minishell_env(t_minishell *mini, char **ev);
int					execute_inbuilt_command(t_op_ref *op_ref,
						char *cmd, char **args);
void				exit_handler(t_minishell *minishell, int error);
void				print_error(int error);
void				cd_cmd(t_op_ref *op_ref, char **args);
void				pwd_cmd(t_op_ref *op_ref);
int					echo_cmd(char **args);
int					env_cmd(t_op_ref *op_ref);
void				unset_cmd(t_op_ref *op_ref, char **args);
void				free_env(t_env *env);
void				free_lst(t_list *lst);
t_env				*alloc_env(char *name, char *data);
void				signal_handler(int newprompt);
int					terminals_config(void);
int					add_sep_tokens(t_minishell *mini,
						t_tokens_split *tokens_split, char *line);
int					add_token(t_minishell *mini,
						t_tokens_split *tokens_split);
int					lexical_analysis(t_minishell *mini);
int					expander_add_quote_tok(char *word, t_tok_expander *tok_exp);
#endif	