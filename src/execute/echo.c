#include "bulitin.h"

int	is_envp(char *arg, t_env *env)
{
	t_env	*cur;

	if (env == NULL)
		return (1);
	if (*arg != '$')
		return (1);
	arg++;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, arg) == 0)
		{
			printf("%s", cur->var->content);
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	ft_echo(char **args, t_env *env)
{
	int	newline;
	int	i;

	i = -1;
	newline = 0;
	while (ft_strcmp("-n", args[++i]) == 0)
		newline = 1;
	while (args[i])
	{
		if (is_envp(args[i], env) == 1)
			printf("%s", args[i]);
		if (!args[i + 1])
		{
			if (newline == 0)
				printf("\n");
		}
		else
			printf(" ");
		i++;
	}
	return (0);
}
