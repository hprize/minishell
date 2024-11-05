#include "../minishell.h"

int	main (int ac, char **av, const char **envp)
{
	t_env	*shell_env;
	char	*input;

	shell_env = init_env((char **)envp);
	input = readline("minishell: ");
	if (input)
	{
		add_history(input);
		builtin_cmd(shell_env, input);
	}
}