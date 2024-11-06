#include "../minishell.h"

int	g_signal;
int	main (int ac, char **av, const char **envp)
{
	t_env	*shell_env;
	char	*input;

	shell_env = init_env((char **)envp);
	// while (1)
	// {
	// 	//환경변수 재설정
	// 	//shlvl 업데이트
	// 	//pwd 업데이트
	// 	//명령어 하나 들어올 때마다 여기로 나와서 업데이트 해야
	// 	input = readline("minishell: ");
	// 	if (input)
	// 	{
	// 		add_history(input);
	// 		builtin_cmd(shell_env, input);
	// 	}
	// 	else if (input == NULL)
	// 	{
	// 		//구조체 프리
	// 		exit(0);
	// 	}
	// }
}