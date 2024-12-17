/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:19:38 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 20:22:39 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	execute_command(t_tree *exec_node, t_envp *master, int i)
{
	int		j;
	int		k;
	t_tree	*cmd_node;
	char	**args;

	j = 0;
	while (j < exec_node->child_count)
	{
		if (exec_node->children[j]->type == NODE_RED || \
			exec_node->children[j]->type == NODE_HEREDOC)
		{
			if (setup_redirection(exec_node->children[j], i, j) != 0)
				exit(1);
		}
		j++;
	}
	cmd_node = find_cmd_node(exec_node);
	if (cmd_node != NULL)
	{
		args = each_args(cmd_node, master, 1);
		k = execve(args[0], args, master->envp);
		if (k != 0)
			handle_execve_error(cmd_node);
		exit(1);
	}
}

void	execute_node_command(t_tree *node, t_envp *master, int i)
{
	t_tree	*execute_node;
	int		les;

	execute_node = find_cmd_node(node);
	if (is_bulitin(execute_node->value) == 0)
	{
		les = builtin_cmd(node, master, i);
		exit(les);
	}
	else
		execute_command(node, master, i);
}

void	gen_pipe_process(int pipe_count, int **pipe_fds, t_tree *pipe_node, \
						t_envp *master)
{
	int	i;
	int	*child_pid;

	i = 0;
	child_pid = malloc(sizeof(int) * pipe_count);
	while (i < pipe_count)
	{
		if (i < pipe_count - 1)
			pipe(pipe_fds[i]);
		child_pid[i] = fork();
		if (child_pid[i] == 0)
		{
			setup_pipe_io(i, pipe_count, pipe_fds);
			execute_node_command(pipe_node->children[i], master, i);
		}
		close_unused_pipes(i, pipe_count, pipe_fds);
		i++;
	}
	i = 0;
	while (i < pipe_count)
	{
		handle_child_status(child_pid[i], master);
		i++;
	}
	free(child_pid);
}

void	execute_pipe(t_tree *pipe_node, t_envp *master)
{
	int	pipe_count;
	int	**pipe_fds;
	int	i;

	pipe_count = pipe_node->child_count;
	pipe_fds = malloc(sizeof(int *) * (pipe_count - 1));
	i = -1;
	if (!pipe_fds)
		strerror_exit();
	while (++i < pipe_count - 1)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		if (pipe_fds[i] == NULL)
		{
			while (i-- > 0)
				free(pipe_fds[i]);
			free(pipe_fds);
			strerror_exit();
		}
	}
	set_all_heredoc(pipe_node, master);
	g_signal = 0;
	signal_all_dfl();
	signal_handle_execve();
	gen_pipe_process(pipe_count, pipe_fds, pipe_node, master);
}

void	execute_tree(t_tree *root, t_envp *master)
{
	int	s_stdin;
	int	s_stdout;

	s_stdin = dup(STDIN_FILENO);
	s_stdout = dup(STDOUT_FILENO);
	if (s_stdin < 0 || s_stdout < 0)
		strerror_exit();
	if (root->type == NODE_PIPE)
		execute_pipe(root, master);
	else if (root->type == NODE_EXEC)
		execute_exec(root, master, s_stdin, s_stdout);
	restore_stdio(s_stdin, s_stdout);
}
