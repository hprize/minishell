#include "bulitin.h"

void	ft_exit_call()
{
	exit(0);
}

int	ft_env(char **args, t_env *env)
{
	t_env	*cur;

	if (*args != NULL)
		exit(127);
	cur = env;
	while (cur)
	{
		if (cur->var->flag_env == 1)
			printf("%s=%s\n", cur->var->name, cur->var->content);
		cur = cur->next;
	}
	return (0);
}




int	builtin_cmd(t_tree *node, t_envp *master)
{
	char	**args;

	args = each_args(node, master, 0);

	if (ft_strncmp(node->value, "env", ft_strlen("env")) == 0)
		ft_env(args, master->u_envp);
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
	return (1);
}

// void execute_command(t_tree *exec_node, t_envp *master)
// {
//     int i = 0;
//     if (fork() == 0) { // 자식 프로세스
//         // 앞 리다이렉션 설정
//         while (i < exec_node->child_count) {
//             if (exec_node->children[i]->type == NODE_RED || exec_node->children[i]->type == NODE_HEREDOC)
//                 setup_redirection(exec_node->children[i]);
//             else if (exec_node->children[i]->type == NODE_CMD) {
//                 // CMD와 ARG 배열 준비
//                 t_tree *cmd_node = exec_node->children[i];
//                 char *args[cmd_node->child_count + 2];
//                 args[0] = return_absolute_path(cmd_node, master);
//                 if (args[0] == NULL)
//                     exit(EXIT_FAILURE);
//                 int j = 0;
//                 while (j < cmd_node->child_count) {
//                     args[j + 1] = cmd_node->children[j]->value;
//                     j++;
//                 }
//                 args[cmd_node->child_count + 1] = NULL;
//                 // 명령 실행
//                 execve(args[0], args, master->envp);
//                 perror("execvp failed");
//                 exit(1);
//             }
//             i++;
//         }
//         exit(0);
//     }
//     else {
//         wait(NULL);
//     }
// }
