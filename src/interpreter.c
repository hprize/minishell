/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:57:49 by hyebinle          #+#    #+#             */
/*   Updated: 2024/10/31 18:47:42 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_host_name(t_envp *envp);
static char	*get_pwd(t_envp *envp, const char **r_envp);
// static int	get_is_su(t_envp *envp);

char	*set_envp(t_envp *envp, const char **r_envp)
{
	free_struct(envp);
	envp->is_first = 1;
	envp->user = get_word("USER", r_envp);
	envp->host = get_host_name(envp); // /etc/hostname 파일 안에 있음./
	envp->where = get_pwd(envp, r_envp); // 만약 root면 ~로 나오게
	// if (get_is_su(envp)) // UID 체크 후 uid == 0 이면 su
	// 	envp->is_su = '#';
	// else
	// 	envp->is_su = '$';

	// return (join(usr, host, where, ...));//하나씩 받아온거 한꺼번에 조합하면서 return
	envp->cmd = ft_strjoin(envp->user, "@");
	envp->cmd = ft_strjoin_free(envp->cmd, ft_strdup(envp->host));
	envp->cmd = ft_strjoin_free(envp->cmd, ft_strdup(envp->where));
	envp->cmd = ft_strjoin_free(envp->cmd, ft_strdup("$ "));
	return (envp->cmd);
}

void	free_struct(t_envp *s)
{
	if (s == NULL || s->is_first == 0)
		return;
	if (s->cmd != NULL)
		free(s->cmd);
	if (s->user != NULL)
		free(s->user);
	if (s->host != NULL)
		free(s->host);
	if (s->where != NULL)
		free(s->where);
	if (s->root != NULL)
		free(s->root);
	if (s->pwd != NULL)
		free(s->pwd);
	ft_memset(s, 0, sizeof(t_envp));
	s->is_first == 1;
}

char	*get_word(char *word, const char **r_envp)
{
	const char	**cur_line;
	int			word_len;

	cur_line = r_envp;
	word_len = ft_strlen(word);
	while (*cur_line)
	{
		if (ft_strncmp(*cur_line, word, word_len) == 0)
			break;
		cur_line++;
	}
	return (ft_strdup(*cur_line + word_len + 1));
}

static char	*get_pwd(t_envp *envp, const char **r_envp)
{
	int	i;

	envp->root = get_word("HOME", r_envp);
	envp->pwd = get_word("PWD", r_envp);
	i = 0;
	while (envp->root[i] == envp->pwd[i])
		i++;
	return(ft_strjoin(":~", (envp->pwd) + i));
}

static char	*get_host_name(t_envp *envp)
{
	int		fd;
	char	name_leng[256];

	// vscode 디버깅용 파일.
	// fd = open("/etc/hostname", O_RDONLY);
	fd = open("for_test_src/test_hostname", O_RDONLY);
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
	close(fd);
	return (ft_substr(name_leng, 0, ft_strchr_len(name_leng, '.')));
}
