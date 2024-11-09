#include "../minishell.h"

int	g_signal;

int	main(int argc, char **argv, const char **envp)
{
	t_master	*master;
	t_token		*tokens;
	t_tree		*parse_tree;

	t_env		*shell_env;
	char		*input;


	master = ft_calloc(1, sizeof(t_master));
	if (master == NULL)
		exit(1);
	master->envp = (char **)envp;
	master->path_list = find_path(master->envp);

	shell_env = init_env((char **)envp);
	while(1)
	{
		g_signal = 0;

		char	*input = readline("minishell$ ");
		if (input)
		{
			add_history(input);
			tokens = tokenize(input);
			print_tokens(tokens);
			if (check_cmd_path(tokens, master) == -1)
			{
				free_tokens(tokens);
				free(input);
				continue;
			}
			parse_tree = parse(tokens);
			if (parse_tree == NULL) {
				printf("Parsing failed.\n");
				free_tokens(tokens);
				return (1);
			}
			printf("Parsed Tree:\n");
			print_tree(parse_tree, 0);
			//print_tree_linear(parse_tree); -- 트리 일렬 출력
			execute_tree(parse_tree, &shell_env);
			free_tree(parse_tree);
			free_tokens(tokens);
			free(input);
		}
		else if (input == NULL)
		{
			//사용한 모든 구조체 프리
			exit(0);
		}

	}
}