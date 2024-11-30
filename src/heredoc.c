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

void	handle_heredoc(const char *delimiter, t_env *u_envp, int pipe_fd[2])
{
	char	*buf;
	int		del_len;

	del_len = ft_strlen(delimiter);

	close(pipe_fd[0]);

	while (1)
	{
		buf = readline("> ");
		if (buf == NULL)
			break;

		if (ft_strncmp(delimiter, buf, del_len) == 0 && buf[del_len] == '\0')
		{
			free(buf);
			break;
		}
		process_env_replacement(&buf, u_envp); 
		write(pipe_fd[1], buf, ft_strlen(buf));
		write(pipe_fd[1], "\n", 1);
		free(buf);
	}
}


