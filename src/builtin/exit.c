#include "bulitin.h"

void	ft_exit_call(int count, char **args, t_env *envp)
{
	int	result;

	result = ft_atoi(find_content("LAST_EXIT_STATUS", envp));
	if (count > 1)
	{
		perror("too many arguments");
	}
	else if (count == 1)
		exit (ft_atoi(args[0]) % 256);
	else
		exit (result);
}
