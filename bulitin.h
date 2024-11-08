#ifndef BULITIN_H
# define BULITIN_H
# include "struct.h"

t_env	*creat_node(char *data);
void	append_node(t_env **head, char *data);
void	print_node(t_env *head);
void	free_node(t_env *head);
t_env	*init_env(char **envp);

#endif