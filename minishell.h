#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./ft_fprintf/ft_fprintf_header.h"
# include "./gnl/get_next_line_bonus.h"
# include "parsing.h"
# include "struct.h"
# include "src/execute/bulitin.h"

# define HEREDOC_TMP ".heredoc_tmp"

t_tree	*parse(t_token *tokens);
t_token	*tokenize(const char *input);

// utils.c
void	add_token(t_token **head, t_token **current, t_token *new_token);
t_token	*create_token(token_type type, const char *value);
t_tree	*create_tree_node(node_type type, const char *value);
void	add_child(t_tree *parent, t_tree *child);
void	free_tree(t_tree *node);
void	free_tokens(t_token *tokens);

// parsing.c
t_tree	*parse_pipe(t_token **current);
t_tree	*parse_exec(t_token **current);
void	parse_reds_opt(t_tree *exec_node, t_token **current);
t_tree *parse_reds(t_token **current);
t_tree *parse_cmd(t_token **current);

// testing.c
void	print_tree(t_tree *node, int level);
void	print_tree_linear(t_tree *node);
void	print_tokens(t_token *head);

// check_path.c
typedef struct	s_master
{
	char	**envp;
	char	**path_list;
}				t_master;

char	**find_path(char **envp);
int		is_cmd(char *token, t_master *master);
int		check_cmd_path(t_token *head, t_master *master);
char	*return_absolute_path(t_tree *node, t_master *master);

// executor.c
void	execute_tree(t_tree *root, t_master *master);
void	close_all_pipe(int pipe_count, int **pipe_fds);
void	execute_pipe(t_tree *pipe_node, t_master *master);


// heredoc.c
void	handle_heredoc(const char *delimiter);




//main_utils
t_env	*init_env(char **envp);
int	fd_print_exit(char *msg, int fd);

//builtin functions
int	builtin_cmd(t_tree *node, t_env **env);


#endif
