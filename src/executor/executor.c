#include "executor.h"

// 커맨드 실행
void	execute_command(t_tree *exec_node, t_envp *master, int i)
{
	int		j;
	int		k;
	t_tree	*cmd_node;
	char	**args;

	j = 0;
	while (j < exec_node->child_count)
	{
		if (exec_node->children[j]->type == NODE_RED || exec_node->children[j]->type == NODE_HEREDOC)
		{
			if (setup_redirection(exec_node->children[j], master->u_envp, i, j) != 0)
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

void	gen_pipe_process(int pipe_count, int **pipe_fds, t_tree *pipe_node, t_envp *master)
{
	int		i;
	int		*child_pid;
	t_tree	*execute_node;
	int		status;
	int		les;
	char	*c_les;

	i = 0;
	child_pid = malloc(sizeof(int) * pipe_count);
	while (i < pipe_count)
	{
		if (i < pipe_count - 1)
			pipe(pipe_fds[i]);

		child_pid[i] = fork();
		if (child_pid[i] == 0)
		{
			if (i == 0)
			{
				dup2(pipe_fds[i][1], STDOUT_FILENO);
				close(pipe_fds[i][0]);
				close(pipe_fds[i][1]);
			}
			else if (i > 0 && i < pipe_count - 1)
			{
				dup2(pipe_fds[i - 1][0], STDIN_FILENO);
				close(pipe_fds[i - 1][0]);
				close(pipe_fds[i][0]);
				dup2(pipe_fds[i][1], STDOUT_FILENO);
				close(pipe_fds[i][1]);
			}
			else if (i == pipe_count - 1)
			{
				dup2(pipe_fds[i - 1][0], STDIN_FILENO);
				close(pipe_fds[i - 1][0]);
			}
			execute_node = find_cmd_node(pipe_node->children[i]);
			if (is_bulitin(execute_node->value) == 0)
			{
				les = builtin_cmd(pipe_node->children[i], master, i);
				exit(les);
			}
			else
				execute_command(pipe_node->children[i], master, i);
		}
		if (i == 0)
			close(pipe_fds[i][1]);
		else if (i > 0 && i < pipe_count - 1)
		{
			close(pipe_fds[i - 1][0]);
			close(pipe_fds[i][1]);
		}
		else if (i == pipe_count - 1)
			close(pipe_fds[i - 1][0]);
		i++;
	}
	i = 0;
	while (i < pipe_count)
	{
		waitpid(child_pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			c_les = ft_itoa(WEXITSTATUS(status));
			replace_content(master->u_envp, "LAST_EXIT_STATUS", c_les);
			free(c_les);
		}
		else if (WIFSIGNALED(status))
		{
			c_les = ft_itoa(WTERMSIG(status + 128));
			replace_content(master->u_envp, "LAST_EXIT_STATUS", c_les);
			free(c_les);
		}
		i++;
	}
}

// PIPE 실행
void	execute_pipe(t_tree *pipe_node, t_envp *master)
{
	int	pipe_count;
	int	**pipe_fds;
	int	i;

	pipe_count = pipe_node->child_count;
	pipe_fds = malloc(sizeof(int*) * (pipe_count - 1));
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
	t_tree	*cmd_node;
	int		status;
	char	*les;
	int		i;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		strerror_exit();
	// signal_handle_execve();
	if (root->type == NODE_PIPE)
		execute_pipe(root, master);
	else if (root->type == NODE_EXEC)
	{
		cmd_node = find_cmd_node(root);
		if (cmd_node == NULL)
		{
			// signal_handle_heredoc();
			set_all_heredoc(root, master);
			i = 0;
			while (i < root->child_count)
			{
				if (root->children[i]->type == NODE_RED || root->children[i]->type == NODE_HEREDOC)
				{
					if (setup_redirection(root->children[i], master->u_envp, 0, i) < 0)
					{
						perror("minishell: failed to set redirection");
						restore_stdio(saved_stdin, saved_stdout);
						exit(1);
					}
				}
				i++;
			}
			restore_stdio(saved_stdin, saved_stdout);
			return;
		}
		if (is_bulitin(cmd_node->value) == 0)
		{
			les = ft_itoa(builtin_cmd(root, master, 0));
			replace_content(master->u_envp, "LAST_EXIT_STATUS", les);
			free(les);
		}
		else
		{
			set_all_heredoc(root, master);
			signal_all_ign();
			signal_all_dfl();
			signal_handle_execve();
			if (fork() == 0)
				execute_command(root, master, 0);
			wait(&status);
			if (WIFEXITED(status))
			{
				les = ft_itoa(WEXITSTATUS(status));

				strerror(errno);
				replace_content(master->u_envp, "LAST_EXIT_STATUS", les);
				free(les);
			}
			else if (WIFSIGNALED(status))
			{
				int	sig = WTERMSIG(status);
				les = ft_itoa(WTERMSIG(status + 128));
			}
		}
	}
	restore_stdio(saved_stdin, saved_stdout);
}
