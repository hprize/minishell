#include "../minishell.h"

int	g_signal;

static char	*get_host_name(void)
{
	int		fd;
	char	name_leng[256];
	char	*host;

	// vscode 디버깅용 파일.
	fd = open("/etc/hostname", O_RDONLY);
	// fd = open("for_test_src/test_hostname", O_RDONLY);
	ft_bzero(name_leng, 256);
	if (fd < 0)
	{
		perror("Hostname file open error\n");
		return (NULL);
	}
	if (read (fd, name_leng, sizeof(name_leng)) < 0)
	{
		perror("Hostname file read error\n");
		return (NULL);
	}
	host = ft_substr(name_leng, 0, ft_strchr_len(name_leng, '.'));
	close(fd);
	return (host);
}

char	*find_content(char *arg, t_env *env)
{
	t_env	*cur;

	if (env == NULL)
		return (NULL);
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->var->name, arg) == 0)
		{
			return (cur->var->content);
		}
		cur = cur->next;
	}
	return (NULL);
}

char	*interface(t_env *shell_envp)
{
	char	*result;
	char	*temp;
	char	*host;

	result = ft_strjoin(find_content("USER", shell_envp), "@");
	// temp = result;
	// host = get_host_name();
	// result = ft_strjoin(temp, host);
	// free(temp);
	// free(host);
	result = ft_strjoin_free(result, get_host_name());
	result = ft_strjoin_free(result, ft_strdup(":"));
	temp = ft_strjoin(find_content("PWD", shell_envp), "$ ");
	result = ft_strjoin_free(result, temp);

	return (result);
}

void	free_master(t_envp *master)
{
	ft_arrfree(master->path_list);
	free_node(master->u_envp);
	free(master);
}

int	main(int argc, char **argv, const char **envp)
{
	t_envp	*master;
	t_token		*tokens;
	t_tree		*parse_tree;

	// t_env		*shell_env;
	char		*input;
	char *inter;


	master = ft_calloc(1, sizeof(t_envp));
	if (master == NULL)
		exit(1);
	master->envp = (char **)envp;
	master->path_list = find_path(master->envp);

	master->u_envp = init_env((char **)envp);
	// print_node(master->u_envp);
	while(1)
	{
		g_signal = 0;
		inter = interface(master->u_envp);
		char	*input = readline(inter);
		// char	*input = "export | export a=123";
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

			execute_tree(parse_tree, master);
			free_tree(parse_tree);
			free_tokens(tokens);
			free(inter);
			free(input);
			unlink(HEREDOC_TMP);
		}
		else if (input == NULL)
		{
			free_master(master);
			//사용한 모든 구조체 프리
			exit(0);
		}

	}
}