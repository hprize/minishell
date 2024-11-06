#include "../minishell.h"

int	g_signal;

void	signal_exit(int sig)
{
	printf("caught signal %d\n", sig);
	exit(1);
}

int	main(int argc, char **argv, const char **envp)
{
	t_master	*master;
	t_token		*tokens;
	t_tree		*parse_tree;


	master = ft_calloc(1, sizeof(t_master));
	if (master == NULL)
		exit(1);
	master->envp = (char **)envp;
	master->path_list = find_path(master->envp);

	while(1)
	{
		g_signal = 0;

		char	*input = readline("minishell$ ");
		if (input)
		{
			add_history(input);
			printf("entered : %s\n", input);
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
			// execute_tree(parse_tree);
			free_tree(parse_tree);
			free_tokens(tokens);
			free(input);
			
		}
		signal(SIGINT, signal_exit);

	}
}