#include "../minishell.h"

int	fd_print_exit(char *msg, int fd)
{
	ft_fputstr_print(fd, msg, 0);
	exit(1);
}