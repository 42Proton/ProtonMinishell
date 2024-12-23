/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:37:07 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/23 18:16:50 by amsaleh          ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <termcap.h>
# include <termios.h>

typedef struct s_minishell
{
	char					*line_read;
	t_list					*line_tokens;
	t_list					*tokens;
	char					*cwd;
	t_list					*env_lst;
	int						last_exit_code;
}							t_minishell;

typedef struct s_env
{
	char					*name;
	char					*data;
}							t_env;

typedef struct s_redirect
{
	int						redirect_type;
	char					*redirect_name;
}							t_redirect;

typedef struct s_operation	t_operation;

struct						s_operation
{
	int						operation_type;
	t_operation				**operations;
	t_redirect				*in_redirects;
	t_redirect				out_redirect;
	t_redirect				*truncate_out_redirects;
	char					*cmd;
	char					**args;
};

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
	INOUT_REDIRECTION,
	LIMITER_REDIRECTION,
	APPEND_REDIRECTION,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	IDENTIFIER,
	NEWLINE_TOKEN
};

enum						e_errors
{
	ERR_MALLOC,
	ERR_MALLOC2,
	ERR_TERM,
	NONE
};

enum						e_redirect
{
	REDIRECT_STDIN,
	REDIRECT_STDOUT,
	REDIRECT_INFILE,
	REDIRECT_OUTFILE,
	REDIRECT_LIMITER,
	REDIRECT_APPEND,
	REDIRECT_PIPE
};

enum						e_operation
{
	OPERATION_DEFAULT,
	OPERATION_AND,
	OPERATION_OR,
	OPERATION_PIPE
};

enum						e_expander_modes
{
	DEFAULT_MODE,
	SINGLE_QUOTE_MODE,
	DOUBLE_QUOTE_MODE,
	ENV_MODE
};

void						exp_rm_quotes_add_tok(t_minishell *mini, char *word,
								t_tok_expander *tok_exp, t_list **quotes_range);
char						*expander_add_tok_helper(char *word, t_tok_expander *tok_exp);
int							expander_pre_wildcards_update(t_tok_expander *tok_exp,
								int *old_mode, t_list **quotes_range);
int							check_quotes_ex_literal(char c,
								t_tok_expander *tok_exp);
int							check_if_wildcard(char c, size_t i,
								t_list *quotes_range);
char						*expander_remove_quotes(t_minishell *mini, char *s,
								t_list **quotes_range);
int							check_expander_default_mode_basic(char c, int mode);
int							check_env_end(char *s, t_tok_expander *tok_exp);
void						expander_pre_wildcards(t_minishell *mini, char *s,
								t_list **quotes_range);
void						free_tokens(void *tokens);
int							check_expander_if_split(t_tok_expander *tok_exp);
void						expand_tok_wildcards(t_minishell *mini,
								t_list **lst, t_list **main_lst,
								t_list *quotes_range);
void						del_non_matching_entries(t_list **lst_entries,
								char *pattern, t_list *quotes_range);
void						insert_sorted_entries(t_list *lst_entries_sorted,
								t_list **lst, t_list **main_lst);
int							check_str_wildcard(char *s);
void						inc_split_index(t_split *split_se);
void						expander_clean_exit(t_minishell *mini,
								t_tok_expander *tok_exp, t_list **quotes_range);
char						*get_env_safe(t_minishell *mini, char *new_str);
void						expander_add_tok(t_minishell *mini, char *word,
								t_tok_expander *tok_exp, t_list **quotes_range);
char						*expander_join_subtok(t_minishell *mini,
								t_tok_expander *tok_exp, t_list **quotes_range);
int							check_env_sep(char c);
int							check_quotes(char c);
int							check_expander_env(char c, int mode);
int							check_expander_default_mode(char c,
								t_tok_expander *tok_exp);
void						tokens_expander(t_minishell *mini);
int							check_type(char *token, t_token *previous_token);
void						clear_token(void *content);
int							check_sep_operators_nl(char *line);
int							check_operator_num(int type);
void						print_syntax_error(t_token *token);
int							check_redirect_num(int type);
t_token						*get_token_num(t_list *tokens, size_t index);
int							validate_tokens(t_minishell *mini);
void						print_tokens(t_minishell *mini);
int							check_redirect(char *token);
int							get_redirection_type(char *token);
void						line_add_newline(t_minishell *mini);
void						display_header(void);
void						line_tokenizer(t_minishell *mini);
void						add_token(t_minishell *mini,
								t_tokens_split *tokens_split);
void						add_sep_tokens(t_minishell *mini,
								t_tokens_split *tokens_split, char *line);
int							check_sep(char *line);
size_t						skip_spaces(char *line);
int							ft_unsetenv(t_minishell *minishell, char *name);
int							ft_setenv(t_minishell *minishell, char *name,
								char *data);
int							check_env_name(char *name);
int							parse_env_data(char *data, t_env *env);
int							export_cmd(t_minishell *minishell, char *arg2);
int							sort_env(t_minishell *minishell,
								t_list **sorted_env);
int							sort_print_env(t_minishell *minishell);
char						*ft_getenv(t_minishell *minishell, char *env_name);
char						*get_exec_path(t_minishell *minishell, char *cmd);
void						prep_minishell_env(t_minishell *minishell,
								char **ev);
void						execute_inbuilt_command(t_minishell *minishell);
void						exit_handler(t_minishell *minishell, int error);
void						print_error(int error);
void						cd_cmd(t_minishell *minishell, char *arg2);
void						pwd_cmd(t_minishell *minishell);
void						echo_cmd(char **args);
void						env_cmd(t_minishell *minishell);
void						unset_cmd(t_minishell *minishell, char *name);
void						free_env(t_env *env);
void						free_lst(t_list *lst);
t_env						*alloc_env(char *name, char *data);
void						signal_handler(void);
int							terminals_config(void);
void						add_sep_tokens(t_minishell *mini,
								t_tokens_split *tokens_split, char *line);
void						add_token(t_minishell *mini,
								t_tokens_split *tokens_split);
int							lexical_analysis(t_minishell *mini);
int							execute_process(t_minishell *mini);

#endif
