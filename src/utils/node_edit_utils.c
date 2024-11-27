#include "utils.h"

int	replace_content(t_env *head, char *name, char *content)
{
	t_env	*cur;
	char	*temp;

	if (head == NULL)
		return (0);
	cur = head;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, name) == 0)
		{
			temp = cur->var->content;
			cur->var->content = ft_strdup(content);
			free(temp);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

char	*find_content(char *arg, t_env *env)
{
	t_env	*cur;

	if (env == NULL)
		return (NULL);
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, arg) == 0)
		{
			return (cur->var->content);
		}
		cur = cur->next;
	}
	return (NULL);
}

char	*is_envp(char *arg, t_env *env)
{
	t_env	*cur;

	if (env == NULL)
		return (NULL);
	if (*arg != '$')
		return (NULL);
	arg++;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, arg) == 0)
		{
			return (cur->var->content);
		}
		cur = cur->next;
	}
	return (NULL);
}