/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:21:36 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 22:30:05 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (copy == NULL)
		strerror_exit();
	i = -1;
	while (envp[++i])
		copy[i] = ft_strdup(envp[i]);
	copy[i] = NULL;
	return (copy);
}

int	find_shlvl(char **envp)
{
	char	*shlvl;
	int		i;
	char	*temp;
	char	*now;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			now = ft_strchr(envp[i], '=') + 1;
			shlvl = ft_itoa(ft_atoi(now) + 1);
			now = ft_strjoin("SHLVL=", shlvl);
			temp = envp[i];
			envp[i] = now;
			free(temp);
			free(shlvl);
			return (1);
		}
		i++;
	}
	return (0);
}

void	set_master(t_envp **master, const char **envp)
{
	char	**c_envp;

	*master = ft_calloc(1, sizeof(t_envp));
	if (*master == NULL)
		strerror_exit();
	(*master)->envp = (char **)envp;
	(*master)->path_list = find_path((*master)->envp);
	c_envp = copy_envp((*master)->envp);
	find_shlvl(c_envp);
	(*master)->envp = c_envp;
	(*master)->u_envp = init_env(c_envp);
}
