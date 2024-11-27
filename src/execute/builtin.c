#include "bulitin.h"

int	builtin_cmd(t_tree *node, t_envp *master)
{
	char	**args;
	int		result;

	args = each_args(node, master, 0);
	result = 0;

	if (ft_strncmp(node->value, "env", ft_strlen("env")) == 0)
		result = ft_env(args, master->u_envp);
	else if (ft_strncmp(node->value, "exit", ft_strlen("exit")) == 0)
		ft_exit_call();
	else if (ft_strncmp(node->value, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd();
	else if (ft_strncmp(node->value, "export", ft_strlen("export")) == 0)
		export(node, args, master->u_envp);
	else if (ft_strncmp(node->value, "unset", ft_strlen("unset")) == 0)
		unset(args, master->u_envp);
	else if (ft_strncmp(node->value, "cd", ft_strlen("cd")) == 0)
		ft_cd(node, args, master->u_envp);
	else if (ft_strncmp(node->value, "echo", ft_strlen("echo")) == 0)
		ft_echo(args, master->u_envp);
	ft_arrfree(args);
	return (result);
}
