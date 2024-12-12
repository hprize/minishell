#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./ft_fprintf/ft_fprintf_header.h"
# include "struct.h"
# include "src/builtin/bulitin.h"
# include "src/node_utils/node_utils.h"
# include "src/parser/parser.h"
# include "src/parser/parser_struct.h"
# include "src/signal/signal.h"
# include "src/error/error.h"
# include "src/utils/utils.h"

# define HEREDOC_TMP ".heredoc_tmp"

extern int	g_signal;

typedef struct	s_var	t_var;
typedef struct	s_env	t_env;
typedef struct	s_inter	t_inter;
typedef struct	s_envp	t_envp;
typedef struct	s_token	t_token;
typedef struct	s_tree	t_tree;


// testing.c
void	print_tree(t_tree *node, int level);
void	print_tree_linear(t_tree *node);
void	print_tokens(t_token *head);

#endif

