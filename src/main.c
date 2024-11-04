#include "../minishell.h"

int	g_signal;

void	signal_exit(int sig)
{
	printf("caught signal %d\n", sig);
	exit(1);
}

int	main(void)
{
	t_token *tokens;
	t_tree *parse_tree;

	while(1)
	{
		g_signal = 0;

		char	*input = readline("minishell$ ");
		if (input)
		{
			add_history(input);
			printf("entered : %s\n", input);
			tokens = tokenize(input);
			parse_tree = parse(tokens);
			if (parse_tree == NULL) {
				fprintf(stderr, "Parsing failed.\n");
				free_tokens(tokens);
				return (1);
			}
			printf("Parsed Tree:\n");
			print_tree(parse_tree, 0);
			print_tree_linear(parse_tree);

			free_tree(parse_tree);
			free_tokens(tokens);
			free(input);
			
		}
		signal(SIGINT, signal_exit);

	}
}