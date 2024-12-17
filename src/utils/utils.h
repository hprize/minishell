#ifndef UTILS_H
# define UTILS_H
# include "../parser/parser_struct.h"
# include "../../minishell.h"

//check_path.c
char	**find_path(char **envp);
int		strchr_is(char *s, int c);
char	*ft_strjoincat(char *s1, char *s2, char c);
char	*valid_path_fn(char *cmd, int is_abs, char *path);
int		is_cmd(char *token, t_envp *master);
int		is_bulitin(char *cmd);
int		check_cmd_path(t_token *head, t_envp *master);
char	*return_absolute_path(t_tree *node, t_envp *master);

// free_utils.c
void	free_tree(t_tree *node);
void	free_tokens(t_token *tokens);
void	free_master(t_envp *master);

// interface.c
char	*get_host_name(void);
char	*interface(t_env *shell_envp);

// set_shlvl.c
char	**copy_envp(char **envp);
int		find_shlvl(char **envp);
void	set_master(t_envp **master, const char **envp);

#endif