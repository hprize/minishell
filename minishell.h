#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./ft_fprintf/ft_fprintf_header.h"
# include "./gnl/get_next_line_bonus.h"
# include "parsing.h"
# include "struct.h"
# include "src/execute/bulitin.h"
# include "src/utils/utils.h"

# define HEREDOC_TMP ".heredoc_tmp"

extern int	g_signal;

typedef struct	s_envp	t_envp;

t_tree	*parse(t_token *tokens);
t_token	*tokenize(const char *input, t_env *u_envp);

// utils.c
void	add_token(t_token **head, t_token **current, t_token *new_token);
t_token	*create_token(token_type type, const char *value);
void	merge_token(t_token **current, char *new_value);
t_tree	*create_tree_node(node_type type, const char *value);
void	add_child(t_tree *parent, t_tree *child);
void	free_tree(t_tree *node);
void	free_tokens(t_token *tokens);
void	free_master(t_envp *master);

// parsing.c
t_tree	*parse_pipe(t_token **current);
t_tree	*parse_exec(t_token **current);
void	parse_reds_opt(t_tree *exec_node, t_token **current);
t_tree *parse_reds(t_token **current);
t_tree *parse_cmd(t_token **current);

// replace_env.c
void	replace_env(t_token *tokens, t_env *u_envp);
void	process_env_replacement(char **value, t_env *u_envp);
int	is_valid_env_char(char c, int is_first);

// testing.c
void	print_tree(t_tree *node, int level);
void	print_tree_linear(t_tree *node);
void	print_tokens(t_token *head);

// check_path.c


char	**find_path(char **envp);
int		is_cmd(char *token, t_envp *master);
int		is_bulitin(char *cmd);
int		check_cmd_path(t_token *head, t_envp *master);
char	*return_absolute_path(t_tree *node, t_envp *master);

// executor.c
void	execute_tree(t_tree *root, t_envp *master);
void	close_all_pipe(int pipe_count, int **pipe_fds);
void	execute_pipe(t_tree *pipe_node, t_envp *master);
char	**each_args(t_tree *node, t_envp *master, int cnt);


// heredoc.c
void	handle_heredoc(const char *delimiter, t_env *u_envp, int i, int j);
char	*generate_filename(int i, int j);
void	remove_heredoc_files();


// interface.c
static char	*get_host_name(void);
char	*interface(t_env *shell_envp);


//main_utils
int	fd_print_exit(char *msg, int fd);

//builtin functions
int	builtin_cmd(t_tree *node, t_envp *env);

// signal.c

void	sig_int_prompt(int signo);
void	signal_handel_prompt();
void	signal_all_ign();
void	signal_all_dfl();
void	sig_int_execve(int signo);
void	sig_quit_execve(int signo);
void	signal_handle_execve();
void	signal_handle_heredoc();

#endif

