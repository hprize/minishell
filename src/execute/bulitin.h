#ifndef BULITIN_H
# define BULITIN_H
#include "../../struct.h"
#include "../../parsing.h"
#include "../../minishell.h"

// init_env.c
t_env	*creat_node(char *data);
void	append_node(t_env **head, char *data);
void	print_node(t_env *head);
void	free_node(t_env *head);
t_env	*init_env(char **envp);
void	free_env(t_env *node);
void	add_node_back(t_env *head, t_env *new);

//export.c
int		export(t_tree *node, char **args, t_env *env);

// unset.c
int	unset(char **args, t_env *env);

// pwd.c
int	ft_pwd(void);

// cd.c
int ft_cd(t_tree *node, char **args, t_env *env);

// echo.c
int	ft_echo(char **args, t_env *env);

#endif