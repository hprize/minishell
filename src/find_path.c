#include "../minishell.h"

// char	*execute_path(char)

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

//특정 char 있으면 return 1
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
int		is_cmd(char *token, char **envp)
{
	char	**path_list;
	char	*valid_path;
	int		is_abs;
	int		i;

	i = -1;
	path_list = find_path(envp);
	is_abs = strchr_is(token, '/');
	while (path_list[++i])
	{
		valid_path = valid_path_fn(token, is_abs, path_list[i]);
		if (access(valid_path, F_OK) == 0)
			return (1);
		free(valid_path);
	}
	return (0);
}