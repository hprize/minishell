#include "bulitin.h"

char	*is_envp(char *arg, t_env *env)
{
	t_env	*cur;

	if (!env || !arg)
		return (NULL);

	if (*arg == '$')
		arg++;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, arg) == 0)
			return (ft_strdup(cur->var->content));
		cur = cur->next;
	}
	return (NULL);
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
			printf("%s", args[i]);
			printf(" ");
		if (!args[i + 1])
		{
			if (newline == 0)
				printf("\n");
		}
		// if (is_envp(args[i], env) == 1)
		// 	printf("%s", args[i]);
		// if (!args[i + 1])
		// {
		// 	if (newline == 0)
		// 		printf("\n");
		// }
		i++;
	}
	return (0);
}
