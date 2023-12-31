/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:52:29 by maburnet          #+#    #+#             */
/*   Updated: 2023/12/30 20:00:50 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <stddef.h>
# include <limits.h>
# include <errno.h>

# include "../libft/libft.h"

# define NFOUND "command not found"
# define NOFILE	"No such file or directory"
# define ISDIR	"Is a directory"
# define PERM	"Permission denied"
# define AMBIGUOUS "ambiguous redirect"
# define DOLQUESTION "Minishell: unset: `0': not a valid identifier\n"

typedef enum e_label
{
	EMPTY = 0,
	WORD = 1,
	CMD = 2,
	ARG = 3,
	SQUOTE = 4,
	DQUOTE = 5,
	I_RDR = 6,
	O_RDR = 7,
	HEREDOC = 8,
	OAPPEND = 9,
	PIPE = 10,
	IO_FILE = 11,
	LIMITER = 12,
	SYNTAX = 13,
	NL = 14
}	t_label;

typedef struct s_token_list
{
	char					*value;
	t_label					label;
	int						index;
	struct s_token_list		*next;
	struct s_token_list		*prev;
}	t_token;

typedef struct s_command
{
	char	**cmd_arg;
	char	**files;
	int		*is_ambiguous;
	int		*redir;
	int		nb_io;
	int		nb_arg;
}	t_command;

typedef struct s_envp
{
	char			**content;
	struct s_envp	*next;
}	t_envp;

typedef struct s_exp
{
	char			*s;
	struct s_exp	*next;
}	t_exp;

typedef struct s_clean
{
	char		*line;
	t_token		*token_list;
}	t_clean;

typedef struct s_data
{
	t_command	*commands;
	t_envp		*env;
	char		*line;
	int			nb_cmd;
	int			pipefd[2];
	int			infile;
	int			outfile;
	int			stdin;
	int			stdout;
	int			pid;
	int			status;
}	t_data;

/* 00_MAIN */

char	*ft_get_line(t_data *data, char *line);

int		minishell(t_data *data);

/* 01 LEXER */

int		ft_get_token(char *value);

int		ft_tokenize(t_token **token_list);

int		expand_line(char **line, t_envp *ep);

int		ft_lexer(t_token **token_list, char **line, t_data *data);

/* 02 TOKEN */

int		ft_count_words(char *line);

int		ft_stacked_word(char *line, int *i);

int		ft_next_word_len(char *line, int *i);

char	*ft_get_next_word(char *line, int *i);

int		ft_get_token_list(t_token **tl, char *l);

/* 03 TOKEN LIST */

t_token	*ft_lstnew(void *value);

t_token	*ft_lstlast(t_token *lst);

void	ft_lstadd_back(t_token **lst, t_token *new);

void	ft_lstclear(t_token **lst);

size_t	ft_lstsize(t_envp **lst);

/* 04 SYNTAX */

void	quote_error_loop(char *s, int *dq, int *sq, int *i);

int		quote_error(char *s);

int		check_syntax_error(t_token **tl, t_token *cur);

int		syntax_error(t_token **tl);

/* 05 PARSING */

int		ft_nb_of_cmd(t_token **token_list);

void	ft_go_to_next_cmd(t_token **next_cmd);

int		ft_fill_cmd_table(t_token **token_list, t_data *data);

void	ft_check_tokens(t_token *cur, int *cmd);

int		ft_parsing(t_token **token_list, t_data *data);

/* 06 PARSING UTILS */

int		ft_get_cmd_info(t_token **next_cmd, int *nb_arg, int *nb_io);

int		ft_get_args2(t_command *command, t_token *current, int a);

int		ft_get_args(t_command *command, t_token **token_list);

int		ft_get_redir2(t_command *command, t_token *current, int a);

int		ft_get_redir(t_command *command, t_token **next_cmd);

/* 07 EXEC */

int		ft_exec(char **command, t_envp **envp);

int		ft_do_child(t_data *data, t_envp **envp, int i);

int		ft_do_parent(t_data *data, int i, pid_t pid);

int		ft_do_cmd(t_data *data, t_envp **envp, int i);

/* 08 EXEC 2 */

int		ft_is_directory(char *cmd);

int		ft_execve_error(char *cmd);

int		ft_get_return_value(t_data *data);

int		ft_exec_cmd(t_data *data, t_envp **envp, int i);

int		ft_execute(t_data *data, t_envp **envp);

/* 09 EXEC UTILS */

void	ft_close_std(t_data *data);

void	error_msg(char *file, char *msg, int ret);

char	**ft_removepathprefix(char **paths);

char	**ft_getpaths(char **envp);

char	*ft_findcmdpath(char *cmd, char **envp, char *tmp, char *cmd_path);

/* 10 BUILTINS */

int		ft_do_builtin(t_data *data, t_envp **envp, int i, int is_pipe);

int		ft_is_builtin(t_data *data, int i);

int		ft_builtin_child(t_data *data, t_envp **envp, int i);

int		ft_exec_builtin_pipe(t_data *data, t_envp **envp, int i);

int		ft_exec_builtin(t_data *data, t_envp **envp, int i);

/* 11 HERE DOC */

int		ft_unlink_here_doc(t_data *data, int i);

int		ft_here_doc2(char *limiter, int fd);

int		ft_here_doc(char *limiter, int i);

int		ft_is_here_doc(t_data *data, int i, int *nb_doc);

int		ft_check_here_doc(t_data *data, int i);

/* 12 REDIRECTION */

int		ft_closepipe(int *pipefd);

int		ft_open_here_doc(t_data *data, int i);

int		ft_open_here_doc(t_data *data, int i);

int		ft_open_file(t_data *data, char *file, int mode, int i);

int		ft_io_file(t_data *data, t_envp **envp, int i, int is_pipe);

/* 13 SIGNAL */

void	ft_child_signal(int signum);

void	ft_here_doc_signal(int signum);

void	ft_signal(int signum);

/* 14  TOKENIZATION */

int		ft_quote_word_len(char *line, int *i, char *quote, int *in_quotes);

int		ft_get_amb(t_command *command);

/* 15 PARSING UTILS */

int		is_sep(char c);

int		is_meta(char c);

int		is_quote(char c);

/* 16 ERROR */

void	ft_exit(t_data *data, char *line, int nb);

void	ft_error(char *s, char *err);

void	ft_fail_alloc(void);

/* 17 FREE */

void	ft_free(void *to_free);

void	ft_freetab(char **tab);

void	ft_freemalloc(char **strs, int a);

void	ft_freecmdtable(t_data *data);

/* 18 UNSET */

void	ft_free_ep(t_envp *ep);

int		do_unsets(t_command *cmd, t_envp **ep);

int		ft_do_unset(char *arg, t_envp *t, t_envp *t2);

int		do_unset(char *arg, t_envp **ep);

/* 19 CD */

char	*get_ab_path(char *path);

int		ft_get_path(char *path, char **t, t_envp *ep);

int		ft_open_dir(char *path, char *t);

int		do_cd(char *path, t_envp **ep);

int		exec_cd(t_command *cmd, t_envp **ep);

int		ft_do_chdir(char *t, t_envp **ep);
/* 20 PWD */

int		do_pwd(t_envp *ep);

/* 21 ENV */

int		print_envp(t_envp *envp);

void	free_content(char **content);

char	**split_env(char *s);

int		add_new_envp(t_envp **ep, char **content);

void	clear_ep(t_envp **ep);

/* 22 SET ENV */

int		ft_get_shell_level(t_envp **ep);

int		set_empty_env(t_envp **ep);

int		set_env(t_envp **ep, char **envp);

/* 23 EXPORT */

int		do_exports(t_command *cmd, t_envp **ep, int i);

int		do_export(char *name, char *value, t_envp **ep, char *cmd);

int		export_error(char *name, char *value, char *cmd);

int		build_new_envp(char *name, char *value, t_envp **ep);

char	**add_content(char *name, char *value);

/* 24 EXPORT UTILS */

t_envp	*ft_lstlast_ev(t_envp *lst);

void	ft_lstadd_back_ev(t_envp **lst, t_envp *new);

char	*ft_getenv(char *env_name, t_envp *ep);

void	print_export(t_envp *ep);

/* 25 EXIT */

int		ft_str_is_num(char *s);

int		ft_do_exit(t_data *data, int i, long *res, int too_big);

int		do_exit(t_data *data, t_envp **ep, int i, int is_pipe);

/* 26 EXPAND_CMD */

int		ft_expand_cmd(t_data *data, t_envp **env, int i);

int		is_amb_cmd(char *t, t_envp *ep);

int		ft_not_amb(t_command *cmd, t_envp **env, int a, t_exp *exp);

int		ft_expand_files(t_data *data, t_envp **env, int i);

/* 27 EXPAND */

int		do_dollar(t_exp **exp, char *s, int i, t_envp *ep);

int		do_sq(t_exp **exp, char *s, int i);

int		do_not_exp(t_exp **exp, char *s, int i);

int		do_tilde(t_exp **exp, char *s, t_envp *ep);

int		do_quote_exp(t_exp **exp, char *s, t_envp *ep, int mode);

/* 28 EXPAND UTILS */

int		do_not_exp_dq(t_exp **exp, char *s, int i);

int		do_dq(t_exp **exp, char *s, int i, t_envp *ep);

char	*exp_to_str(t_exp *exp);

/* 29 EXP UTILS */

t_exp	*ft_lstlast_exp(t_exp *lst);

void	ft_lstadd_back_exp(t_exp **lst, t_exp *new);

void	clear_exp(t_exp **exp);

int		add_new_exp(t_exp **exp, char *str);

void	print_exp(t_exp *exp);

/* 30 EXPAND LINE */

char	*get_env_value(char *s, int dollar, t_envp *ep);

int		is_ambiguous(char *s, int dl, t_envp *ep);

int		add_dollar_str(char **line, int i, t_envp *ep);

int		do_dollar_line(char **line, int i, t_envp *ep);

/* 31 EXPAND LINE UTILS */

int		isset(char const *set, char c);

int		is_printable(char c);

int		is_redir(char *s, int i);

int		further_check_amb_str(char *s, int i);

int		check_amb_str(char *s);

/* 32 ECHO */

int		is_option_n(char *s);

int		do_echo(t_command *cmd);

int		add_exp_value(t_exp **exp, char *env_name, t_envp *ep);

/* 34 UTILS */

char	**ft_lst_to_tab(t_envp **lst);

char	*ft_strjoinf(char *s1, char *s2);

int		is_env(int c);

int		inv_env_name(char *s);

#endif
