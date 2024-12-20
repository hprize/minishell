/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:21:45 by junlee            #+#    #+#             */
/*   Updated: 2024/12/19 03:14:51 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_cmd(char *token, t_envp *master)
{
	char	*valid_path;
	int		is_abs;
	int		i;

	i = -1;
	is_abs = strchr_is(token, '/');
	while ((master->path_list)[++i])
	{
		valid_path = valid_path_fn(token, is_abs, (master->path_list)[i]);
		if (access(valid_path, F_OK) == 0)
		{
			free(valid_path);
			return (0);
		}
		free(valid_path);
	}
	return (1);
}

int	is_bulitin(char *cmd)
{
	if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (0);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (0);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (0);
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (0);
	else if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (0);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (0);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (0);
	else
		return (1);
}

int	check_cmd_path(t_token *head, t_envp *master)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == TOKEN_CMD)
		{
			if (is_cmd(current->value, master) != 0 && \
				is_bulitin(current->value) != 0)
			{
				ft_putstr_fd("command not found\n", 2);
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

char	*return_absolute_path(t_tree *node, t_envp *master)
{
	char	**path_list;
	char	*valid_path;
	int		is_abs;
	int		i;

	i = -1;
	is_abs = strchr_is(node->value, '/');
	path_list = find_path(master->envp);
	if (path_list == NULL)
	{
		// ft_arrfree(path_list);
		return (NULL);
	}
	while (path_list[++i])
	{
		valid_path = valid_path_fn(node->value, is_abs, path_list[i]);
		if (access(valid_path, F_OK) == 0)
		{
			ft_arrfree(path_list);
			return (valid_path);
		}
		free(valid_path);
	}
	// ft_arrfree(path_list);
	return (NULL);
}
