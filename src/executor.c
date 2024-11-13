#include "../minishell.h"


// 리다이렉션 설정 함수
int setup_redirection(t_tree *node)
{
	int fd;
	int pipefd[2];

	fd = -1;
	if (node->type == NODE_HEREDOC)
		handle_heredoc(node->children[0]->value);
	else if (node->type == NODE_RED)
	{
		if (strcmp(node->value, ">") == 0)
		{
			fd = open(node->children[0]->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (strcmp(node->value, ">>") == 0)
		{
			fd = open(node->children[0]->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (strcmp(node->value, "<") == 0)
		{
			fd = open(node->children[0]->value, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	return (0);
}


// 커맨드 실행
void execute_command(t_tree *exec_node, t_master *master)
{
	int i;
	int j;
	t_tree *cmd_node;
	char **args;

	i = 0;
	if (fork() == 0)
	{
		while (i < exec_node->child_count)
		{
			if (exec_node->children[i]->type == NODE_RED || exec_node->children[i]->type == NODE_HEREDOC)
			{
				if (setup_redirection(exec_node->children[i]) != 0)
					exit(1);
			}
			i++;
		}
		i = 0;
		while (i < exec_node->child_count)
		{
			if (exec_node->children[i]->type == NODE_CMD)
			{
				cmd_node = exec_node->children[i];
				args = malloc(sizeof(char *) * (cmd_node->child_count + 2));
				if (args == NULL)
					exit(1);
				args[0] = return_absolute_path(cmd_node, master);
				if (args[0] == NULL)
					exit(EXIT_FAILURE);
				j = 0;
				while (j < cmd_node->child_count)
				{
					args[j + 1] = cmd_node->children[j]->value;
					j++;
				}
				args[cmd_node->child_count + 1] = NULL;

				execve(args[0], args, master->envp);
				perror("execve failed");
				exit(1);
			}
			i++;
		}
		exit(0);
	}
	else
		wait(NULL);
}


void gen_pipe_process(int pipe_count, int **pipe_fds, t_tree *pipe_node, t_master *master)
{
	int	i;
	int	child_pid;

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
			execute_command(pipe_node->children[i], master);
			exit(0);
		}
		i++;
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
void execute_pipe(t_tree *pipe_node, t_master *master)
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
	while (i < pipe_count) {
		wait(NULL);
		i++;
	}
}

// 메인 명령어 실행 함수
void	execute_tree(t_tree *root, t_master *master)
{
	if (root->type == NODE_PIPE)
		execute_pipe(root, master);
	else if (root->type == NODE_EXEC)
		execute_command(root, master);
}
