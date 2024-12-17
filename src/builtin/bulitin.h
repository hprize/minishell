#ifndef BULITIN_H
# define BULITIN_H
# include "../../minishell.h"
# include "../../struct.h"
# include "../parser/parser_struct.h"
# include "../executor/executor.h"
# include "../utils/utils.h"

int		ft_env(char **args, t_env *env);
void	ft_exit_call(int count, char **args, t_env *envp);
int		export(t_tree *node, char **args, t_env *env);
int		unset(char **args, t_envp *master);
int		ft_pwd(void);
int		ft_cd(t_tree *node, char **args, t_env *env);
int		ft_echo(char **args, t_env *env);
int		builtin_cmd(t_tree *exec_node, t_envp *master, int i);

#endif