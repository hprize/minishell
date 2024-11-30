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

	close(pipe_fd[0]); // 파이프의 읽기 끝을 닫음

	while (1)
	{
		buf = readline("> ");
		if (buf == NULL) // EOF (Ctrl+D) 입력 처리
			break;

		if (ft_strncmp(delimiter, buf, del_len) == 0 && buf[del_len] == '\0')
		{
			free(buf);
			break; // Delimiter를 만나면 종료
		}
		process_env_replacement(&buf, u_envp); // 환경 변수 처리
		write(pipe_fd[1], buf, ft_strlen(buf));
		write(pipe_fd[1], "\n", 1); // 줄바꿈 추가
		free(buf);
	}
}


