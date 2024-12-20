/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:57:03 by hyebinle          #+#    #+#             */
/*   Updated: 2024/12/17 22:25:08 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULITIN_H
# define BULITIN_H
# include "../../minishell.h"
# include "../../struct.h"
# include "../parser/parser_struct.h"
# include "../executor/executor.h"
# include "../utils/utils.h"

int		ft_env(char **args, t_env *env);
void	ft_exit_call(int count, char **args, t_env *envp);
int		export(char **args, t_env *env);
int		unset(char **args, t_envp *master);
int		ft_pwd(void);
int		ft_cd(t_tree *node, char **args, t_env *env);
int		ft_echo(char **args);
int		builtin_cmd(t_tree *exec_node, t_envp *master, int i);

void	insert_sorted(t_env **sorted_head, t_env *new_node);
t_env	*sorted_envp_list(t_env *head);

#endif