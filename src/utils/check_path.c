#include "utils.h"

char	**find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	strchr_is(char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		else
			i++;
	}
	if (s[i] == (char)c)
		return (1);
	return (0);
}

char	*ft_strjoincat(char *s1, char *s2, char c)
{
	int		i;
	int		j;
	char	*arr;

	arr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = c;
	i++;
	while (s2[j])
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	return (arr);
}

char	*valid_path_fn(char *cmd, int is_abs, char *path)
{
	char	*valid;

	if (is_abs)
		valid = ft_strdup(cmd);
	else
		valid = ft_strjoincat(path, cmd, '/');
	return (valid);
}

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
			if (is_cmd(current->value, master) == 0 || is_bulitin(current->value) == 0) ;
			else
			{
				ft_putstr_fd("command not found\n", 2);
				return (-1);
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
		return (NULL);
	while (path_list[++i])
	{
		valid_path = valid_path_fn(node->value, is_abs, path_list[i]);
		if (access(valid_path, F_OK) == 0)
			return (valid_path);
		free(valid_path);
	}
	return (NULL);
}
