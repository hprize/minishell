#include "bulitin.h"

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		strerror(errno);
		return (EXIT_FAILURE);
	}
	return (0);
}