#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./ft_fprintf/ft_fprintf_header.h"
# include "parse_input.h"
# include "struct.h"

//main_utils
int	fd_print_exit(char *msg, int fd);

//builtin functions
int	builtin_cmd(t_env *env, char *input);

//env
t_env	*init_env(char** envp);
int	ft_env(t_env *env);


#endif
