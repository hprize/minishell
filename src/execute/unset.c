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
			printf("test unset\n");
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

int	unset(char **args, t_env *env)
{
	int	i;
	t_env	*temp;

	if (env == NULL)
		exit(0);
	i = -1;
	while (args[++i])
	{
		find_unset_value(env, args[i]);
	}
	return (0);
}
