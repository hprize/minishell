#include "../minishell.h"

void	free_struct_envp(t_envp *s)
{
	if (s == NULL)
		return ;
	if (s->cmd)
		free(s->cmd);
	if (s->host)
		free(s->host);
	if (s->pwd)
		free(s->pwd);
	if (s->root)
		free(s->root);
	if (s->user)
		free(s->user);
	if (s->where)
		free(s->where);
	ft_memset(s, 0, sizeof(t_envp));
	free(s);
}

void	free_struct_master(t_master *s)
{
	if (s == NULL)
		return ;
	if (s->envp)
		free(s->envp);
	free_split(s->path_list);
	ft_memset(s, 0, sizeof(t_master));
	free(s);
}

void	free_split(char **s)
{
	int	i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i])
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
}