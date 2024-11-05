#include "../minishell.h"

t_env	*init_env(char** envp)
{
	t_env	*temp;
	char	*var;

	temp = ft_calloc(1, sizeof(t_env));
	if (!temp)
		fd_print_exit("calloc error", STDERR_FILENO);
	var = getenv("_");
	if (!var)
		fd_print_exit("getenv error", STDERR_FILENO);
	temp->envp = envp;
	temp->u_var = var;
	return (temp);
}

int	ft_env(t_env *env)
{
	int	i;

	i = -1;
	while (env->envp[++i])
	{
		printf("%s\n", env->envp[i]);
	}
	// printf("%s\n", env->u_var);
	return (1);
}
