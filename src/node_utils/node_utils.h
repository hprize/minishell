/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:18:01 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 20:18:16 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_UTILS_H
# define NODE_UTILS_H
# include "../../minishell.h"
# include "../../struct.h"
// #include "../../parsing.h"

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
void	append_cust_node_back(t_env **head, char *name, char *value, int flag);
void	free_node(t_env *head);
void	free_env(t_env *node);

// node_edit_utils.c
int		replace_content(t_env *head, char *name, char *content);
char	*find_content(char *arg, t_env *env);
char	*return_env_value(char *arg, t_env *env);

#endif