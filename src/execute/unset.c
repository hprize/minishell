#include "bulitin.h"

int	find_unset_value(t_env *env, char *value)
{
	t_env	*cur;
	t_env	*pre;
	t_env	*temp;

	cur = env;
	pre = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->var->name, value, ft_strlen(value)) == 0)
		{
			// printf("test unset\n");
			if (pre == NULL)
				env = cur->next;
			else
				pre->next = cur->next;
			temp = cur;
			pre = cur;
			cur = cur->next;
			free_env(temp);
			break;
		}
		pre = cur;
		cur = cur->next;
	}
	return (0);
}

int	unset(char **args, t_envp *master)
{
	int	i;
	int	j;
	char	*temp;

	if (master->u_envp == NULL)
		exit(0);
	i = -1;
	while (args[++i])
	{
		find_unset_value(master->u_envp, args[i]);
		if (ft_strcmp(args[i], "PATH") == 0)
		{
			j = -1;
			while (master->envp[++j])
			{
				if (ft_strncmp(master->envp[j], "PATH", 4) == 0)
				{
					temp = master->envp[j];
					master->envp[j] = ft_strdup("");
					free(temp);
				}
			}
		}
	}
	return (0);
}
