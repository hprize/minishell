#ifndef ERROR_H
# define ERROR_H
# include "../../minishell.h"

void	handle_execve_error(t_tree *node);
void	strerror_exit(void);

#endif