#ifndef BULITIN_H
# define BULITIN_H
#include "../../minishell.h"
#include "../../struct.h"
# include "../parser/parser_struct.h"
#include "../executor/executor.h"
#include "../utils/utils.h"

//env.c
int	ft_env(char **args, t_env *env);

//exit.c
void	ft_exit_call(int count, char **args, t_env *envp);

//export.c
int		export(t_tree *node, char **args, t_env *env);

// unset.c
int	unset(char **args, t_envp *master);

// pwd.c
int	ft_pwd(void);

// cd.c
int ft_cd(t_tree *node, char **args, t_env *env);

// echo.c
int	ft_echo(char **args, t_env *env);

// builtin.c
static int	dispatch_builtin(char *cmd, char **args, t_tree *node, t_envp *master);
int			builtin_cmd(t_tree *node, t_envp *master);

#endif