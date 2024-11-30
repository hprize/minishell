#include "../minishell.h"


void	msg_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ulink_error(const char *filename)
{
	unlink(filename);
	perror("Error unlinking file");
	exit(EXIT_FAILURE);
}

void	free_buf(char *buf)
{
	if (buf != NULL)
		free(buf);
}

int	handle_heredoc(const char *delimiter, t_env *u_envp)
{
	int		file;
	char	*buf;
	int		infile;
	int		del_len;
	int		tty_fd;

	del_len = ft_strlen(delimiter);
	file = open(HEREDOC_TMP, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		msg_error("Error creating heredoc file");
	tty_fd = open("/dev/tty", O_WRONLY);
	if (tty_fd < 0)
		msg_error("Error opening terminal for heredoc prompt");

	while (1)
	{
		write(tty_fd, "> ", 2);

		buf = get_next_line(0);
		if (buf == NULL) // ctrl + D
		{
			ft_fprintf(tty_fd, "\nwarning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			// close(file);
			// close(tty_fd);
			free_buf(buf); // 이거 댕글링 가능성
			break;
			// return (1);
		}
		if (ft_strncmp(delimiter, buf, del_len) == 0 && buf[del_len] == '\n')
		{
			free_buf(buf);
			break;
		}
		// if (ft_strlen(buf) == 0) // ctrl + D
		// {
		// 	printf(" warning: here-document delimited by end-of-file (wanted `%s')", delimiter);
		// 	free_buf(buf);
		// 	break;
		// }
		process_env_replacement(&buf, u_envp);
		write(file, buf, ft_strlen(buf));
		free_buf(buf);
	}
	close(file);
	close(tty_fd);
	infile = open(HEREDOC_TMP, O_RDONLY);
	if (infile < 0)
	{
		ulink_error(HEREDOC_TMP);
		msg_error("Error opening heredoc file for reading");
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (0);
}


