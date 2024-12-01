#include "../minishell.h"

void	free_char_index(char *index_i, char *index_j)
{
	free(index_i);
	free(index_j);
}

char	*generate_filename(int i, int j)
{
	char	*filename;
	char	*index_i;
	char	*index_j;
	size_t	filename_len;

	index_i = ft_itoa(i);
	index_j = ft_itoa(j);
	if (!index_i || !index_j)
	{
		free_char_index(index_i, index_j);
		return (NULL);
	}
	filename_len = ft_strlen(HEREDOC_TMP) + ft_strlen(index_i) + ft_strlen(index_j) + 2;
	filename = malloc(filename_len);
	if (!filename)
	{
		free_char_index(index_i, index_j);
		return (NULL);
	}
	ft_strcpy(filename, HEREDOC_TMP);
	ft_strcat(filename, index_i);
	ft_strcat(filename, "_");
	ft_strcat(filename, index_j);
	free_char_index(index_i, index_j);
	return (filename);
}

void	handle_heredoc(const char *delimiter, t_env *u_envp, int i, int j)
{
	char	*buf;
	char	*filename;
	int		del_len;
	int		fd;

	del_len = ft_strlen(delimiter);
	filename = generate_filename(i, j);
	if (!filename)
	{
		perror("Error generating filename");
		return;
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error opening heredoc file");
		free(filename);
		return;
	}
	//printf("Heredoc file created: %s\n", filename);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break;
		if (ft_strncmp(delimiter, buf, del_len) == 0 && buf[del_len] == '\0')
		{
			free(buf);
			break;
		}
		process_env_replacement(&buf, u_envp);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
		close(tty_fd);
	}
	close(fd);
	free(filename);
}

void remove_heredoc_files()
{
	DIR				*dir;
	struct dirent	*entry;
	const char		*pattern;
	size_t			pattern_len;

	pattern = HEREDOC_TMP;
	pattern_len = strlen(pattern);
	dir = opendir(".");
	if (!dir)
	{
		perror("Failed to open directory");
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strncmp(entry->d_name, pattern, pattern_len) == 0)
		{
			if (unlink(entry->d_name) != 0)
				perror("Error deleting file");
		}
	}
	if (closedir(dir) < 0)
		perror("Failed to close directory");
}
