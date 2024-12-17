/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:21:30 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 20:23:20 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

char	*valid_path_fn(char *cmd, int is_abs, char *path)
{
	char	*valid;

	if (is_abs)
		valid = ft_strdup(cmd);
	else
		valid = ft_strjoincat(path, cmd, '/');
	return (valid);
}
