#include "utils.h"

char	**copy_envp(char **envp)
{
	int	i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (copy == NULL)
	{
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (envp[++i])
		copy[i] = ft_strdup(envp[i]);
	copy[i] = NULL;
	return (copy);
}

int	find_shlvl(char **envp)
{
	char	*shlvl;
	int	i;
	char	*temp;
	char	*now;
	char	*new;

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
}

void	set_master(t_envp *master)
{
	char	**c_envp;

	c_envp = copy_envp(master->envp);
	find_shlvl(c_envp);
	master->envp = c_envp;
	master->u_envp = init_env(c_envp);
}
