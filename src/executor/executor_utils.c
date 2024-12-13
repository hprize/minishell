#include "executor.h"

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) < 0)
		perror("Failed to restore stdin");
	close(saved_stdin);
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		perror("Failed to restore stdout");
	close(saved_stdout);
}

t_tree	*find_cmd_node(t_tree *node)
{
	int		i;
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

char	**each_args(t_tree *node, t_envp *master, int cnt)
{
	char	**args;
	int		i;
	int		j;

	args = malloc(sizeof(char *) * (node->child_count + cnt + 1));
	if (args == NULL)
		strerror_exit();
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
