#include "bulitin.h"

char	*find_envp_content(t_env *envp, char *name)
{
	t_env	*cur;
	char	*temp;

	if (envp == NULL)
		return (NULL);
	cur = envp;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, name) == 0)
		{
			return (cur->var->content);
		}
		cur = cur->next;
	}
	return (NULL);
}

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
			free(temp);
			return ;
		}
		cur = cur->next;
	}
}

int	ft_cd(t_tree *node, char **args, t_env *env)
{
	char	*way;
	char	*old;
	char	pwd[1024];

	if (node->child_count != 1)
		fd_print_exit("too many argument\n", 2);
	old = find_envp_content(env, "PWD");
	way = args[0];
	if (ft_strcmp(args[0], "-") == 0)
		way = old;
	else if (ft_strcmp(args[0], "~") == 0)
		way = find_envp_content(env, "HOME");
	printf("test cd %s\n", way);
	if (chdir(way) == 0)
	{
		printf("cd success\n");
		if (getcwd(pwd, sizeof(pwd)) == NULL)
			exit(1);
		change_env(env, "OLDPWD", old);
		change_env(env, "PWD", pwd);
	}
	else
		perror("chdir failed");

	return (0);
}
