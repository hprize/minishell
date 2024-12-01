#include "../minishell.h"

void	set_all_heredoc(t_tree *node, t_envp *master)
{
	t_tree	*current;
	int		i;
	int		j;

	signal_all_ign();
	
	// signal_handle_heredoc();
	i = 0;
	if (node->type == NODE_EXEC)
	{
		while (i < node->child_count)
		{
			if (node->children[i]->type == NODE_HEREDOC)
			{
				process_heredoc_node(node, master, 0, i);
			}
			i++;
		}
	}
	else if (node->type == NODE_PIPE)
	{
		while (i < node->child_count)
		{
			j = 0;
			current = node->children[i];
			while (j < current->child_count)
			{
				if (current->children[j]->type == NODE_HEREDOC)
				{
					process_heredoc_node(current, master, i, j);
				}
				j++;
			}
			i++;
		}
	}
}

int	open_and_redirect(const char *filepath, int flags, int redirect_fd)
{
	int fd;

	fd = open(filepath, flags, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", filepath, strerror(errno));
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

int	setup_redirection(t_tree *node, t_env *u_envp, int i, int j)
{
	char	*filename;

	if (node->type == NODE_HEREDOC)
	{
		filename = generate_filename(i, j);
		if (open_and_redirect(filename, O_RDONLY, STDIN_FILENO) < 0)
		{
			free(filename);
			return (-1);
		}
		free(filename);
	}
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