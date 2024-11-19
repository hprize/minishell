#include "bulitin.h"

int	ft_exit_call()
{
	exit(0);
}

int	ft_env(char **args, t_env **env)
{
	t_env	*cur;

	if (*args != NULL)
		return (127);
	cur = *env;
	while (cur)
	{
		if (cur->var->flag == 1)
			printf("%s=%s\n", cur->var->name, cur->var->content);
		cur = cur->next;
	}
	return (0);
}

int	builtin_cmd(t_tree *node, t_env **env)
{
	int	i;

	i = 0;
	while (node->child_count > i)
	{
		if (node->children[i]->type == NODE_CMD)
		{
			t_tree	*cmd_node = node->children[i];
			char	*args[cmd_node->child_count + 1];
			
			args[cmd_node->child_count] = NULL;
			for (int j = 0; j < cmd_node->child_count; j++)
			{
				args[j] = cmd_node->children[j]->value;
				// printf("test %s\n", args[j]);
			}
			if (ft_strncmp(cmd_node->value, "env", ft_strlen("env")) == 0)
				ft_env(args, env);
			if (ft_strncmp(cmd_node->value, "exit", ft_strlen("exit")) == 0)
				ft_exit_call();
			if (ft_strncmp(cmd_node->value, "pwd", ft_strlen("pwd")) == 0)
				ft_pwd();
			if (ft_strncmp(cmd_node->value, "export", ft_strlen("export")) == 0)
				export(cmd_node, args, env);
			if (ft_strncmp(cmd_node->value, "unset", ft_strlen("unset")) == 0)
				unset(args, *env);
			if (ft_strncmp(cmd_node->value, "cd", ft_strlen("cd")) == 0)
				ft_cd(cmd_node, args, *env);
			if (ft_strncmp(cmd_node->value, "echo", ft_strlen("echo")) == 0)
				ft_echo(args, *env);
		}
		i++;
	}

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
