#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../minishell.h"
# include "../builtin/bulitin.h"
# include "../parser/parser_struct.h"


// -- executor.c -- //
void	execute_command(t_tree *exec_node, t_envp *master, int i);
void	gen_pipe_process(int pipe_count, int **pipe_fds, t_tree *pipe_node, t_envp *master);
void	execute_pipe(t_tree *pipe_node, t_envp *master);
void	execute_tree(t_tree *root, t_envp *master);

// -- executor_utils.c -- //
void	restore_stdio(int saved_stdin, int saved_stdout);
t_tree	*find_cmd_node(t_tree *node);
char	**each_args(t_tree *node, t_envp *master, int cnt);

// -- heredoc.c -- //
void	free_char_index(char *index_i, char *index_j);
char	*generate_filename(int i, int j);
void	handle_heredoc(const char *delimiter, t_env *u_envp, int i, int j);
void	remove_heredoc_files();
void	process_heredoc_node(t_tree *node, t_envp *master, int i, int j);

// -- redirection.c -- //
void	set_all_heredoc(t_tree *node, t_envp *master);
int	open_and_redirect(const char *filepath, int flags, int redirect_fd);
int	setup_redirection(t_tree *node, t_env *u_envp, int i, int j);

#endif