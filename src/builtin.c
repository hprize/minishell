#include "../minishell.h"

int	builtin_cmd(t_env *env, char *input)
{
	if (ft_strncmp(input, "env", ft_strlen("env")) == 0)
		ft_env(env);
	

	return (1);
}
