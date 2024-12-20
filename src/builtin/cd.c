/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:54:50 by hyebinle          #+#    #+#             */

/*   Updated: 2024/12/19 02:14:29 by hyebinle         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "bulitin.h"

void	change_env(t_env *envp, char *name, char *content)
{
	t_env	*cur;
	char	*temp;

	if (envp == NULL)
		return ;
	cur = envp;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, name) == 0)
		{
			temp = cur->var->content;
			cur->var->content = ft_strdup(content);
			if (temp != NULL)
				free(temp);
			return ;
		}
		cur = cur->next;
	}
}

static char	*find_way(char **args, t_env *env)
{
	char	*way;

	way = args[0];
	if (ft_strcmp(args[0], "-") == 0)
		way = find_content("OLDPWD", env);
	else if (ft_strcmp(args[0], "~") == 0)
		way = find_content("HOME", env);
	return (way);
}

static void	chdir_suc(char *pwd, char *old, t_env *env)
{
	if (getcwd(pwd, sizeof(char) * 1024) == NULL)
		exit(1);
	change_env(env, "OLDPWD", old);
	change_env(env, "PWD", pwd);
}

int	ft_cd(t_tree *node, char **args, t_env *env)
{
	char	*way;
	char	*old;
	char	pwd[1024];

	if (node->child_count == 0)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (node->child_count != 1)
	{
		ft_putstr_fd("too many argument\n", 2);
		return (1);
	}
	old = find_content("PWD", env);
	way = find_way(args, env);
	if (chdir(way) == 0)
		chdir_suc(pwd, old, env);
	else
	{
		strerror(errno);
		return (1);
	}
	return (0);
}
