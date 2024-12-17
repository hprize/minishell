#include "../minishell.h"

int	g_signal;

void	handle_no_input(t_envp *master, char *inter)
{
	replace_content(master->u_envp, "LAST_EXIT_STATUS", "130");
	free_master(master);
	free(inter);
	exit(0);
}

void	wrong_cmd_path(t_token *tokens, char *input, t_envp **master)
{
	free_tokens(tokens);
	free(input);
	replace_content((*master)->u_envp, "LAST_EXIT_STATUS", "127");
}

void	parse_tree_err(t_token *tokens, char *input)
{
	free_tokens(tokens);
	free(input);
}

void	right_input(char *input, t_envp **master, char *inter)
{
	t_token	*tokens;
	t_tree	*parse_tree;

	add_history(input);
	tokens = tokenize(input, (*master)->u_envp);
	if (check_cmd_path(tokens, (*master)) == -1)
		wrong_cmd_path(tokens, input, master);
	else
	{
		parse_tree = parse(tokens);
		if (parse_tree == NULL)
			parse_tree_err(tokens, input);
		else
		{
			execute_tree(parse_tree, (*master));
			free_tree(parse_tree);
			free_tokens(tokens);
			free(inter);
			free(input);
			remove_heredoc_files();
		}
	}
}

int	main(int argc, char **argv, const char **envp)
{
	t_envp	*master;
	char	*input;
	char	*inter;

	set_master(&master, envp);
	while (1)
	{
		g_signal = 0;
		signal_handel_prompt();
		inter = interface(master->u_envp);
		input = readline(inter);
		signal_all_dfl();
		if (input == NULL)
			handle_no_input(master, inter);
		else if (ft_strlen(input) == 0)
			free(input);
		else if (input)
			right_input(input, &master, inter);
	}
}
