/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:57:49 by hyebinle          #+#    #+#             */
/*   Updated: 2024/10/30 01:33:08 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char	*get_host_name(t_envp *envp);
static char	*get_pwd(t_envp *envp);
// static int	get_is_su(t_envp *envp);

char	*set_envp(t_envp *envp)
{
	envp->user = get_word("USER", envp);
	// envp->host = get_host_name(envp); // /etc/hostname 파일 안에 있음.
	envp->where = get_pwd(envp); // 만약 root면 ~로 나오게
	printf("test where : %s\n", envp->where);
	// if (get_is_su(envp)) // UID 체크 후 uid == 0 이면 su
	// 	envp->is_su = '#';
	// else
	// 	envp->is_su = '$';

	// return (join(usr, host, where, ...));//하나씩 받아온거 한꺼번에 조합하면서 return
	return ("a");
}

char	*get_word(char *word, t_envp *envp)
{
	char	**cur_line;
	int		word_len;

	cur_line = envp->envp;
	word_len = ft_strlen(word);
	while (*cur_line)
	{
		if (ft_strncmp(*cur_line, word, word_len) == 0)
			break;
		cur_line++;
	}
	*cur_line = *cur_line + word_len + 1;
	return (ft_strdup(*cur_line));
}

static char	*get_pwd(t_envp *envp)
{
	int	i;

	envp->root = get_word("HOME", envp);
	envp->pwd = get_word("PWD", envp);
	i = 0;
	while (envp->root[i] == envp->pwd[i])
		i++;
	return(ft_strjoin("~", (envp->pwd) + i));
}
