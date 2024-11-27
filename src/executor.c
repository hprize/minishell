#include "../minishell.h"

int open_and_redirect(const char *filepath, int flags, int redirect_fd)
{
	int fd;

	fd = open(filepath, flags, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", filepath, strerror(errno));
		//perror("minishell: ");
		return (-1);
	}
	if (dup2(fd, redirect_fd) < 0)
	{
		printf("minishell: %s: dup2 failed\n", filepath);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

// 리다이렉션 설정 함수
int setup_redirection(t_tree *node, t_env *u_envp)
{
	if (node->type == NODE_HEREDOC)
		handle_heredoc(node->children[0]->value, u_envp);
	else if (node->type == NODE_RED)
	{
		if (strcmp(node->value, ">") == 0)
		{
			if (open_and_redirect(node->children[0]->value, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO) < 0)
				return (-1);
		}
		else if (strcmp(node->value, ">>") == 0)
		{
			if (open_and_redirect(node->children[0]->value, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO) < 0)
				return (-1);
		}
		else if (strcmp(node->value, "<") == 0)
		{
			if (open_and_redirect(node->children[0]->value, O_RDONLY, STDIN_FILENO) < 0)
				return (-1);
		}
	}
	return (0);
}

char	**each_args(t_tree *node, t_envp *master, int cnt)
{
	char	**args;
	int		i;
	int		j;

	args = malloc(sizeof(char *) * (node->child_count + cnt + 1));
	if (args == NULL)
		exit(1);
	if (cnt == 1)
	{
		args[0] = return_absolute_path(node, master);
		if (args[0] == NULL)
			exit(EXIT_FAILURE);
	}
	i = cnt;
	j = 0;
	while (j < node->child_count)
	{
		args[i] = ft_strdup(node->children[j]->value);
		if (args[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
		j++;
	}
	args[i] = NULL;
	return (args);
}

t_tree	*find_cmd_node(t_tree *node)
{
	int	i;
	t_tree	*now;

	now = node;
	i = 0;
	while (i < now->child_count)
	{
		if (now->children[i]->type == NODE_CMD)
			return (now->children[i]);
		i++;
	}
	return (NULL);
}

// 커맨드 실행
void execute_command(t_tree *exec_node, t_envp *master)
{
	int i;
	int j;
	int	bulitin;
	t_tree *cmd_node;
	char **args;

	i = 0;
	if (fork() == 0)
	{
		while (i < exec_node->child_count)
		{
			if (exec_node->children[i]->type == NODE_RED || exec_node->children[i]->type == NODE_HEREDOC)
			{
				if (setup_redirection(exec_node->children[i], master->u_envp) != 0)
					exit(1);
			}
			i++;
		}
		cmd_node = find_cmd_node(exec_node);
		if (cmd_node != NULL)
		{
			bulitin = is_bulitin(cmd_node->value);
			args = each_args(cmd_node, master, bulitin);

			FILE* tty_fd = fopen("/dev/tty", "w");
			int debug_i = 0;
			while (args[debug_i])
			{
				fprintf(tty_fd,"args[%d]: %s\n", debug_i, args[debug_i]);
				debug_i++;
			}
			execve(args[0], args, master->envp);
			perror("execve failed");
			exit(1);
		}
		exit(0);
	}
	
	
}

int	replace_content(t_env *head, char *name, char *content)
{
	t_env	*cur;
	char	*temp;

	if (head == NULL)
		return (0);
	cur = head;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, name) == 0)
		{
			temp = cur->var->content;
			cur->var->content = ft_strdup(content);
			free(temp);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

void gen_pipe_process(int pipe_count, int **pipe_fds, t_tree *pipe_node, t_envp *master)
{
	int	i;
	int	child_pid;
	int	status;
	t_tree	*execute_node;

	i = 0;
	while (i < pipe_count)
	{
		if (i < pipe_count - 1)
			pipe(pipe_fds[i]);

		child_pid = fork();
		if (child_pid == 0)
		{
			if (i > 0)
			{
				dup2(pipe_fds[i - 1][0], STDIN_FILENO);
				close(pipe_fds[i - 1][0]);
			}
			if (i < pipe_count - 1)
			{
				dup2(pipe_fds[i][1], STDOUT_FILENO);
				close(pipe_fds[i][1]);
			}

			close_all_pipe(pipe_count, pipe_fds);
			execute_node = find_cmd_node(pipe_node->children[i]);
			if (is_bulitin(execute_node->value) == 0)
				exit(builtin_cmd(execute_node, master));
			else
				execute_command(pipe_node->children[i], master);

			exit(0);
		}
		i++;
		wait(&status);
		if (WIFEXITED(status))
		{
			int last_exit_code = WEXITSTATUS(status);
			replace_content(master->u_envp, "LAST_EXIT_STATUS", ft_itoa(last_exit_code));
		}
		else if (WIFSIGNALED(status))
		{
			int last_exit_code = WEXITSTATUS(status);
			int signal_num = WTERMSIG(status);
			printf("ERR exit code : %d, signal : %d\n", last_exit_code, signal_num);
			replace_content(master->u_envp, "LAST_EXIT_STATUS", ft_itoa(last_exit_code));
		}
	}
}


void	close_all_pipe(int pipe_count, int **pipe_fds)
{
	int i;

	i = 0;
	while (i < pipe_count - 1) {
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}

// PIPE 실행
void execute_pipe(t_tree *pipe_node, t_envp *master)
{
	int pipe_count;
	int **pipe_fds;
	int i;

	pipe_count = pipe_node->child_count;
	pipe_fds = malloc(sizeof(int*) * (pipe_count - 1));
	i = 0;
	if (!pipe_fds)
	{
		printf("malloc failed\n");
		exit(1);
	}
	while (i < pipe_count - 1)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		if (pipe_fds[i] == NULL)
		{
			printf("malloc failed\n");
			while (i-- > 0)
				free(pipe_fds[i]);
			free(pipe_fds);
			exit(1);
		}
		i++;
	}

	gen_pipe_process(pipe_count, pipe_fds, pipe_node, master);
	close_all_pipe(pipe_count, pipe_fds);
	i = 0;
	while (i < pipe_count)
	{
		wait(NULL);
		i++;
	}
}

// 메인 명령어 실행 함수
void	execute_tree(t_tree *root, t_envp *master)
{
	t_tree	*execute_node;
	int		last_exit_code;

	if (root->type == NODE_PIPE)
		execute_pipe(root, master);
	else if (root->type == NODE_EXEC)
	{
		execute_node = find_cmd_node(root);
		if (is_bulitin(execute_node->value) == 0)
		{
			last_exit_code = builtin_cmd(execute_node, master);
			replace_content(master->u_envp, "LAST_EXIT_STATUS", ft_itoa(last_exit_code));
		}
		else
			execute_command(root, master);
	}


}
