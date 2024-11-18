#include "../minishell.h"

char	**find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	return (ft_split(envp[i] + 5, ':'));
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

//cmd == 1 not_cmd == 0
int	is_cmd(char *token, t_master *master)
{
	// char	**path_list;
	char	*valid_path;
	int		is_abs;
	int		i;

	i = -1;
	// path_list = find_path(envp);
	is_abs = strchr_is(token, '/');
	while ((master->path_list)[++i])
	{
		valid_path = valid_path_fn(token, is_abs, (master->path_list)[i]);
		if (access(valid_path, F_OK) == 0)
		{
			free(valid_path); // 나중에 실행명령어 할 때 이거 살리면 됨.
			return (1);
		}
		free(valid_path);
	}
	return (0);
}
// 이거 추가됨. 빌트인 함수 확인

int	is_bulitin(char *cmd)
{
	if ((ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0) || \
	(ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0) || \
	(ft_strncmp(cmd, "env", ft_strlen("env")) == 0) || \
	(ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0) || \
	(ft_strncmp(cmd, "export", ft_strlen("export")) == 0) || \
	(ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0) || \
	(ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0))
		return (1);
	else
		return (0);
}

int check_cmd_path(t_token *head, t_master *master)
{
	t_token *current;
	
	current = head;
	while (current != NULL)
	{
		if (current->type == TOKEN_CMD)
			//여기 수정
			if (is_cmd(current->value, master) || is_bulitin(current->value))
				printf("cmd Token - value: %s, type: %d\n", current->value, current->type);
			else
			{
				printf("%s: command not found\n", current->value);
				return (-1);
			}
		current = current->next;
	}
	return (0);
}

char	*return_absolute_path(t_tree *node, t_master *master)
{
	char	*valid_path;
	int		is_abs;
	int		i;

	i = -1;
	is_abs = strchr_is(node->value, '/');
	while ((master->path_list)[++i])
	{
		valid_path = valid_path_fn(node->value, is_abs, (master->path_list)[i]);
		if (access(valid_path, F_OK) == 0)
			return (valid_path);
		free(valid_path);
	}
	return (NULL);
}