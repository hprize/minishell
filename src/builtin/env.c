#include "bulitin.h"

int	ft_env(char **args, t_env *env)
{
	t_env	*cur;

	if (*args != NULL)
		return (127);
	cur = env;
	while (cur)
	{
		if (cur->var->flag_env == 0)
			printf("%s=%s\n", cur->var->name, cur->var->content);
		cur = cur->next;
	}
	return (0);
}
