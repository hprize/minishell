#ifndef UTILS_H
# define UTILS_H
#include "../../struct.h"
#include "../../parsing.h"
#include "../../minishell.h"

//init_env.c
t_env	*create_t_env(void);
void	print_node(t_env *head);
void	set_envp_flag(t_env *env);
t_env	*init_env(char **envp);

//node_create_utils.c
t_env	*creat_node(char *data);
void	add_node_back(t_env **head, t_env *new);
t_env	*new_node(t_var *var);
void	append_node(t_env **head, char *data);
void	append_custom_node_back(t_env **head, char *name, char *value, int flag);
void	free_node(t_env *head);
void	free_env(t_env *node);

// node_edit_utils.c
int		replace_content(t_env *head, char *name, char *content);
char	*find_content(char *arg, t_env *env);
char	*is_envp(char *arg, t_env *env);

#endif