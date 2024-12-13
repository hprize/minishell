#include "../minishell.h"

int	g_signal;

int	main(int argc, char **argv, const char **envp)
{
	t_envp	*master;
	t_token	*tokens;
	t_tree	*parse_tree;
	char	*input;
	char	*inter;


	master = ft_calloc(1, sizeof(t_envp));
	if (master == NULL)
		exit(1);
	master->envp = (char **)envp;
	master->path_list = find_path(master->envp);
	set_master(master);
	while(1)
	{
		g_signal = 0;
		signal_handel_prompt();
		inter = interface(master->u_envp);
		char	*input = readline(inter);
		signal_all_dfl();
		if (input == NULL)
		{
			replace_content(master->u_envp, "LAST_EXIT_STATUS", "130");
			free_master(master);
			free(inter);
			exit(0);
		}
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue;
		}
		if (input)
		{
			add_history(input);
			tokens = tokenize(input, master->u_envp);
			if (check_cmd_path(tokens, master) == -1)
			{
				free_tokens(tokens);
				free(input);
				replace_content(master->u_envp, "LAST_EXIT_STATUS", "127");
				continue;
			}
			parse_tree = parse(tokens);
			if (parse_tree == NULL)
			{
				free_tokens(tokens);
				free(input);
				continue;
			}
			execute_tree(parse_tree, master);
			free_tree(parse_tree);
			free_tokens(tokens);
			free(inter);
			free(input);
			remove_heredoc_files();
		}
	}
}
