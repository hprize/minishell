#include "../minishell.h"

int	ft_exit_call()
{
	exit(0);
}

//export

int	print_export(t_env *head)
{
	t_env	*cur;

	cur = head;
	while (cur)
	{
		printf("declare -x %s=\"%s\"\n", cur->var->name, cur->var->content);
		cur = cur->next;
	}
	return (0);
}
int	export(t_env **head, char *input)
{
	char **split = ft_split(input, ' '); // 일단 테스트용
	int	num_rows;

	for (num_rows = 0; split[num_rows] != 0; num_rows++) // 대충 만듬
		;
	if (num_rows == 1)
		print_export(*head);
	// else if ()
}

int	builtin_cmd(t_env **env, char *input)
{
	// if (ft_strncmp(input, "env", ft_strlen("env")) == 0)
	// 	ft_env(env);
	if (ft_strncmp(input, "exit", ft_strlen("exit")) == 0)
		ft_exit_call();
	// if (ft_strncmp(input, "pwd", ft_strlen("pwd")) == 0)
	// 	ft_pwd(env);
	if (ft_strncmp(input, "export", ft_strlen("export")) == 0)
		export(env, input);

	return (1);
}
