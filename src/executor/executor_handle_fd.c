/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handle_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee <junlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:19:48 by junlee            #+#    #+#             */
/*   Updated: 2024/12/17 20:22:53 by junlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	restore_stdio(int s_stdin, int s_stdout)
{
	if (dup2(s_stdin, STDIN_FILENO) < 0)
		perror("Failed to restore stdin");
	close(s_stdin);
	if (dup2(s_stdout, STDOUT_FILENO) < 0)
		perror("Failed to restore stdout");
	close(s_stdout);
}

void	setup_pipe_io(int i, int pipe_count, int **pipe_fds)
{
	if (i == 0)
	{
		dup2(pipe_fds[i][1], STDOUT_FILENO);
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
	}
	else if (i > 0 && i < pipe_count - 1)
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		close(pipe_fds[i - 1][0]);
		close(pipe_fds[i][0]);
		dup2(pipe_fds[i][1], STDOUT_FILENO);
		close(pipe_fds[i][1]);
	}
	else if (i == pipe_count - 1)
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		close(pipe_fds[i - 1][0]);
	}
}

void	close_unused_pipes(int i, int pipe_count, int **pipe_fds)
{
	if (i == 0)
		close(pipe_fds[i][1]);
	else if (i > 0 && i < pipe_count - 1)
	{
		close(pipe_fds[i - 1][0]);
		close(pipe_fds[i][1]);
	}
	else if (i == pipe_count - 1)
		close(pipe_fds[i - 1][0]);
}
