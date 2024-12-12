#include "../minishell.h"

int	g_signal;


int	main(int argc, char **argv, const char **envp)
{
	t_envp	*master;
	t_token		*tokens;
	t_tree		*parse_tree;
	char		*input;
	char *inter;


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
		// SIGINT
		// SIGQUIT
		// SIGTERM == EOF
		inter = interface(master->u_envp);
		char	*input = readline(inter);
		signal_all_dfl();
		if (input == NULL)
		{
			replace_content(master->u_envp, "LAST_EXIT_STATUS", "130");
			free_master(master);
			free(inter);
			//사용한 모든 구조체 프리
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
			//차라리 글로벌 값으로 시그널 받고 업데이트
			// replace_content(master->u_envp, "LAST_EXIT_STATUS", "130");
			tokens = tokenize(input, master->u_envp);
			// print_tokens(tokens);
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
			// printf("Parsed Tree:\n");
			// print_tree(parse_tree, 0);
			//print_tree_linear(parse_tree); -- 트리 일렬 출력
			// signal_all_ign(); // 미니쉘 중첩되기 전에 시그널 전체 무시하도록. 시그널 중첩되지 않게 처리
			execute_tree(parse_tree, master);
	
			free_tree(parse_tree);
			free_tokens(tokens);
			free(inter);
			free(input);
			remove_heredoc_files();
		}
	}
}
