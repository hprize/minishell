#include "executor.h"

void	process_all_heredocs(t_tree *parent, t_envp *master, int parent_index)
{
	int	i;

	i = 0;
	while (i < parent->child_count)
	{
		if (parent->children[i]->type == NODE_HEREDOC)
			process_heredoc_node(parent, master, parent_index, i);
		i++;
	}
}

void	set_all_heredoc(t_tree *node, t_envp *master)
{
	t_tree	*current;
	int		i;

	signal_all_ign();
	i = 0;
	if (node->type == NODE_EXEC)
		process_all_heredocs(node, master, 0);
	else if (node->type == NODE_PIPE)
	{
		while (i < node->child_count)
		{
			current = node->children[i];
			process_all_heredocs(current, master, i);
			i++;
		}
	}
}

int	open_and_redirect(const char *filepath, int flags, int redirect_fd)
{
	int	fd;

	fd = open(filepath, flags, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", filepath, strerror(errno));
		return (-1);
	}
	if (dup2(fd, redirect_fd) < 0)
	{
		ft_fprintf(2, "minishell: %s: dup2 failed\n", filepath);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_redirection(const char *value, const char *filename)
{
	int	flags;
	int	fd;

	if (strcmp(value, ">") == 0)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = STDOUT_FILENO;
	}
	else if (strcmp(value, ">>") == 0)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		fd = STDOUT_FILENO;
	}
	else if (strcmp(value, "<") == 0)
	{
		flags = O_RDONLY;
		fd = STDIN_FILENO;
	}
	else
		return (-1);
	if (open_and_redirect(filename, flags, fd) < 0)
		return (-1);
	return (0);
}

int	setup_redirection(t_tree *node, int i, int j)
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
		if (handle_redirection(node->value, node->children[0]->value) < 0)
			return (-1);
	}
	return (0);
}
