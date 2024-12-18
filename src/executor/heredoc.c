/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:03:00 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 20:03:01 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	process_heredoc_input(const char *delimiter, t_env *u_envp, int fd)
{
	char	*buf;
	int		del_len;

	del_len = ft_strlen(delimiter);
	while (1)
	{
		buf = readline("> ");
		if (buf == NULL)
		{
			ft_fprintf(2, "warning: here-document delimited by end-of-file \
				(wanted '%s')\n", delimiter);
			break ;
		}
		if (ft_strncmp(delimiter, buf, del_len) == 0 && buf[del_len] == '\0')
		{
			free(buf);
			break ;
		}
		process_env_replacement(&buf, u_envp);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
}

void	handle_heredoc(const char *delimiter, t_env *u_envp, int i, int j)
{
	char	*filename;
	int		fd;

	filename = generate_filename(i, j);
	if (!filename)
	{
		perror("Error generating filename");
		return ;
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error opening heredoc file");
		free(filename);
		return ;
	}
	process_heredoc_input(delimiter, u_envp, fd);
	close(fd);
	free(filename);
}

void	remove_heredoc_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	const char		*pattern;
	size_t			pattern_len;

	pattern = HEREDOC_TMP;
	pattern_len = strlen(pattern);
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Failed to open directory");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, pattern, pattern_len) == 0)
		{
			if (unlink(entry->d_name) != 0)
				perror("Error deleting file");
		}
		entry = readdir(dir);
	}
	if (closedir(dir) < 0)
		perror("Failed to close directory");
}

void	handle_heredoc_child_status(t_envp *master, int status)
{
	int		sig;
	char	*les;

	if (WIFEXITED(status))
	{
		les = ft_itoa(WEXITSTATUS(status));
		strerror(errno);
		replace_content(master->u_envp, "LAST_EXIT_STATUS", les);
		free(les);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		les = ft_itoa(sig + 128);
		replace_content(master->u_envp, "LAST_EXIT_STATUS", les);
		free(les);
	}
}

void	process_heredoc_node(t_tree *node, t_envp *master, int i, int j)
{
	pid_t	pid;
	int		status;
	char	*delimiter;

	pid = fork();
	if (pid == 0)
	{
		delimiter = node->children[j]->children[0]->value;
		signal_handle_heredoc();
		handle_heredoc(delimiter, master->u_envp, i, j);
		exit(0);
	}
	else if (pid > 0)
	{
		signal_all_ign();
		if (wait(&status) == -1)
		{
			perror("wait failed");
			exit(1);
		}
		handle_heredoc_child_status(master, status);
	}
	else
		strerror_exit();
	signal_all_dfl();
}
