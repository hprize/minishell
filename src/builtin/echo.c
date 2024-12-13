#include "bulitin.h"

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
		if (args[i + 1])
			printf(" ");
		if (!args[i + 1])
		{
			if (newline == 0)
				printf("\n");
		}
		i++;
	}
	return (0);
}
