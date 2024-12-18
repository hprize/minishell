/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:02:54 by junlee            #+#    #+#             */
/*   Updated: 2024/12/18 20:37:48 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../minishell.h"
# include "../builtin/bulitin.h"
# include "../parser/parser_struct.h"

// -- executor_exec.c -- //
void	handle_red_exec(t_tree *root, t_envp *master, int s_stdin, \
						int s_stdout);
void	handle_execve_exec(t_tree *root, t_envp *master);
void	execute_exec(t_tree *root, t_envp *master, int s_stdin, int s_stdout);

// -- executor_handle_fd.c -- //
void	restore_stdio(int s_stdin, int s_stdout);
void	setup_pipe_io(int i, int pipe_count, int **pipe_fds);
void	close_unused_pipes(int i, int pipe_count, int **pipe_fds);

// -- executor_utils.c -- //
t_tree	*find_cmd_node(t_tree *node);
char	**each_args(t_tree *node, t_envp *master, int cnt);
void	handle_child_status(int pid, t_envp *master);
void	free_pipe_fds(int **pipe_fds, int pipe_count);

// -- executor.c -- //
void	execute_command(t_tree *exec_node, t_envp *master, int i);
void	execute_node_command(t_tree *node, t_envp *master, int i);
void	gen_pipe_process(int pipe_count, int **pipe_fds, t_tree *pipe_node, \
						t_envp *master);
void	execute_pipe(t_tree *pipe_node, t_envp *master);
void	execute_tree(t_tree *root, t_envp *master);

// -- heredoc_utils.c -- //
void	free_char_index(char *index_i, char *index_j);
char	*generate_filename(int i, int j);

// -- heredoc.c -- //
void	process_heredoc_input(const char *delimiter, t_env *u_envp, int fd);
void	handle_heredoc(const char *delimiter, t_env *u_envp, int i, int j);
void	remove_heredoc_files(void);
void	handle_heredoc_child_status(t_envp *master, int status);
void	process_heredoc_node(t_tree *node, t_envp *master, int i, int j);

// -- redirection.c -- //
void	set_all_heredoc(t_tree *node, t_envp *master);
int		open_and_redirect(const char *filepath, int flags, int redirect_fd);
int		setup_redirection(t_tree *node, int i, int j);

#endif