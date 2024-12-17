/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:19:43 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 20:22:18 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

void	handle_child_status(int pid, t_envp *master)
{
	int		status;
	char	*c_les;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		c_les = ft_itoa(WEXITSTATUS(status));
		replace_content(master->u_envp, "LAST_EXIT_STATUS", c_les);
		free(c_les);
	}
	else if (WIFSIGNALED(status))
	{
		c_les = ft_itoa(WTERMSIG(status) + 128);
		replace_content(master->u_envp, "LAST_EXIT_STATUS", c_les);
		free(c_les);
	}
}
