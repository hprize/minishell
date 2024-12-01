#include "bulitin.h"

static int	dispatch_builtin(char *cmd, char **args, t_tree *node, t_envp *master)
{
	if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (ft_env(args, master->u_envp));
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		ft_exit_call(node->child_count, args, master->u_envp);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (export(node, args, master->u_envp));
	if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (unset(args, master));
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (ft_cd(node, args, master->u_envp));
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (ft_echo(args, master->u_envp));
	return (0);
}

int	builtin_cmd(t_tree *node, t_envp *master)
{
	char	**args;
	int		result;

	args = each_args(node, master, 0);
	if (!args)
		return (0);
	result = dispatch_builtin(node->value, args, node, master);
	ft_arrfree(args);
	return (result);
}
